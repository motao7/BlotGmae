// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/Tasks/AbilityTask_GrantAbilitiesForNearbyInteractors.h"

#include "AbilitySystemComponent.h"
#include "Interaction/InteractableTarget.h"
#include "Interaction/InteractionOption.h"
#include "Interaction/InteractionStatics.h"
#include "Physics/BlotCollisionChannel.h"
#include "Engine/EngineTypes.h"
#include "Engine/OverlapResult.h"


UAbilityTask_GrantAbilitiesForNearbyInteractors* UAbilityTask_GrantAbilitiesForNearbyInteractors::GrantAbilitiesForNearbyInteractors(UGameplayAbility* OwningAbility, float InteractionScanRange, float InteractionScanRate)
{
	UAbilityTask_GrantAbilitiesForNearbyInteractors* MyObj = NewAbilityTask<UAbilityTask_GrantAbilitiesForNearbyInteractors>(OwningAbility);
	MyObj->InteractionScanRange = InteractionScanRange;
	MyObj->InteractionScanRate = InteractionScanRate;
	return MyObj;
}

void UAbilityTask_GrantAbilitiesForNearbyInteractors::Activate()
{
	SetWaitingOnAvatar();
	
	UWorld* World = GetWorld();
	World->GetTimerManager().SetTimer(QueryTimerHandle, this, &ThisClass::QueryInteractables, InteractionScanRate, true);
}

void UAbilityTask_GrantAbilitiesForNearbyInteractors::OnDestroy(bool AbilityEnded)
{
	Super::OnDestroy(AbilityEnded);

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(QueryTimerHandle);
	}

	Super::OnDestroy(AbilityEnded);
}

void UAbilityTask_GrantAbilitiesForNearbyInteractors::QueryInteractables()
{
	UWorld* World = GetWorld();
	AActor* ActorOwner = GetAvatarActor();
	
	if (World && ActorOwner)
	{
		FCollisionQueryParams Params(SCENE_QUERY_STAT(UAbilityTask_GrantAbilitiesForNearbyInteractors), false);
		
		TArray<FOverlapResult> OverlapResults;
		
		World->OverlapMultiByChannel(OUT OverlapResults, ActorOwner->GetActorLocation(), FQuat::Identity, Blot_TraceChannel_Interaction, FCollisionShape::MakeSphere(InteractionScanRange), Params);

		if (OverlapResults.Num() > 0)
		{
			TArray<TScriptInterface<IInteractableTarget>> InteractableTargets;
			UInteractionStatics::AppendInteractableTargetsFromOverlapResults(OverlapResults, OUT InteractableTargets);
			
			TArray<FInteractionOption> Options;
			for (TScriptInterface<IInteractableTarget>& InteractiveTarget : InteractableTargets)
			{
				InteractiveTarget->GatherInteractionOptions(/*out*/Options);
			}

			TArray<FInteractionOption> NewOptions;

			// Check if any of the options need to grant the ability to the user before they can be used.
			for (FInteractionOption& Option : Options)
			{
				if (Option.InteractionAbilityToGrant)
				{
					// Grant the ability to the GAS, otherwise it won't be able to do whatever the interaction is.
					FObjectKey ObjectKey(Option.InteractionAbilityToGrant);
					if (!InteractionAbilityCache.Find(ObjectKey))
					{
						FGameplayAbilitySpec Spec(Option.InteractionAbilityToGrant, 1, INDEX_NONE, this);
						FGameplayAbilitySpecHandle Handle = AbilitySystemComponent->GiveAbility(Spec);
						InteractionAbilityCache.Add(ObjectKey, Handle);
					}
				}

				//Update Option's Info
				FGameplayAbilitySpec* InteractionAbilitySpec = nullptr;
				// if there is a handle an a target ability system, we're triggering the ability on the target.
				if (Option.TargetAbilitySystem && Option.TargetInteractionAbilityHandle.IsValid())
				{
					// Find the spec
					InteractionAbilitySpec = Option.TargetAbilitySystem->FindAbilitySpecFromHandle(Option.TargetInteractionAbilityHandle);
				}
				// If there's an interaction ability then we're activating it on ourselves.
				else if (Option.InteractionAbilityToGrant)
				{
					// Find the spec
					InteractionAbilitySpec = AbilitySystemComponent->FindAbilitySpecFromClass(Option.InteractionAbilityToGrant);

					if (InteractionAbilitySpec)
					{
						// update the option
						Option.TargetAbilitySystem = AbilitySystemComponent.Get();
						Option.TargetInteractionAbilityHandle = InteractionAbilitySpec->Handle;
					}
				}

				if (InteractionAbilitySpec)
				{
					// Filter any options that we can't activate right now for whatever reason.
					if (InteractionAbilitySpec->Ability->CanActivateAbility(InteractionAbilitySpec->Handle, AbilitySystemComponent->AbilityActorInfo.Get()))
					{
						NewOptions.Add(Option);
					}
				}
			}

			//Check if CurrentOptions Changed 
			bool bOptionsChanged = false;
			if (NewOptions.Num() == CurrentOptions.Num())
			{
				NewOptions.Sort();

				for (int OptionIndex = 0; OptionIndex < NewOptions.Num(); OptionIndex++)
				{
					const FInteractionOption& NewOption = NewOptions[OptionIndex];
					const FInteractionOption& CurrentOption = CurrentOptions[OptionIndex];

					if (NewOption != CurrentOption)
					{
						bOptionsChanged = true;
						break;
					}
				}
			}
			else
			{
				bOptionsChanged = true;
			}

			if (bOptionsChanged)
			{
				CurrentOptions = NewOptions;
				InteractableObjectsChanged.Broadcast(CurrentOptions);
			}
		}	
	}
}
