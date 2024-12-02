// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BlotHeroComponent.h"

#include "BlotCharacter.h"
#include "BlotGameplayTag.h"
#include "BlotPawnExtensionComponent.h"
#include "CommonCameraComponent.h"
#include "CommonCameraMode.h"
#include "ExperiencePawnData.h"
#include "Team.h"
#include "Components/GameFrameworkComponentManager.h"
#include "Player/BlotPlayerController.h"
#include "Player/BlotPlayerState.h"

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
