// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/CommonWeaponUserWidget.h"

#include "Equipment/CommonEquipmentManagerComponent.h"
#include "Weapon/CommonWeaponInstance.h"


void UCommonEquipmentUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (APawn* Pawn = GetOwningPlayerPawn())
	{
		if (UCommonEquipmentManagerComponent* EquipmentManager = Pawn->FindComponentByClass<UCommonEquipmentManagerComponent>())
		{
			if (UCommonEquipmentInstance* NewInstance = EquipmentManager->GetFirstInstanceOfType<UCommonEquipmentInstance>())
			{
				if (NewInstance != CurrentInstance && NewInstance->GetInstigator() != nullptr)
				{
					UCommonEquipmentInstance* OldEquipment = CurrentInstance;
					CurrentInstance = NewInstance;
					OnEquipmentChanged(OldEquipment, CurrentInstance);
				}
			}
		}
	}
}
