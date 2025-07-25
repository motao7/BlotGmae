// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/BlotAbilityCost.h"
#include "BlotAbilityCost_ItemTagStack.generated.h"

/**
 * 
 */
UCLASS()
class BLOTGAME_API UBlotAbilityCost_ItemTagStack : public UBlotAbilityCost
{
	GENERATED_BODY()

public:
	UBlotAbilityCost_ItemTagStack();

	//~UBlotAbilityCost interface
	virtual bool CheckCost(const UBlotGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo) const override;
	virtual void ApplyCost(const UBlotGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	//~End of UBlotAbilityCost interface

protected:
	/** How much of the tag to spend (keyed on ability level) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Costs)
	FScalableFloat Quantity;

	/** Which tag to spend some of */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Costs)
	FGameplayTag Tag;
};
