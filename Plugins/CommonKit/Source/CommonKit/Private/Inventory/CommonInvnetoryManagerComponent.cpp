// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/CommonInvnetoryManagerComponent.h"

#include "CommonKit.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Inventory/CommonInventoryItemDefinition.h"
#include "Inventory/CommonInventoryItemFragment.h"
#include "Inventory/CommonInventoryItemInstance.h"
#include "Net/UnrealNetwork.h"
#include "NativeGameplayTags.h"
#include "ToolMenusEditor.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_Common_Inventory_Message_StackChanged, "Common.Inventory.Message.StackChanged");

///////////////////////////////////////////////////

FCommonInventoryList::FCommonInventoryList(UActorComponent* InOwnerComponent, int32 MaxSize)
	: OwnerComponent(InOwnerComponent)
	, ListMaxSize(MaxSize)
{
}

void FCommonInventoryList::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
	for (int32 Index : RemovedIndices)
	{
		FCommonInventoryEntry& Stack = Entries[Index];
		BroadcastChangeMessage(Stack,Index,/*OldCount=*/ Stack.StackCount, /*NewCount=*/ 0);
		Stack.LastObservedCount = 0;
	}
}

void FCommonInventoryList::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	for (int32 Index : AddedIndices)
	{
		FCommonInventoryEntry& Stack = Entries[Index];
		/**Since pass a pointer so reposition the position of the pointer on the client's computer */
		Entries[Index].Instance->InitializeWithEntry(&Entries[Index]);
		BroadcastChangeMessage(Stack,Index,/*OldCount=*/ 0, /*NewCount=*/ Stack.StackCount);
		Stack.LastObservedCount = Stack.StackCount;
	}
}

void FCommonInventoryList::PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize)
{
	for (int32 Index : ChangedIndices)
	{
		FCommonInventoryEntry& Stack = Entries[Index];
		check(Stack.LastObservedCount != INDEX_NONE);
		BroadcastChangeMessage(Stack,Index,/*OldCount=*/ Stack.LastObservedCount, /*NewCount=*/ Stack.StackCount);
		Stack.LastObservedCount = Stack.StackCount;
	}
}

UCommonInventoryItemInstance* FCommonInventoryList::AddEntry(TSubclassOf<UCommonInventoryItemDefinition> ItemDef, int32 StackCount)
{
	check(ItemDef != nullptr);
	check(OwnerComponent);

	AActor* OwningActor = OwnerComponent->GetOwner();
	check(OwningActor->HasAuthority());
	
	//Check if has same Instance
	for (int32 Index = 0; Index < ListMaxSize; ++Index)
	{
		FCommonInventoryEntry& Entry= Entries[Index];
		if (Entry.Instance && Entry.Instance->GetItemDef())
		{
			if (Entry.Instance->IsStackableWith(ItemDef))
			{
				Entry.StackCount += StackCount;
				
				MarkItemDirty(Entry);
				BroadcastChangeMessage(Entry,Index,/*OldCount=*/ Entry.LastObservedCount, /*NewCount=*/ Entry.StackCount);
				return Entry.Instance;
			}
		}
	}
	
	for (int32 Inx = 0; Inx < ListMaxSize; ++Inx)
	{
		FCommonInventoryEntry& Entry= Entries[Inx];
		if (!Entry.Instance->GetItemDef())
		{
			UCommonInventoryItemInstance* Result = nullptr;
			Entry.Instance->SetItemDef(ItemDef);
			Entry.Instance->InitializeWithEntry(&Entry);

			for (UCommonInventoryItemFragment* Fragment : GetDefault<UCommonInventoryItemDefinition>(ItemDef)->Fragments)
			{
				if (Fragment != nullptr)
				{
					Fragment->OnInstanceCreated(Entry.Instance);
				}
			}
			Entry.StackCount = StackCount;

			Result = Entry.Instance;
	
			MarkItemDirty(Entry);
			BroadcastChangeMessage(Entry,Inx,/*OldCount=*/ Entry.LastObservedCount, /*NewCount=*/ Entry.StackCount);
			return Result;
		}
	}
	
	UE_LOG(LogCommonKit,Error,TEXT("Inventory Add Item Over Inventory Size"));
	return nullptr;
}

UCommonInventoryItemInstance* FCommonInventoryList::ClearEntry(int32 Index)
{
	UCommonInventoryItemInstance* Result=nullptr;
	if (Entries.IsValidIndex(Index))
	{
		FCommonInventoryEntry& Entry=Entries[Index];
		Result=Entry.Instance;
		Entry.Instance->SetItemDef(nullptr);
		Entry.StackCount = 0;
		MarkItemDirty(Entry);
		BroadcastChangeMessage(Entry,Index,/*OldCount=*/ Entry.LastObservedCount, /*NewCount=*/ Entry.StackCount);
	}
	return Result;
}

