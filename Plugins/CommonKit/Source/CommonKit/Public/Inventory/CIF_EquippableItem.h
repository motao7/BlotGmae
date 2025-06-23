// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonInventoryItemFragment.h"
#include "Inventory/CommonInventoryItemInstance.h"
#include "CIF_EquippableItem.generated.h"

class UCommonEquipmentDefinition;
/**
 * 
 */
UCLASS()
class COMMONKIT_API UCIF_EquippableItem : public UCommonInventoryItemFragment
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category=Lyra)
	TSubclassOf<UCommonEquipmentDefinition> EquipmentDefinition;
};
