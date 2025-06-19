// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlotAttributeSet.h"
#include "BlotCombatAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class BLOTGAME_API UBlotCombatAttributeSet : public UBlotAttributeSet
{
	GENERATED_BODY()
public:
	UBlotCombatAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
private:
	UFUNCTION()
	void OnRep_MaxWalkSpeed(const FGameplayAttributeData& OldValue);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxWalkSpeed, Category = "Lyra|Combat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxWalkSpeed;
	ATTRIBUTE_ACCESSORS(UBlotCombatAttributeSet, MaxWalkSpeed);
};
