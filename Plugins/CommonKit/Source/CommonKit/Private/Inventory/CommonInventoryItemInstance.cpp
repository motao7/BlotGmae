// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/CommonInventoryItemInstance.h"

#include "CommonKit.h"
#include "Equipment/CommonEquipmentInstance.h"
#include "NativeGameplayTags.h"
#include "Inventory/CommonInventoryItemDefinition.h"
#include "Inventory/CommonInventoryItemFragment.h"
#include "Net/UnrealNetwork.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(Blot_Inventory_NonStackable,"Blot.Inventory.NonStackable")

UCommonInventoryItemInstance::UCommonInventoryItemInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, EntryOwnerRef(nullptr)
{
}

void UCommonInventoryItemInstance::InitializeWithEntry(FCommonInventoryEntry* InEntry)
{
	EntryOwnerRef=InEntry;
}

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

const UCommonInventoryItemFragment* UCommonInventoryItemInstance::FindFragmentByClass(TSubclassOf<UCommonInventoryItemFragment> FragmentClass) const
{
	if ((ItemDef != nullptr) && (FragmentClass != nullptr))
	{
		return GetDefault<UCommonInventoryItemDefinition>(ItemDef)->FindFragmentByClass(FragmentClass);
	}

	return nullptr;
}

int32 UCommonInventoryItemInstance::GetInventoryCount() const
{
	if (EntryOwnerRef&&EntryOwnerRef->Instance==this)
	{
		return EntryOwnerRef->StackCount;
	}

	UE_LOG(LogCommonKit, Error, TEXT("EntryOwnerRef is wrong!!!"));
	return INDEX_NONE;
}

bool UCommonInventoryItemInstance::IsStackableWith(TSubclassOf<UCommonInventoryItemDefinition> OtherItemDef) const
{
	if (OtherItemDef == nullptr||StatTags.ContainsTag(Blot_Inventory_NonStackable))
	{
		return false;
	}

	// ItemDef must be consistent
	if (ItemDef != OtherItemDef)
	{
		return false;
	}
	
	return true;
}

