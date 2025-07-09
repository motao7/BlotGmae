// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/BlotAbilityCost_ItemTagStack.h"

#include "BlotGameplayAbility_FromEquipment.h"
#include "Inventory/CommonInventoryItemInstance.h"


UBlotAbilityCost_ItemTagStack::UBlotAbilityCost_ItemTagStack()
{
	Quantity.SetValue(1.0f);
}

bool UBlotAbilityCost_ItemTagStack::CheckCost(const UBlotGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo) const
{
	if (const UBlotGameplayAbility_FromEquipment* EquipmentAbility = Cast<const UBlotGameplayAbility_FromEquipment>(Ability))
	{
		if (UCommonInventoryItemInstance* ItemInstance = EquipmentAbility->GetAssociatedItem())
		{
			const int32 AbilityLevel = Ability->GetAbilityLevel(Handle, ActorInfo);

			const float NumStacksReal = Quantity.GetValueAtLevel(AbilityLevel);
			const int32 NumStacks = FMath::TruncToInt(NumStacksReal);
			const bool bCanApplyCost = ItemInstance->GetStatTagStackCount(Tag) >= NumStacks;
			
			return bCanApplyCost;
		}
	}
	return false;
}

void UBlotAbilityCost_ItemTagStack::ApplyCost(const UBlotGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (ActorInfo->IsNetAuthority())
	{
		if (const UBlotGameplayAbility_FromEquipment* EquipmentAbility = Cast<const UBlotGameplayAbility_FromEquipment>(Ability))
		{
			if (UCommonInventoryItemInstance* ItemInstance = EquipmentAbility->GetAssociatedItem())
			{
				const int32 AbilityLevel = Ability->GetAbilityLevel(Handle, ActorInfo);

				const float NumStacksReal = Quantity.GetValueAtLevel(AbilityLevel);
				const int32 NumStacks = FMath::TruncToInt(NumStacksReal);

				ItemInstance->RemoveStatTagStack(Tag, NumStacks);
			}
		}
	}
}
