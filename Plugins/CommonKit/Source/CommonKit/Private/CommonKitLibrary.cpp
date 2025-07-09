// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonKitLibrary.h"

#include "Equipment/CommonEquipmentInstance.h"
#include "Equipment/CommonEquipmentManagerComponent.h"


AActor* UCommonKitLibrary::GetEquipetCommonWeaponInstance(APawn* Pawn)
{
	if (UCommonEquipmentManagerComponent* EquipManagerComp=Pawn->FindComponentByClass<UCommonEquipmentManagerComponent>())
	{
		if (UCommonEquipmentInstance* EquipInstance=EquipManagerComp->GetFirstInstanceOfType(UCommonEquipmentInstance::StaticClass()))
		{
			TArray<AActor*> Actors=EquipInstance->GetSpawnedActors();
			if (Actors.Num()>0)
			{
				return Actors.Last();
			}
		}
	}
	return nullptr;
}
