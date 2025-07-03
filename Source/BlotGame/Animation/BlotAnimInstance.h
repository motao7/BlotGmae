// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Animation/AnimInstance.h"
#include "BlotAnimInstance.generated.h"

/**
 *		Maintain GameplayTagPropertyMap
 */
UCLASS()
class BLOTGAME_API UBlotAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void InitializeWithAbilitySystem(UAbilitySystemComponent* ASC);
	
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	// Gameplay tags that can be mapped to blueprint variables. The variables will automatically update as the tags are added or removed.
	// These should be used instead of manually querying for the gameplay tags.
	UPROPERTY(EditDefaultsOnly, Category = "GameplayTags")
	FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;

	UPROPERTY(BlueprintReadOnly, Category = "Character State Data")
	float GroundDistance = -1.0f;
};
