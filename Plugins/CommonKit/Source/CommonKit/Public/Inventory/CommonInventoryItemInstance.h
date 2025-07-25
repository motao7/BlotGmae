// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonInvnetoryManagerComponent.h"
#include "GameplayTagStack.h"
#include "CommonInventoryItemInstance.generated.h"

struct FCommonInventoryEntry;
class UCommonInventoryItemFragment;
class UCommonInventoryItemDefinition;
/**
 *		Instance base on InventoryDefinaton
 *		Instance only is data! that maintain by ManagerComponent,it is not exist in game world.
 *		As a bridge between "List view" and "Common Inventory"
 */
UCLASS(BlueprintType)
class COMMONKIT_API UCommonInventoryItemInstance : public UObject
{
	GENERATED_BODY()
public:
	UCommonInventoryItemInstance(const FObjectInitializer& ObjectInitializer);
	void InitializeWithEntry(FCommonInventoryEntry* InEntry);
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	//~UObject interface
	virtual bool IsSupportedForNetworking() const override { return true; }
	//~End of UObject interface
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Inventory)
	void AddStatTagStack(FGameplayTag Tag, int32 StackCount);
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category= Inventory)
	void RemoveStatTagStack(FGameplayTag Tag, int32 StackCount);
	
	UFUNCTION(BlueprintCallable, Category=Inventory)
	int32 GetStatTagStackCount(FGameplayTag Tag) const;
	
	UFUNCTION(BlueprintCallable, Category=Inventory)
	bool HasStatTag(FGameplayTag Tag) const;

	UFUNCTION(BlueprintCallable, BlueprintPure=false, meta=(DeterminesOutputType=FragmentClass), Category=Inventory)
	const UCommonInventoryItemFragment* FindFragmentByClass(TSubclassOf<UCommonInventoryItemFragment> FragmentClass) const;

	UFUNCTION(BlueprintCallable, Category=Inventory)
	TSubclassOf<UCommonInventoryItemDefinition> GetItemDef() const{return ItemDef;}
	
	UFUNCTION(BlueprintCallable, Category=Inventory)
	void SetItemDef(TSubclassOf<UCommonInventoryItemDefinition> InDef){ItemDef = InDef;}

	UFUNCTION(BlueprintCallable, Category=Inventory)
	int32 GetInventoryCount() const;
	
	template <typename ResultClass>
	const ResultClass* FindFragmentByClass() const
	{
		return (ResultClass*)FindFragmentByClass(ResultClass::StaticClass());
	}

	UFUNCTION(BlueprintCallable, Category=Inventory)
	bool IsStackableWith(TSubclassOf<UCommonInventoryItemDefinition> OtherItemDef) const;
	
private:
	friend FCommonInventoryEntry;

	FCommonInventoryEntry* EntryOwnerRef;
	
	UPROPERTY(Replicated)
	FGameplayTagStackContainer StatTags;

	UPROPERTY(Replicated)
	TSubclassOf<UCommonInventoryItemDefinition> ItemDef;
};
