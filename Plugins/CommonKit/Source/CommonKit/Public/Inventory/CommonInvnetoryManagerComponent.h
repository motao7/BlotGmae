// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "CommonInvnetoryManagerComponent.generated.h"

class UCommonInventoryItemDefinition;
class UCommonInventoryItemInstance;
class UCommonInventoryManageComponent;
struct FCommonInventoryList;

namespace Inventory
{
	constexpr int32 InventorySize = 36;
}

/** A message when an item is added to the inventory */
USTRUCT(BlueprintType)
struct FCommonInventoryChangeMessage
{
	GENERATED_BODY()
	
	//@TODO: Tag based names+owning actors for inventories instead of directly exposing the component?
	UPROPERTY(BlueprintReadOnly, Category=Inventory)
	TObjectPtr<UActorComponent> InventoryManager = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = Inventory)
	TObjectPtr<UCommonInventoryItemInstance> Instance = nullptr;

	UPROPERTY(BlueprintReadOnly, Category=Inventory)
	int32 NewCount = 0;

	UPROPERTY(BlueprintReadOnly, Category=Inventory)
	int32 Delta = 0;
};

/** A single entry in an inventory */
USTRUCT(BlueprintType)
struct FCommonInventoryEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()

public:
	FCommonInventoryEntry(){}

private:
	friend FCommonInventoryList;
	friend UCommonInventoryManageComponent;

	UPROPERTY()
	TObjectPtr<UCommonInventoryItemInstance> Instance = nullptr;

	/**The Count of Instance*/
	UPROPERTY()
	int32 StackCount = 0;

	/**Last Client observe the Count of Instance*/
	UPROPERTY(NotReplicated)
	int32 LastObservedCount = INDEX_NONE;
};

/** List of inventory items */
USTRUCT(BlueprintType)
struct FCommonInventoryList : public FFastArraySerializer
{
	GENERATED_BODY()
public:
	FCommonInventoryList()
		: OwnerComponent(nullptr)
	{
	}

	FCommonInventoryList(UActorComponent* InOwnerComponent)
		: OwnerComponent(InOwnerComponent)
	{
	}
	
	//~FFastArraySerializer contract
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);
	void PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize);
	//~End of FFastArraySerializer contract

	/**Must write,the reason is in FFastArraySerializer’s begin*/
	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FCommonInventoryEntry, FCommonInventoryList>(Entries, DeltaParms, *this);
	}

	/**Actully Create a Instance,this Instance only is data that not exist in the game world*/
	UCommonInventoryItemInstance* AddEntry(TSubclassOf<UCommonInventoryItemDefinition> ItemDef, int32 StackCount);
	void AddEntry(UCommonInventoryItemInstance* Instance);
	void RemoveEntry(UCommonInventoryItemInstance* Instance);
	TArray<UCommonInventoryItemInstance*> GetAllItems() const;

private:
	friend UCommonInventoryManageComponent;

	void BroadcastChangeMessage(FCommonInventoryEntry& Entry, int32 OldCount, int32 NewCount);
	
	// Replicated list of items
	UPROPERTY()
	TArray<FCommonInventoryEntry> Entries;

	UPROPERTY(NotReplicated)
	TObjectPtr<UActorComponent> OwnerComponent;
};
template<>
struct TStructOpsTypeTraits<FCommonInventoryList> : public TStructOpsTypeTraitsBase2<FCommonInventoryList>
{
	enum { WithNetDeltaSerializer = true };
};



/**
 *		Maintain InventoryList.
 *		Manage InventoryItemInstance support Add/Remove Item.....
 */
UCLASS(BlueprintType,Config=Game)
class COMMONKIT_API UCommonInventoryManageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCommonInventoryManageComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Inventory)
	UCommonInventoryItemInstance* AddItemByDefinition(TSubclassOf<UCommonInventoryItemDefinition> ItemDef, int32 StackCount = 1);
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Inventory)
	void RemoveItemByInstance(UCommonInventoryItemInstance* ItemInstance);

	UFUNCTION(BlueprintCallable, Category=Inventory, BlueprintPure=false)
	TArray<UCommonInventoryItemInstance*> GetAllItems() const;

	UFUNCTION(BlueprintCallable, Category=Inventory, BlueprintPure)
	UCommonInventoryItemInstance* FindFirstItemStackByDefinition(TSubclassOf<UCommonInventoryItemDefinition> ItemDef) const;

private:
	UPROPERTY(Replicated)
	FCommonInventoryList InventoryList;
};
