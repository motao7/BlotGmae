// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/BlotGameplayAbility_Death.h"

#include "BlotAbilitySystemComponent.h"
#include "Character/BlotHealthComponent.h"


void UBlotGameplayAbility_Death::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	check(ActorInfo);

	//TODO:CancelAbilities
	// UBlotAbilitySystemComponent* BlotASC = CastChecked<UBlotAbilitySystemComponent>(ActorInfo->AbilitySystemComponent.Get());
	// BlotASC->CancelAbilities(nullptr, &AbilityTypesToIgnore, this);

	SetCanBeCanceled(false);
	StartDeath();

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UBlotGameplayAbility_Death::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	check(ActorInfo);
	FinishDeath();
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UBlotGameplayAbility_Death::StartDeath()
{
	if (UBlotHealthComponent* HealthComponent = UBlotHealthComponent::FindHealthComponent(GetAvatarActorFromActorInfo()))
	{
		if (HealthComponent->GetDeathState() == EBlotDeathState::NotDead)
		{
			HealthComponent->StartDeath();
		}
	}
}

void UBlotGameplayAbility_Death::FinishDeath()
{
	if (UBlotHealthComponent* HealthComponent = UBlotHealthComponent::FindHealthComponent(GetAvatarActorFromActorInfo()))
	{
		if (HealthComponent->GetDeathState() == EBlotDeathState::DeathStarted)
		{
			HealthComponent->FinishDeath();
		}
	}
}
