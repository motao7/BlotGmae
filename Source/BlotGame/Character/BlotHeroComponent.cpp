// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BlotHeroComponent.h"

#include "BlotCharacter.h"
#include "BlotGameplayTag.h"
#include "BlotPawnExtensionComponent.h"
#include "CommonCameraComponent.h"
#include "CommonCameraMode.h"
#include "EnhancedInputSubsystems.h"
#include "ExperiencePawnData.h"
#include "TagInputComponent.h"
#include "Team.h"
#include "Components/GameFrameworkComponentManager.h"
#include "Player/BlotPlayerController.h"
#include "Player/BlotPlayerState.h"
#include "TagInputConfig.h"
#include "InputMappingContext.h"
#include "UserSettings/EnhancedInputUserSettings.h"

const FName UBlotHeroComponent::NAME_ActorFeatureName("Hero");

bool UBlotHeroComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
check(Manager);

	APawn* Pawn = GetPawn<APawn>();

	//Pawn有效就行
	if (!CurrentState.IsValid() && DesiredState == BlotGameplayTags::InitState_Spawned)
	{
		// As long as we have a real pawn, let us transition
		if (Pawn) return true;
	}
	//PlayerState必须有效，并且如果是本地InputComponent和LocalPlayer必须有效
	else if (CurrentState == BlotGameplayTags::InitState_Spawned && DesiredState == BlotGameplayTags::InitState_DataAvailable)
	{
		// The player state is required.
		if (!GetPlayerState<ABlotPlayerState>()) return false;

		// If we're authority or autonomous, we need to wait for a controller with registered ownership of the player state.
		if (Pawn->GetLocalRole() != ROLE_SimulatedProxy)
		{
			AController* Controller = GetController<AController>();

			const bool bHasControllerPairedWithPS = (Controller != nullptr) && \
				(Controller->PlayerState != nullptr) && \
				(Controller->PlayerState->GetOwner() == Controller);

			if (!bHasControllerPairedWithPS)
			{
				return false;
			}
		}

		const bool bIsLocallyControlled = Pawn->IsLocallyControlled();
		const bool bIsBot = Pawn->IsBotControlled();

		if (bIsLocallyControlled && !bIsBot)
		{
			ABlotPlayerController* BlotPC = GetController<ABlotPlayerController>();

			// The input component and local player is required when locally controlled.
			if (!Pawn->InputComponent || !BlotPC || !BlotPC->GetLocalPlayer()) return false;
		}

		return true;
	}
	//等待PanwExtension到达DataInitialized状态
	else if (CurrentState == BlotGameplayTags::InitState_DataAvailable && DesiredState == BlotGameplayTags::InitState_DataInitialized)
	{
		ABlotPlayerState* BlotPS = GetPlayerState<ABlotPlayerState>();
		return BlotPS && Manager->HasFeatureReachedInitState(Pawn, UBlotPawnExtensionComponent::NAME_ActorFeatureName, BlotGameplayTags::InitState_DataInitialized);
	}
	else if (CurrentState == BlotGameplayTags::InitState_DataInitialized && DesiredState == BlotGameplayTags::InitState_GameplayReady)
	{
		return true;
	}

	return false;
}

void UBlotHeroComponent::HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState)
{
	if (CurrentState == BlotGameplayTags::InitState_DataAvailable && DesiredState == BlotGameplayTags::InitState_DataInitialized)
	{
		//Init Camera System
		if(ABlotPlayerState* BlotPS = GetPlayerState<ABlotPlayerState>())
		{
			if(const UExperiencePawnData* PawnData=BlotPS->GetPawnData())
			{
				UCommonCameraComponent* CameraComponent=GetOwner()->FindComponentByClass<UCommonCameraComponent>();
				check(CameraComponent);
				CameraComponent->DetermindCameraModeOnPawnDataSetDelgate.BindUObject(this,&ThisClass::DetermindCameraModeOnPawnDataSet);
			}
		}

		//Init InputSystem
		APawn* Pawn = GetPawn<APawn>();
		if (ABlotPlayerController* LyraPC = GetController<ABlotPlayerController>())
		{
			if (Pawn->InputComponent != nullptr)
			{
				InitializePlayerInput(Pawn->InputComponent);
			}
		}
	}
}

void UBlotHeroComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	if (Params.FeatureName == UBlotPawnExtensionComponent::NAME_ActorFeatureName)
	{
		if (Params.FeatureState == BlotGameplayTags::InitState_DataInitialized)
		{
			// If the extension component says all all other components are initialized, try to progress to next state
			CheckDefaultInitialization();
		}
	}
}

void UBlotHeroComponent::CheckDefaultInitialization()
{
	static const TArray<FGameplayTag> StateChain = { BlotGameplayTags::InitState_Spawned, BlotGameplayTags::InitState_DataAvailable, BlotGameplayTags::InitState_DataInitialized, BlotGameplayTags::InitState_GameplayReady };
	ContinueInitStateChain(StateChain);
}

void UBlotHeroComponent::OnRegister()
{
	Super::OnRegister();

	RegisterInitStateFeature();
}

void UBlotHeroComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Listen for when the pawn extension component changes init state
	BindOnActorInitStateChanged(UBlotPawnExtensionComponent::NAME_ActorFeatureName, FGameplayTag(), false);

	// Notifies that we are done spawning, then try the rest of initialization
	ensure(TryToChangeInitState(BlotGameplayTags::InitState_Spawned));
	CheckDefaultInitialization();
}

void UBlotHeroComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterInitStateFeature();
	
	Super::EndPlay(EndPlayReason);
}

void UBlotHeroComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent); // 关键系统失败可崩溃

	const APawn* Pawn = GetPawn<APawn>();
	if (!ensureMsgf(Pawn, TEXT("Pawn is null in SetupPlayerInputComponent")))
	{
		return;
	}
	
	const APlayerController* PC = GetController<APlayerController>();
	if (!ensureMsgf(PC, TEXT("PlayerController is null in SetupPlayerInputComponent")))
	{
		return;
	}
	
	const ULocalPlayer* LP = PC->GetLocalPlayer();
	if (!ensureMsgf(LP, TEXT("LocalPlayer is null in SetupPlayerInputComponent")))
	{
		return;
	}
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!ensureMsgf(Subsystem, TEXT("EnhancedInputLocalPlayerSubsystem is null")))
	{
		return;
	}
	
	Subsystem->ClearAllMappings();
	
	const UBlotPawnExtensionComponent* PawnExtComp = Pawn->FindComponentByClass<UBlotPawnExtensionComponent>();
	if (!ensureMsgf(PawnExtComp, TEXT("Missing UBlotPawnExtensionComponent on pawn")))
	{
		return;
	}
	
	const UExperiencePawnData* PawnData = GetPlayerState<ABlotPlayerState>()->GetPawnData();
	if (!ensureMsgf(PawnData, TEXT("PawnData is null in PawnExtensionComponent")))
	{
		return;
	}
	
	const UTagInputConfig* InputConfig = PawnData->InputConfig;
	if (!ensureMsgf(InputConfig, TEXT("InputConfig is null in PawnData")))
	{
		return;
	}

	//疑问:这里应该在GFA_AddinputMapping中添加向local player

	//怎么将pawn的InputComponent设置为TagInputComponent?
	UTagInputComponent* BlotIC = Cast<UTagInputComponent>(PlayerInputComponent);
	if (!ensureMsgf(BlotIC, TEXT("Unexpected Input Component class! Should be UTagInputComponent or subclass")))
	{
		return;
	}
	
	const TArray<FInputMappingContextAndPriority>& MappingAndPrioritys = PawnData->InputMappingAndPrioritys;

	for (const auto& MappingAndPriority : MappingAndPrioritys)
	{
		UInputMappingContext* Mapping = MappingAndPriority.InputMapping.LoadSynchronous();
		if (!Mapping)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load InputMappingContext!"));
			continue;
		}

		FModifyContextOptions Options;
		Options.bIgnoreAllPressedKeysUntilRelease = false;

		Subsystem->AddMappingContext(Mapping, MappingAndPriority.Priority, Options);
	}
	
	// 绑定输入行为到 GameplayTag（确保 Config 中存在相关标签）
	BlotIC->BindNativeAction(InputConfig, BlotGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move, false);
	BlotIC->BindNativeAction(InputConfig, BlotGameplayTags::InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &ThisClass::Input_LookMouse, false);
	BlotIC->BindNativeAction(InputConfig, BlotGameplayTags::InputTag_Crouch, ETriggerEvent::Triggered, this, &ThisClass::Input_Crouch, false);
}
	
	TSubclassOf<UCommonCameraMode> UBlotHeroComponent::DetermindCameraModeOnPawnDataSet() const
{
	if(ABlotPlayerState* BlotPS=GetPlayerState<ABlotPlayerState>())
	{
		const TSubclassOf<UCommonCameraMode> CommonCameraModeClass= BlotPS->GetPawnData()->DefaultCameraMode;
		check(CommonCameraModeClass);
		return CommonCameraModeClass;
	}
	else
	{
		UE_LOG(LogTeam,Type::Error,TEXT("HeroComponent Only Can be Used On Blot Characer "))
		return nullptr;
	}
}

void UBlotHeroComponent::Input_Move(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();

	if (AController* Controller = Pawn ? Pawn->GetController() : nullptr)
	{
		const FVector2D Value = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

		if (Value.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			Pawn->AddMovementInput(MovementDirection, Value.X);
		}

		if (Value.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			Pawn->AddMovementInput(MovementDirection, Value.Y);
		}
	}
}

void UBlotHeroComponent::Input_LookMouse(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();

	if (!Pawn)
	{
		return;
	}
	
	const FVector2D Value = InputActionValue.Get<FVector2D>();

	if (Value.X != 0.0f)
	{
		Pawn->AddControllerYawInput(Value.X);
	}

	if (Value.Y != 0.0f)
	{
		Pawn->AddControllerPitchInput(Value.Y);
	}
}

void UBlotHeroComponent::Input_Crouch(const FInputActionValue& InputActionValue)
{
	if (ABlotCharacter* Character = GetPawn<ABlotCharacter>())
	{
		Character->ToggleCrouch();
	}
}
