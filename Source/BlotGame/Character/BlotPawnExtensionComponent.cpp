// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BlotPawnExtensionComponent.h"

#include "BlotAbilitySystemComponent.h"
#include "BlotGameplayTag.h"
#include "Components/GameFrameworkComponentManager.h"
#include "Player/BlotPlayerState.h"

const FName UBlotPawnExtensionComponent::NAME_ActorFeatureName("PawnExtension");


bool UBlotPawnExtensionComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	check(Manager);

	APawn* Pawn = GetPawn<APawn>();
	//Pawn有效进入Spanwned状态
	if (!CurrentState.IsValid() && DesiredState == BlotGameplayTags::InitState_Spawned)
	{
		
		if (Pawn) return true;
	}

	//PawnData有效&&该charatcer(持有该组件的Pawn)本地和服务器端都有控制器控制进入DataAvaliable状态
	if (CurrentState == BlotGameplayTags::InitState_Spawned && DesiredState == BlotGameplayTags::InitState_DataAvailable)
	{
		ABlotPlayerState* PS=GetPlayerState<ABlotPlayerState>();
		if (!PS) return false;

		if (!PS->GetPawnData()) return false;
		
		const bool bHasAuthority = Pawn->HasAuthority();
		const bool bIsLocallyControlled = Pawn->IsLocallyControlled();

		if (bHasAuthority || bIsLocallyControlled)
		{
			if (!Pawn->GetController()) return false;
		}

		return true;
	}
	//所有其他组件(拥有插件GameFrameworkInitStateInterface)也初始化到达DataAvailable状态，进入DataInitialized状态
	else if (CurrentState == BlotGameplayTags::InitState_DataAvailable && DesiredState == BlotGameplayTags::InitState_DataInitialized)
	{
		return Manager->HaveAllFeaturesReachedInitState(Pawn, BlotGameplayTags::InitState_DataAvailable);
	}
	else if (CurrentState == BlotGameplayTags::InitState_DataInitialized && DesiredState == BlotGameplayTags::InitState_GameplayReady)
	{
		return true;
	}

	return false;
}

void UBlotPawnExtensionComponent::HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState)
{
	//啥事不干
}

void UBlotPawnExtensionComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	// OnActorInitStateChanged无论是哪一个组件的状态发生变化所有其他接有接口(GameFrameworkInitStateInterface)的组件
	//都会调用OnActorInitStateChanged，OnActorInitStateChanged就是回调函数，而委托是一个多播委托
	if (Params.FeatureName != NAME_ActorFeatureName)
	{
		//如果其他组件进入了DataAvailable检查此组件是否能往下更进一步(检查所有组件是否在进入了DataAvailable状态)
		if (Params.FeatureState == BlotGameplayTags::InitState_DataAvailable)
		{
			CheckDefaultInitialization();
		}
	}
}

void UBlotPawnExtensionComponent::CheckDefaultInitialization()
{
	//在Check我们自己的初始化链时，先调用其他所有接入(GameFrameworkInitStateInterface)接口的组件的CheckDefaultInitialization函数
	CheckDefaultInitializationForImplementers();

	static const TArray<FGameplayTag> StateChain = { BlotGameplayTags::InitState_Spawned, BlotGameplayTags::InitState_DataAvailable, BlotGameplayTags::InitState_DataInitialized, BlotGameplayTags::InitState_GameplayReady };
	ContinueInitStateChain(StateChain);
}

void UBlotPawnExtensionComponent::InitializeAbilitySystem(UBlotAbilitySystemComponent* InASC, AActor* InOwnerActor)
{
	check(InASC);
	check(InOwnerActor);

	if (AbilitySystemComponent == InASC)
	{
		// The ability system component hasn't changed.
		return;
	}

	APawn* Pawn = GetPawnChecked<APawn>();
	
	AbilitySystemComponent = InASC;
	AbilitySystemComponent->InitAbilityActorInfo(InOwnerActor, Pawn);

	OnAbilitySystemInitialized.Broadcast();
}

void UBlotPawnExtensionComponent::HandleOnControllerChanged()
{
	CheckDefaultInitialization();
}

void UBlotPawnExtensionComponent::HandleOnPlayerStateReplicated()
{
	CheckDefaultInitialization();
}

void UBlotPawnExtensionComponent::HandleOnSetupPlayerInputComponent()
{
	CheckDefaultInitialization();
}

void UBlotPawnExtensionComponent::SetupPlayerInputComponent()
{
	CheckDefaultInitialization();
}

void UBlotPawnExtensionComponent::OnAbilitySystemInitialized_RegisterAndCall(FSimpleMulticastDelegate::FDelegate Delegate)
{
	if (!OnAbilitySystemInitialized.IsBoundToObject(Delegate.GetUObject()))
	{
		OnAbilitySystemInitialized.Add(Delegate);
	}

	if (AbilitySystemComponent)
	{
		Delegate.Execute();
	}
}

void UBlotPawnExtensionComponent::OnRegister()
{
	Super::OnRegister();

	RegisterInitStateFeature();
}

void UBlotPawnExtensionComponent::BeginPlay()
{
	Super::BeginPlay();

	// Listen for when the pawn extension component changes init state
	BindOnActorInitStateChanged(NAME_None, FGameplayTag(), false);

	// Notifies that we are done spawning, then try the rest of initialization
	ensure(TryToChangeInitState(BlotGameplayTags::InitState_Spawned));
	CheckDefaultInitialization();
}

void UBlotPawnExtensionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterInitStateFeature();
	
	Super::EndPlay(EndPlayReason);
}
