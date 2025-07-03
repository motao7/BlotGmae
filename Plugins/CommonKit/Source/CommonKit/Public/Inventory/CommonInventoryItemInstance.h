// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CommonInventoryItemInstance.generated.h"

class UCommonInventoryItemFragment;
class UCommonInventoryItemDefinition;
/**
 *		Instance base on InventoryDefinaton
 *		Instance only is data! that maintain by ManagerComponent,it is not exist in game world.
 */
UCLASS(BlueprintType)
class COMMONKIT_API UCommonInventoryItemInstance : public UObject
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	//~UObject interface
	virtual bool IsSupportedForNetworking() const override { return true; }
	//~End of UObject interface
	
	TSubclassOf<UCommonInventoryItemDefinition> GetItemDef() const{return ItemDef;}

	void SetItemDef(TSubclassOf<UCommonInventoryItemDefinition> InDef){ItemDef = InDef;}

	bool IsDefaultItem();
	
	UFUNCTION(BlueprintCallable, BlueprintPure=false, meta=(DeterminesOutputType=FragmentClass))
	const UCommonInventoryItemFragment* FindFragmentByClass(TSubclassOf<UCommonInventoryItemFragment> FragmentClass) const;

	template <typename ResultClass>
	const ResultClass* FindFragmentByClass() const
	{
		return (ResultClass*)FindFragmentByClass(ResultClass::StaticClass());
	}
	
private:
	UPROPERTY(Replicated)
	TSubclassOf<UCommonInventoryItemDefinition> ItemDef;
};
