// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/CommonQuickBarComponent.h"

#include "Equipment/CommonEquipmentDefinition.h"
#include "Equipment/CommonEquipmentManagerComponent.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Inventory/CIF_EquippableItem.h"
#include "Inventory/CommonInventoryItemInstance.h"
#include "NativeGameplayTags.h"
#include "Equipment/CommonEquipmentInstance.h"
#include "GameFramework/Character.h"
#include "Inventory/CommonInventoryItemDefinition.h"
#include "Inventory/CommonInvnetoryManagerComponent.h"
#include "Net/UnrealNetwork.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_Common_QuickBar_Message_SlotsChanged, "Common.QuickBar.Message.SlotsChanged");
UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_Common_QuickBar_Message_ActiveIndexChanged, "Common.QuickBar.Message.ActiveIndexChanged");

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
	DOREPLIFETIME(ThisClass, EquippedInstance);
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
		if (Slots[SlotIndex]==nullptr)
		{
			Slots[SlotIndex] = Item;
			//Only server excute AddItemToSlot,Call OnRep_Slots() is for the player in listen server
			OnRep_Slots();
		}
	}
}

UCommonInventoryItemInstance* UCommonQuickBarComponent::GetActiveSlotItem() const
{
	return Slots.IsValidIndex(ActiveSlotIndex) ? Slots[ActiveSlotIndex] : nullptr;
}

int32 UCommonQuickBarComponent::GetNextFreeItemSlot() const
{
	int32 SlotIndex = 0;
	for (const TObjectPtr<UCommonInventoryItemInstance>& ItemPtr : Slots)
	{
		if (ItemPtr==nullptr)
		{
			return SlotIndex;
		}
		++SlotIndex;	
	}

	return INDEX_NONE;
}

const UCommonEquipmentInstance* UCommonQuickBarComponent::GetEquippedInstance() const
{
	return EquippedInstance;
}

void UCommonQuickBarComponent::UnequipItemInSlot()
{
	if (UCommonEquipmentManagerComponent* EquipmentManager = FindEquipmentManager())
	{
		if (EquippedInstance != nullptr)
		{
			EquipmentManager->UnequipItem(EquippedInstance);
			EquippedInstance = nullptr;
		}
	}
}

void UCommonQuickBarComponent::EquipItemInSlot()
{
	check(Slots.IsValidIndex(ActiveSlotIndex));
	check(EquippedInstance == nullptr);

	if (UCommonInventoryItemInstance* SlotItem = Slots[ActiveSlotIndex])
	{
		if (const UCIF_EquippableItem* EquipInfo = SlotItem->FindFragmentByClass<UCIF_EquippableItem>())
		{
			TSubclassOf<UCommonEquipmentDefinition> EquipDef = EquipInfo->EquipmentDefinition;
			if (EquipDef != nullptr)
			{
				if (UCommonEquipmentManagerComponent* EquipmentManager = FindEquipmentManager())
				{
					EquippedInstance = EquipmentManager->EquipItem(EquipDef);
					if (EquippedInstance != nullptr)
					{
						EquippedInstance->SetInstigator(SlotItem);
					}
				}
			}
		}
	}
}

void UCommonQuickBarComponent::OnRep_Slots()
{
	FCommonQuickBarSlotsChangedMessage Message;
	Message.Owner = GetOwner();
	Message.Slots = Slots;

	UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(this);
	MessageSystem.BroadcastMessage(TAG_Common_QuickBar_Message_SlotsChanged, Message);
}

void UCommonQuickBarComponent::OnRep_ActiveSlotIndex()
{
	FCommonQuickBarActiveIndexChangedMessage Message;
	Message.Owner = GetOwner();
	Message.ActiveIndex = ActiveSlotIndex;

	UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(this);
	MessageSystem.BroadcastMessage(TAG_Common_QuickBar_Message_ActiveIndexChanged, Message);
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

void UCommonQuickBarComponent::SetActiveSlotIndex_Implementation(int32 Index)
{
	if (Slots.IsValidIndex(Index))
	{
		UnequipItemInSlot();

		ActiveSlotIndex = Index;
		
		EquipItemInSlot();

		OnRep_ActiveSlotIndex();
		
	}
}
