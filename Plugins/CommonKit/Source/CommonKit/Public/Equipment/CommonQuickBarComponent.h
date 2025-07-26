// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonEquipmentManagerComponent.h"
#include "Components/ControllerComponent.h"
#include "CommonQuickBarComponent.generated.h"

class UCommonEquipmentInstance;
class UCommonInventoryItemInstance;

USTRUCT(BlueprintType)
struct FCommonQuickBarSlotsChangedMessage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category=Inventory)
	TObjectPtr<AActor> Owner = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = Inventory)
	TArray<TObjectPtr<UCommonInventoryItemInstance>> Slots;
};


USTRUCT(BlueprintType)
struct FCommonQuickBarActiveIndexChangedMessage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category=Inventory)
	TObjectPtr<AActor> Owner = nullptr;

	UPROPERTY(BlueprintReadOnly, Category=Inventory)
	int32 ActiveIndex = 0;
};


/**
 *		Manage (QuickBar)Slot so that InventoryItemInstance can insert in correct slot.
 *		Connect InventorySystem and EquipmentSyatem by QuickBar.
 */
UCLASS(Blueprintable,Config=Game)
class COMMONKIT_API UCommonQuickBarComponent : public UControllerComponent
{
	GENERATED_BODY()
public:
	UCommonQuickBarComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void BeginPlay() override;

	/**Only Slot is Default or empty can add*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly,Category="QuickBar")
	void AddItemToSlot(int32 SlotIndex, UCommonInventoryItemInstance* Item);
	
	UFUNCTION(Server, Reliable, BlueprintCallable,Category="QuickBar")
	void SetActiveSlotIndex(int32 Index);

	UFUNCTION( BlueprintCallable,Category="QuickBar")
	bool HasItemInSlots(UCommonInventoryItemInstance* Instance);

	UFUNCTION(BlueprintCallable, BlueprintPure=false,Category="QuickBar")
	int32 GetActiveSlotIndex() const { return ActiveSlotIndex; }

	UFUNCTION(BlueprintCallable, BlueprintPure = false,Category="QuickBar")
	UCommonInventoryItemInstance* GetActiveSlotItem() const;

	UFUNCTION(BlueprintCallable, BlueprintPure=false,Category="QuickBar")
	int32 GetNextFreeItemSlot() const;

	UFUNCTION(BlueprintCallable, BlueprintPure=true,Category="QuickBar")
	const UCommonEquipmentInstance* GetEquippedInstance() const;

protected:
	void UnequipItemInSlot();
	void EquipItemInSlot();

	UFUNCTION()
	void OnRep_Slots();

	UFUNCTION()
	void OnRep_ActiveSlotIndex();
	
	UCommonEquipmentManagerComponent* FindEquipmentManager() const;

	UPROPERTY(BlueprintReadOnly,Category="QuickBar")
	int32 NumSlots = 9;

private:
	UPROPERTY(ReplicatedUsing=OnRep_Slots)
	TArray<TObjectPtr<UCommonInventoryItemInstance>> Slots;
	
	UPROPERTY(ReplicatedUsing=OnRep_ActiveSlotIndex)
	int32 ActiveSlotIndex = -1;

	UPROPERTY(Replicated)
	TObjectPtr<UCommonEquipmentInstance> EquippedInstance;
	
};
