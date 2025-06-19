// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/BlotGameplayAbility.h"
#include "BlotGameplayAbility_SlientWalk.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BLOTGAME_API UBlotGameplayAbility_SlientWalk : public UBlotGameplayAbility
{
	GENERATED_BODY()

public:
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
};
