// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/BlotGameplayAbility_FromEquipment.h"

#include "Equipment/CommonEquipmentInstance.h"
#include "Inventory/CommonInventoryItemInstance.h"


UCommonEquipmentInstance* UBlotGameplayAbility_FromEquipment::GetAssociatedEquipment() const
{
	if (FGameplayAbilitySpec* Spec=GetCurrentAbilitySpec())
	{
		return Cast<UCommonEquipmentInstance>(Spec->SourceObject);
	}
	return nullptr;
}

UCommonInventoryItemInstance* UBlotGameplayAbility_FromEquipment::GetAssociatedItem() const
{
	if (UCommonEquipmentInstance* Equipment = GetAssociatedEquipment())
	{
		return Cast<UCommonInventoryItemInstance>(Equipment->GetInstigator());
	}
	return nullptr;
}
