// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CommonKitStatics.generated.h"

class UCommonEquipmentManagerComponent;
class UCommonQuickBarComponent;
class UCommonInventoryManageComponent;
class UCommonWeaponInstance;
/**
 * 
 */
UCLASS()
class COMMONKIT_API UCommonKitStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="KitStatics")
	static AActor* GetEquippedInstanceSpawnedActor(APawn* Pawn);

	UFUNCTION(BlueprintCallable, Category="KitStatics")
	static UCommonInventoryManageComponent* GetInventoryManager(APawn* Pawn);

	UFUNCTION(BlueprintCallable, Category="KitStatics")
	static UCommonQuickBarComponent* GetQuickBarManager(APawn* Pawn);

	UFUNCTION(BlueprintCallable, Category="KitStatics")
	static UCommonEquipmentManagerComponent* GetEquipmentManager(APawn* Pawn);
};
