// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/CommonQuickBarComponent.h"

#include "Equipment/CommonEquipmentDefinition.h"
#include "Equipment/CommonEquipmentInstance.h"
#include "Equipment/CommonEquipmentManagerComponent.h"
#include "Inventory/CIF_EquippableItem.h"
#include "Inventory/CommonInventoryItemInstance.h"
#include "Net/UnrealNetwork.h"


UCommonQuickBarComponent::UCommonQuickBarComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetIsReplicatedByDefault(true);
}

void UCommonQuickBarComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, Slots);
	DOREPLIFETIME(ThisClass, ActiveSlotIndex);
}

void UCommonQuickBarComponent::BeginPlay()
{
	if (Slots.Num() < NumSlots)
	{
		Slots.AddDefaulted(NumSlots - Slots.Num());
	}
	Super::BeginPlay();
}

void UCommonQuickBarComponent::AddItemToSlot(int32 SlotIndex, UCommonInventoryItemInstance* Item)
{
	if (Slots.IsValidIndex(SlotIndex) && (Item != nullptr))
	{
		if (Slots[SlotIndex] == nullptr)
		{
			Slots[SlotIndex] = Item;
		}
	}
}

void UCommonQuickBarComponent::UnequipItemInSlot()
{
	if (UCommonEquipmentManagerComponent* EquipmentManager = FindEquipmentManager())
	{
		if (EquippedItem != nullptr)
		{
			EquipmentManager->UnequipItem(EquippedItem);
			EquippedItem = nullptr;
		}
	}
}

void UCommonQuickBarComponent::EquipItemInSlot()
{
	check(Slots.IsValidIndex(ActiveSlotIndex));
	check(EquippedItem == nullptr);

	if (UCommonInventoryItemInstance* SlotItem = Slots[ActiveSlotIndex])
	{
		if (const UCIF_EquippableItem* EquipInfo = SlotItem->FindFragmentByClass<UCIF_EquippableItem>())
		{
			TSubclassOf<UCommonEquipmentDefinition> EquipDef = EquipInfo->EquipmentDefinition;
			if (EquipDef != nullptr)
			{
				if (UCommonEquipmentManagerComponent* EquipmentManager = FindEquipmentManager())
				{
					EquippedItem = EquipmentManager->EquipItem(EquipDef);
					// if (EquippedItem != nullptr)
					// {
					// 	EquippedItem->SetInstigator(SlotItem);
					// }
				}
			}
		}
	}
}

void UCommonQuickBarComponent::OnRep_Slots()
{
}

void UCommonQuickBarComponent::OnRep_ActiveSlotIndex()
{
}

UCommonEquipmentManagerComponent* UCommonQuickBarComponent::FindEquipmentManager() const
{
	if (AController* OwnerController = Cast<AController>(GetOwner()))
	{
		if (APawn* Pawn = OwnerController->GetPawn())
		{
			return Pawn->FindComponentByClass<UCommonEquipmentManagerComponent>();
		}
	}
	return nullptr;
}

void UCommonQuickBarComponent::SetActiveSlotIndex_Implementation(int32 NewIndex)
{
	if (Slots.IsValidIndex(NewIndex) && (ActiveSlotIndex != NewIndex))
	{
		UnequipItemInSlot();

		ActiveSlotIndex = NewIndex;

		EquipItemInSlot();
	}
}
