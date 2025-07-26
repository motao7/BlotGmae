// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonKitStatics.h"

#include "Inventory/CommonInvnetoryManagerComponent.h"
#include "Equipment/CommonQuickBarComponent.h"
#include "Equipment/CommonEquipmentInstance.h"
#include "Equipment/CommonEquipmentManagerComponent.h"

AActor* UCommonKitStatics::GetEquippedInstanceSpawnedActor(APawn* Pawn)
{
	if (Pawn==nullptr) return nullptr;
	
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

UCommonInventoryManageComponent* UCommonKitStatics::GetInventoryManager(APawn* Pawn)
{
	if (Pawn==nullptr) return nullptr;
	
	if (APlayerController* PC=Cast<APlayerController>(Pawn->GetController()))
	{
		return PC->GetComponentByClass<UCommonInventoryManageComponent>();
	}
	return nullptr;
}

UCommonQuickBarComponent* UCommonKitStatics::GetQuickBarManagerFromPawn(APawn* Pawn)
{
	if (Pawn==nullptr) return nullptr;
	
	if (APlayerController* PC=Cast<APlayerController>(Pawn->GetController()))
	{
		return PC->GetComponentByClass<UCommonQuickBarComponent>();
	}
	return nullptr;
}

UCommonQuickBarComponent* UCommonKitStatics::GetQuickBarManagerFromController(AController* Controller)
{
	if (Controller==nullptr) return nullptr;
	
	return Controller->GetComponentByClass<UCommonQuickBarComponent>();
}

UCommonEquipmentManagerComponent* UCommonKitStatics::GetEquipmentManager(APawn* Pawn)
{
	if (Pawn)
	{
		return Pawn->GetComponentByClass<UCommonEquipmentManagerComponent>();
	}
	return nullptr;
}

