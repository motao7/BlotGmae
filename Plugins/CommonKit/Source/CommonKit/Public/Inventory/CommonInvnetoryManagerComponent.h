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

	UPROPERTY(BlueprintReadOnly, Category=Inventory)
	int32 Index = 0;
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
	friend UCommonInventoryItemInstance;

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
		, ListMaxSize(-1)
	{
	}

	FCommonInventoryList(UActorComponent* InOwnerComponent,int32 MaxSize);

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
	
	/**Only friend UCommonInventoryManageComponent can modity Entries*/
protected:
	/**Actully Create a Instance,this Instance only is data that not exist in the game world*/
	UCommonInventoryItemInstance* AddEntry(TSubclassOf<UCommonInventoryItemDefinition> ItemDef, int32 StackCount);

	/**Return remain StackCount*/
	UCommonInventoryItemInstance* ClearEntry(int32 Index);
	int32 RemoveEntry(int32 Index, int32 DecreaseCount);
	
	TArray<UCommonInventoryItemInstance*> GetAllItems() const;
	FCommonInventoryEntry& GetEntry(int32 Index);
	int32 GetIndexForItemInstance(UCommonInventoryItemInstance* Instance) const;

private:
	friend UCommonInventoryManageComponent;

	void BroadcastChangeMessage(FCommonInventoryEntry& Entry,int32 Index,int32 OldCount, int32 NewCount);
	
	// Replicated list of items
	UPROPERTY()
	TArray<FCommonInventoryEntry> Entries;

	UPROPERTY(NotReplicated)
	TObjectPtr<UActorComponent> OwnerComponent;

	UPROPERTY(NotReplicated)
	int32 ListMaxSize;

};
template<>
struct TStructOpsTypeTraits<FCommonInventoryList> : public TStructOpsTypeTraitsBase2<FCommonInventoryList>
{
	enum { WithNetDeltaSerializer = true };
};

DECLARE_MULTICAST_DELEGATE(FInventoryIntilizeCompleteEvent)

/**
 *		Maintain InventoryList.
 *		Manage InventoryItemInstance support Add/Remove Item.....
 *		Actors that storage information can owned this.
 *		This only for fixed size
 */
UCLASS(Blueprintable,BlueprintType,Abstract,Config=Game)
class COMMONKIT_API UCommonInventoryManageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCommonInventoryManageComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Inventory)
	virtual UCommonInventoryItemInstance* AddItemByDefinition(TSubclassOf<UCommonInventoryItemDefinition> ItemDef, int32 StackCount = 1);
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Inventory)
	void RemoveItem(int32 Index);

	/**Return remain StackCount*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Inventory)
	int32 DecreaseItem(int32 Index,int32 DecreaseCount);

	UFUNCTION(BlueprintCallable, Category=Inventory, BlueprintPure=false)
	TArray<UCommonInventoryItemInstance*> GetAllItems() const;

	UFUNCTION(BlueprintCallable, Category=Inventory, BlueprintPure=false)
	UCommonInventoryItemInstance* GetItem(int32 Index) const;

	UFUNCTION(BlueprintCallable, Category=Inventory, BlueprintPure=false)
	int32 GetIndexForItemInstance(UCommonInventoryItemInstance* Instance) const;
	
	UFUNCTION(BlueprintCallable, Category=Inventory, BlueprintPure)
	UCommonInventoryItemInstance* FindFirstItemStackByDefinition(TSubclassOf<UCommonInventoryItemDefinition> ItemDef) const;

	UFUNCTION(BlueprintCallable, Category=Inventory, BlueprintPure)
	AController* GetOwnerAsController() const;

	UFUNCTION(BlueprintCallable, Category=Inventory, BlueprintPure=false)
	virtual void ExchangeItems(int32 Index1, int32 Index2);

	FInventoryIntilizeCompleteEvent InventoryIntilizeCompleteEvent;
private:
	/**Limit the size of InventoryList,facilitate the operation of the list view*/
	UPROPERTY(EditDefaultsOnly, Category=Inventory)
	int32 InventorySize;
	
	UPROPERTY(Replicated)
	FCommonInventoryList InventoryList;
};
