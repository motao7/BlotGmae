// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonEquipmentManagerComponent.h"
#include "Components/ControllerComponent.h"
#include "CommonQuickBarComponent.generated.h"

class UCommonEquipmentInstance;
class UCommonInventoryItemInstance;

/**
 *		Manage (QuickBar)Slot so that InventoryItemInstance can insert in correct slot
 */
UCLASS(Blueprintable)
class COMMONKIT_API UCommonQuickBarComponent : public UControllerComponent
{
	GENERATED_BODY()
public:
	UCommonQuickBarComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void AddItemToSlot(int32 SlotIndex, UCommonInventoryItemInstance* Item);
	
	UFUNCTION(Server, Reliable, BlueprintCallable, Category="Lyra")
	void SetActiveSlotIndex(int32 NewIndex);

protected:
	void UnequipItemInSlot();
	void EquipItemInSlot();

	UFUNCTION()
	void OnRep_Slots();
	UFUNCTION()
	void OnRep_ActiveSlotIndex();
	
	UCommonEquipmentManagerComponent* FindEquipmentManager() const;

	UPROPERTY()
	int32 NumSlots = 3;

private:
	UPROPERTY(ReplicatedUsing=OnRep_Slots)
	TArray<TObjectPtr<UCommonInventoryItemInstance>> Slots;

	UPROPERTY(ReplicatedUsing=OnRep_ActiveSlotIndex)
	int32 ActiveSlotIndex = -1;

	UPROPERTY()
	TObjectPtr<UCommonEquipmentInstance> EquippedItem;
};
