// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/CommonWeaponUserWidget.h"

#include "Equipment/CommonEquipmentManagerComponent.h"
#include "Weapon/CommonWeaponInstance.h"


void UCommonWeaponUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (APawn* Pawn = GetOwningPlayerPawn())
	{
		if (UCommonEquipmentManagerComponent* EquipmentManager = Pawn->FindComponentByClass<UCommonEquipmentManagerComponent>())
		{
			if (UCommonWeaponInstance* NewInstance = EquipmentManager->GetFirstInstanceOfType<UCommonWeaponInstance>())
			{
				if (NewInstance != CurrentInstance && NewInstance->GetInstigator() != nullptr)
				{
					UCommonWeaponInstance* OldWeapon = CurrentInstance;
					CurrentInstance = NewInstance;
					OnWeaponChanged(OldWeapon, CurrentInstance);
				}
			}
		}
	}
}
