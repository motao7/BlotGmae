// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Templates/SharedPointer.h"
#include "BlotAbilitySystemStatics.generated.h"


/**
 * 
 */
UCLASS()
class BLOTGAME_API UBlotAbilitySystemStatics : public UAbilitySystemBlueprintLibrary
{
	GENERATED_BODY()
	
public:
	/** Extracts a hit results from the effect context if it is set */
	UFUNCTION(BlueprintPure, Category = "Ability|EffectContext", Meta = (DisplayName = "GetHitResults"))
	static TArray<FHitResult> EffectContextGetHitResults(FGameplayEffectContextHandle EffectContext);

};
