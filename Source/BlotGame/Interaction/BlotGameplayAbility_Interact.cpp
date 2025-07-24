// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/BlotGameplayAbility_Interact.h"
#include "NativeGameplayTags.h"
#include "AbilitySystemComponent.h"
#include "BlotWorldCollectable.h"
#include "InteractionOption.h"
#include "InteractionStatics.h"
#include "Tasks/AbilityTask_SigleTraceTarget.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_Ability_Interaction_Activate, "Ability.Interaction.Activate");

UBlotGameplayAbility_Interact::UBlotGameplayAbility_Interact(const FObjectInitializer& ObjectInitializer)
{
	ActivationPolicy = EExperienceAbilityActivationPolicy::OnSpawn;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

void UBlotGameplayAbility_Interact::TriggerInteraction()
{
	if (CurrentOptions.Num() == 0)
	{
		return;
	}

	UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponentFromActorInfo();
	if (AbilitySystem)
	{
		const FInteractionOption& InteractionOption = CurrentOptions[0];

		AActor* Instigator = GetAvatarActorFromActorInfo();
		AActor* InteractableTargetActor = UInteractionStatics::GetActorFromInteractableTarget(InteractionOption.InteractableTarget);

		// Allow the target to customize the event data we're about to pass in, in case the ability needs custom data
		// that only the actor knows.
		FGameplayEventData Payload;
		Payload.EventTag = TAG_Ability_Interaction_Activate;
		Payload.Instigator = Instigator;
		Payload.Target = InteractableTargetActor;
		
		// Grab the target actor off the payload we're going to use it as the 'avatar' for the interaction, and the
		// source InteractableTarget actor as the owner actor.
		AActor* TargetActor = const_cast<AActor*>(ToRawPtr(Payload.Target));

		// The actor info needed for the interaction.
		FGameplayAbilityActorInfo ActorInfo;
		ActorInfo.InitFromActor(InteractableTargetActor, TargetActor, InteractionOption.TargetAbilitySystem);

		// Trigger the ability using event tag.
		const bool bSuccess = InteractionOption.TargetAbilitySystem->TriggerAbilityFromGameplayEvent(
			InteractionOption.TargetInteractionAbilityHandle,
			&ActorInfo,
			TAG_Ability_Interaction_Activate,
			&Payload,
			*InteractionOption.TargetAbilitySystem
		);
	}
}



void UBlotGameplayAbility_Interact::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (UAbilityTask_SigleTraceTarget* TraceTask = UAbilityTask_SigleTraceTarget::SigleTraceTarget(this))
	{
		TraceTask->HitTargetChanged.AddDynamic(this, &ThisClass::OnHitTargetChanged);
		TraceTask->ReadyForActivation();
	}
}

void UBlotGameplayAbility_Interact::OnHitTargetChanged(AActor* NewTarget, AActor* OldTarget)
{
	CurrentTarget=NewTarget;
	if (ABlotWorldCollectable* OldWorldCollectable=Cast<ABlotWorldCollectable>(OldTarget))
	{
		OldWorldCollectable->SetHighlight(false);
	}
	if (ABlotWorldCollectable* NewWorldCollectable=Cast<ABlotWorldCollectable>(NewTarget))
	{
		NewWorldCollectable->SetHighlight(true);
	}

	OnInteractableTargetChanged(NewTarget, OldTarget);
}

void UBlotGameplayAbility_Interact::OnInteractableTargetChanged(AActor* NewTarget, AActor* OldTarget)
{
	UWorld* World = GetWorld();
	AActor* ActorOwner = GetAvatarActorFromActorInfo();
	
	if (World && ActorOwner)
	{
		TScriptInterface<IInteractableTarget> InteractableTarget;
		InteractableTarget.SetInterface(Cast<IInteractableTarget>(NewTarget));

		if (InteractableTarget.GetInterface() != nullptr)
		{
			TArray<FInteractionOption> Options;
			InteractableTarget->GatherInteractionOptions(/*out*/Options);

			TArray<FInteractionOption> NewOptions;

			UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
			
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
						Option.TargetAbilitySystem = AbilitySystemComponent;
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

			CurrentOptions=Options;
		}
	}
}

