// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/CommonInventoryItemInstance.h"

#include "CommonKit.h"
#include "Equipment/CommonEquipmentInstance.h"
#include "Inventory/CommonInventoryItemDefinition.h"
#include "Inventory/CommonInventoryItemFragment.h"
#include "Net/UnrealNetwork.h"


void UCommonInventoryItemInstance::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, ItemDef);
	DOREPLIFETIME(ThisClass, StatTags);
}

void UCommonInventoryItemInstance::AddStatTagStack(FGameplayTag Tag, int32 StackCount)
{
	StatTags.AddStack(Tag, StackCount);
}

void UCommonInventoryItemInstance::RemoveStatTagStack(FGameplayTag Tag, int32 StackCount)
{
	StatTags.RemoveStack(Tag, StackCount);
}

int32 UCommonInventoryItemInstance::GetStatTagStackCount(FGameplayTag Tag) const
{
	return StatTags.GetStackCount(Tag);
}

bool UCommonInventoryItemInstance::HasStatTag(FGameplayTag Tag) const
{
	return StatTags.ContainsTag(Tag);
}

bool UCommonInventoryItemInstance::IsDefaultItem()
{
	if (!ItemDef)
	{
		UE_LOG(LogCommonKit, Warning, TEXT("IsDefaultItem() called, but ItemDef is null in %s"), *GetName());
		return false;
	}

	UCommonInventoryItemDefinition* DefaultDef = Cast<UCommonInventoryItemDefinition>(ItemDef->GetDefaultObject());
	if (!DefaultDef)
	{
		UE_LOG(LogCommonKit, Warning, TEXT("IsDefaultItem() failed to cast ItemDef in %s to UCommonInventoryItemDefinition"), *GetName());
		return false;
	}

	UE_LOG(LogCommonKit, Log, TEXT("IsDefaultItem() called on %s, result = %s"), *GetName(), DefaultDef->IsDefaultItem ? TEXT("true") : TEXT("false"));
	return DefaultDef->IsDefaultItem;
}

const UCommonInventoryItemFragment* UCommonInventoryItemInstance::FindFragmentByClass(TSubclassOf<UCommonInventoryItemFragment> FragmentClass) const
{
	if ((ItemDef != nullptr) && (FragmentClass != nullptr))
	{
		return GetDefault<UCommonInventoryItemDefinition>(ItemDef)->FindFragmentByClass(FragmentClass);
	}

	return nullptr;
}
