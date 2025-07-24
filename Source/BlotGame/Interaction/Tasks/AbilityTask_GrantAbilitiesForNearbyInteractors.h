// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Interaction/InteractionOption.h"
#include "AbilityTask_GrantAbilitiesForNearbyInteractors.generated.h"

class IInteractableTarget;

/**
 *		Used for GA_Interact to GrantAbilitiesForNearbyInteractor
 */
UCLASS()
class BLOTGAME_API UAbilityTask_GrantAbilitiesForNearbyInteractors : public UAbilityTask
{
	GENERATED_BODY()

public:
	/** Wait until an overlap occurs. This will need to be better fleshed out so we can specify game specific collision requirements */
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_GrantAbilitiesForNearbyInteractors* GrantAbilitiesForNearbyInteractors(UGameplayAbility* OwningAbility);

	virtual void Activate() override;

private:
	void OnInteractableTargetChanged();

	IInteractableTarget* CurrentInteractableTarget;
};
