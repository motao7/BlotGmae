// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BlotHeroComponent.h"

#include "BlotGameplayTag.h"
#include "BlotPawnExtensionComponent.h"
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
	IGameFrameworkInitStateInterface::HandleChangeInitState(Manager, CurrentState, DesiredState);
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