int32 FCommonInventoryList::RemoveEntry(int32 Index, int32 DecreaseCount)
{
	check(OwnerComponent);
	AActor* OwningActor = OwnerComponent->GetOwner();
	check(OwningActor->HasAuthority());
	check(Entries.IsValidIndex(Index));

	FCommonInventoryEntry& Entry = Entries[Index];
	int32 OldCount = Entry.StackCount;
    
	// 如果减少的数量大于等于当前堆叠数，则清除整个条目
	if (DecreaseCount >= Entry.StackCount)
	{
		UCommonInventoryItemInstance* Result = ClearEntry(Index);
		// 注意：调用者需要处理RemoveReplicatedSubObject
	}
	else
	{
		// 否则减少指定数量
		Entry.StackCount -= DecreaseCount;
		MarkItemDirty(Entry);
		BroadcastChangeMessage(Entry, Index, OldCount, Entry.StackCount);
	}
	return Entry.StackCount;
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

FCommonInventoryEntry& FCommonInventoryList::GetEntry(int32 Index)
{
	check(Entries.IsValidIndex(Index));
	return Entries[Index];
}

int32 FCommonInventoryList::GetIndexForItemInstance(UCommonInventoryItemInstance* Instance) const
{
	for (int32 Index = 0; Index < Entries.Num(); ++Index)
	{
		if (Entries[Index].Instance == Instance)
		{
			return Index;
		}
	}
	UE_LOG(LogCommonKit, Warning, TEXT("Inventory GetIndexForItemInstance Failed"))
	return INDEX_NONE; 
}

void FCommonInventoryList::BroadcastChangeMessage(FCommonInventoryEntry& Entry,int32 Index,int32 OldCount, int32 NewCount)
{
	FCommonInventoryChangeMessage Message;
	Message.InventoryManager = OwnerComponent;
	Message.Instance = Entry.Instance;
	Message.NewCount = NewCount;
	Message.Delta = NewCount - OldCount;
	Message.Index=Index;

	UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(OwnerComponent->GetWorld());
	MessageSystem.BroadcastMessage(TAG_Common_Inventory_Message_StackChanged, Message);
}

///////////////////////////////////////////////////

UCommonInventoryManageComponent::UCommonInventoryManageComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), InventoryList(this,InventorySize)
{
	SetIsReplicatedByDefault(true);
	bReplicateUsingRegisteredSubObjectList = true;
}

void UCommonInventoryManageComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, InventoryList);
}

void UCommonInventoryManageComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		if (GetOwner()->HasAuthority())
		{
			InventoryList = FCommonInventoryList(this, InventorySize);
			for (int32 i = 0; i < InventoryList.ListMaxSize; ++i)
			{
				InventoryList.Entries.AddDefaulted(); 
				FCommonInventoryEntry& NewEntry= InventoryList.Entries[i];

				NewEntry.Instance = NewObject<UCommonInventoryItemInstance>(GetOwner());
				NewEntry.StackCount = 0;

				InventoryList.MarkItemDirty(NewEntry);

				if (IsUsingRegisteredSubObjectList() && IsReadyForReplication() && NewEntry.Instance)
				{
					AddReplicatedSubObject(NewEntry.Instance);
				}
			}
		}
		InventoryIntilizeCompleteEvent.Broadcast();
	}
}


UCommonInventoryItemInstance* UCommonInventoryManageComponent::AddItemByDefinition(TSubclassOf<UCommonInventoryItemDefinition> ItemDef, int32 StackCount)
{
	UCommonInventoryItemInstance* Result = nullptr;
	if (ItemDef != nullptr)
	{
		Result = InventoryList.AddEntry(ItemDef, StackCount);
	}
	return Result;
}

void UCommonInventoryManageComponent::RemoveItem(int32 Index)
{
	UCommonInventoryItemInstance* ItemInstance=InventoryList.ClearEntry(Index);

	if (ItemInstance && IsUsingRegisteredSubObjectList())
	{
		RemoveReplicatedSubObject(ItemInstance);
	}
}

int32 UCommonInventoryManageComponent::DecreaseItem(int32 Index, int32 DecreaseCount)
{
	if (Index >= 0 && Index < InventoryList.Entries.Num() && DecreaseCount > 0)
	{
		FCommonInventoryEntry& Entry = InventoryList.GetEntry(Index);
		if (Entry.Instance != nullptr && Entry.Instance->GetItemDef() != nullptr)
		{
			// 如果物品被完全移除，也需要从复制子对象列表中移除
			if (InventoryList.RemoveEntry(Index, DecreaseCount)== 0)
			{
				if (IsUsingRegisteredSubObjectList())
				{
					RemoveReplicatedSubObject(Entry.Instance);
				}
			}
		}
		return Entry.StackCount;
	}
	return INDEX_NONE;
}

TArray<UCommonInventoryItemInstance*> UCommonInventoryManageComponent::GetAllItems() const
{
	return InventoryList.GetAllItems();
}

UCommonInventoryItemInstance* UCommonInventoryManageComponent::GetItem(int32 Index) const
{
	if (GetAllItems().IsValidIndex(Index))
	{
		GetAllItems()[Index];
	}
	UE_LOG(LogCommonKit, Error, TEXT("Index is not Valid In InventoryList"));
	return nullptr;
}

int32 UCommonInventoryManageComponent::GetIndexForItemInstance(UCommonInventoryItemInstance* Instance) const
{
	return InventoryList.GetIndexForItemInstance(Instance);
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

AController* UCommonInventoryManageComponent::GetOwnerAsController() const
{
	return Cast<AController>(GetOwner());
}
