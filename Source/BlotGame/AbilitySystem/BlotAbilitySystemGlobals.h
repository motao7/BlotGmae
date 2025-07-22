// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "BlotAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS(Config=Game)
class BLOTGAME_API UBlotAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

public:
	//~UAbilitySystemGlobals interface
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
	//~End of UAbilitySystemGlobals interface
};
