// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_GrantAbilitiesForNearbyInteractors.generated.h"

struct FInteractionOption;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractableObjectsChangedEvent, const TArray<FInteractionOption>&, InteractableOptions);

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
	static UAbilityTask_GrantAbilitiesForNearbyInteractors* GrantAbilitiesForNearbyInteractors(UGameplayAbility* OwningAbility, float InteractionScanRange, float InteractionScanRate);

	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FInteractableObjectsChangedEvent InteractableObjectsChanged;

private:
	virtual void OnDestroy(bool AbilityEnded) override;

	void QueryInteractables();
	
	float InteractionScanRange = 100;
	float InteractionScanRate = 0.100;

	FTimerHandle QueryTimerHandle;

	TMap<FObjectKey, FGameplayAbilitySpecHandle> InteractionAbilityCache;

	TArray<FInteractionOption> CurrentOptions;
};
