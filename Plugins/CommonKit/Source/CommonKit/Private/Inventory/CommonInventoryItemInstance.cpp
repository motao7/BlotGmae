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

// 在 CommonInvnetoryManagerComponent.cpp 中添加以下函数实现

void UCommonInventoryManageComponent::ExchangeItems(int32 Index1, int32 Index2)
{
	// 检查索引有效性
	if (Index1 == Index2 || 
		!InventoryList.Entries.IsValidIndex(Index1) || 
		!InventoryList.Entries.IsValidIndex(Index2))
	{
		return;
	}

	// 只有在服务器端执行交换逻辑
	if (GetOwner()->HasAuthority())
	{
		FCommonInventoryEntry& Entry1 = InventoryList.Entries[Index1];
		FCommonInventoryEntry& Entry2 = InventoryList.Entries[Index2];

		// 交换两个条目的内容
		UCommonInventoryItemInstance* TempInstance = Entry1.Instance;
		int32 TempStackCount = Entry1.StackCount;

		Entry1.Instance = Entry2.Instance;
		Entry1.StackCount = Entry2.StackCount;
		
		Entry2.Instance = TempInstance;
		Entry2.StackCount = TempStackCount;

		// 标记两个条目为脏数据以触发网络同步
		InventoryList.MarkItemDirty(Entry1);
		InventoryList.MarkItemDirty(Entry2);

		// 如果使用了注册子对象列表，需要更新子对象
		if (IsUsingRegisteredSubObjectList() && IsReadyForReplication())
		{
			// 移除旧的子对象（如果存在）
			if (Entry1.Instance)
			{
				RemoveReplicatedSubObject(Entry1.Instance);
			}
			if (Entry2.Instance)
			{
				RemoveReplicatedSubObject(Entry2.Instance);
			}

			// 添加新的子对象（如果存在）
			if (Entry1.Instance)
			{
				AddReplicatedSubObject(Entry1.Instance);
			}
			if (Entry2.Instance)
			{
				AddReplicatedSubObject(Entry2.Instance);
			}
		}

		// 广播变化消息
		InventoryList.BroadcastChangeMessage(Entry1, Index1, Entry1.LastObservedCount, Entry1.StackCount);
		InventoryList.BroadcastChangeMessage(Entry2, Index2, Entry2.LastObservedCount, Entry2.StackCount);

		// 更新最后观察到的数量
		Entry1.LastObservedCount = Entry1.StackCount;
		Entry2.LastObservedCount = Entry2.StackCount;
	}
}


