// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/Tasks/AbilityTask_GrantAbilitiesForNearbyInteractors.h"

#include "AbilitySystemComponent.h"
#include "Interaction/InteractableTarget.h"
#include "Engine/EngineTypes.h"


UAbilityTask_GrantAbilitiesForNearbyInteractors* UAbilityTask_GrantAbilitiesForNearbyInteractors::GrantAbilitiesForNearbyInteractors(UGameplayAbility* OwningAbility)
{
	UAbilityTask_GrantAbilitiesForNearbyInteractors* MyObj = NewAbilityTask<UAbilityTask_GrantAbilitiesForNearbyInteractors>(OwningAbility);
	MyObj->CurrentInteractableTarget=nullptr;
	return MyObj;
}

void UAbilityTask_GrantAbilitiesForNearbyInteractors::Activate()
{
	SetWaitingOnAvatar();
}

