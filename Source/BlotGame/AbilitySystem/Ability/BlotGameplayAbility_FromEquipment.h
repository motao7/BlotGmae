// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/BlotGameplayAbility.h"
#include "BlotGameplayAbility_FromEquipment.generated.h"

class UCommonInventoryItemInstance;
class UCommonEquipmentInstance;
/**
 * 
 */
UCLASS()
class BLOTGAME_API UBlotGameplayAbility_FromEquipment : public UBlotGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="Blot|Ability")
	UCommonEquipmentInstance* GetAssociatedEquipment() const;

	UFUNCTION(BlueprintCallable, Category = "Blot|Ability")
	UCommonInventoryItemInstance* GetAssociatedItem() const;

	
	
};
