// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/CommonInvnetoryManagerComponent.h"

#include "Inventory/CommonInventoryItemDefinition.h"
#include "Inventory/CommonInventoryItemFragment.h"
#include "Inventory/CommonInventoryItemInstance.h"
#include "Net/UnrealNetwork.h"

///////////////////////////////////////////////////

void FCommonInventoryList::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
}

void FCommonInventoryList::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
}

void FCommonInventoryList::PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize)
{
}

UCommonInventoryItemInstance* FCommonInventoryList::AddEntry(TSubclassOf<UCommonInventoryItemDefinition> ItemDef, int32 StackCount)
{
	UCommonInventoryItemInstance* Result = nullptr;

	check(ItemDef != nullptr);
	check(OwnerComponent);

	AActor* OwningActor = OwnerComponent->GetOwner();
	check(OwningActor->HasAuthority());
	
	FCommonInventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Instance = NewObject<UCommonInventoryItemInstance>(OwnerComponent->GetOwner());
	NewEntry.Instance->SetItemDef(ItemDef);
	for (UCommonInventoryItemFragment* Fragment : GetDefault<UCommonInventoryItemDefinition>(ItemDef)->Fragments)
	{
		if (Fragment != nullptr)
		{
			Fragment->OnInstanceCreated(NewEntry.Instance);
		}
	}
	NewEntry.StackCount = StackCount;
	Result = NewEntry.Instance;
	
	MarkItemDirty(NewEntry);

	return Result;
}

void FCommonInventoryList::AddEntry(UCommonInventoryItemInstance* Instance)
{
	unimplemented();
}

void FCommonInventoryList::RemoveEntry(UCommonInventoryItemInstance* Instance)
{
	for (auto EntryIt = Entries.CreateIterator(); EntryIt; ++EntryIt)
	{
		FCommonInventoryEntry& Entry = *EntryIt;
		if (Entry.Instance == Instance)
		{
			EntryIt.RemoveCurrent();
			MarkArrayDirty();
		}
	}
}

TArray<UCommonInventoryItemInstance*> FCommonInventoryList::GetAllItems() const
{
	TArray<UCommonInventoryItemInstance*> Results;
	Results.Reserve(Entries.Num());
	for (const FCommonInventoryEntry& Entry : Entries)
	{
		if (Entry.Instance != nullptr)
		{
			Results.Add(Entry.Instance);
		}
	}
	return Results;
}

///////////////////////////////////////////////////

UCommonInventoryManageComponent::UCommonInventoryManageComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), InventoryList(this)
{
	SetIsReplicatedByDefault(true);
	bReplicateUsingRegisteredSubObjectList = true;
}

void UCommonInventoryManageComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, InventoryList);
}

UCommonInventoryItemInstance* UCommonInventoryManageComponent::AddItemByDefinition(TSubclassOf<UCommonInventoryItemDefinition> ItemDef, int32 StackCount)
{
	UCommonInventoryItemInstance* Result = nullptr;
	if (ItemDef != nullptr)
	{
		Result = InventoryList.AddEntry(ItemDef, StackCount);
		
		if (IsUsingRegisteredSubObjectList() && IsReadyForReplication() && Result)
		{
			AddReplicatedSubObject(Result);
		}
	}
	return Result;
}

void UCommonInventoryManageComponent::RemoveItemByInstance(UCommonInventoryItemInstance* ItemInstance)
{
	InventoryList.RemoveEntry(ItemInstance);

	if (ItemInstance && IsUsingRegisteredSubObjectList())
	{
		RemoveReplicatedSubObject(ItemInstance);
	}
}

TArray<UCommonInventoryItemInstance*> UCommonInventoryManageComponent::GetAllItems() const
{
	return InventoryList.GetAllItems();
}

UCommonInventoryItemInstance* UCommonInventoryManageComponent::FindFirstItemStackByDefinition(TSubclassOf<UCommonInventoryItemDefinition> ItemDef) const
{
	for (const FCommonInventoryEntry& Entry : InventoryList.Entries)
	{
		UCommonInventoryItemInstance* Instance = Entry.Instance;

		if (IsValid(Instance))
		{
			if (Instance->GetItemDef() == ItemDef)
			{
				return Instance;
			}
		}
	}

	return nullptr;
}
