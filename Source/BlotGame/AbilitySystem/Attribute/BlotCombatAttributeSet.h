// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlotAttributeSet.h"
#include "BlotCombatAttributeSet.generated.h"

/**
 *		Class that defines attributes that are necessary for applying damage or healing.
 *		Attribute examples include: damage, healing, attack power, and shield penetrations.
 */
UCLASS(BlueprintType)
class BLOTGAME_API UBlotCombatAttributeSet : public UBlotAttributeSet
{
	GENERATED_BODY()
	
public:
	UBlotCombatAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	ATTRIBUTE_ACCESSORS(UBlotCombatAttributeSet, BaseDamage);
	ATTRIBUTE_ACCESSORS(UBlotCombatAttributeSet, BaseHeal);
	ATTRIBUTE_ACCESSORS(UBlotCombatAttributeSet, MaxWalkSpeed);

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

protected:
	UFUNCTION()
	void OnRep_BaseDamage(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_BaseHeal(const FGameplayAttributeData& OldValue);
	
private:
	UFUNCTION()
	void OnRep_MaxWalkSpeed(const FGameplayAttributeData& OldValue);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxWalkSpeed, Category = "Blot|Combat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxWalkSpeed;

	// The base amount of damage to apply in the damage execution.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BaseDamage, Category = "Blot|Combat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseDamage;

	// The base amount of healing to apply in the heal execution.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BaseHeal, Category = "Blot|Combat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseHeal;
};
