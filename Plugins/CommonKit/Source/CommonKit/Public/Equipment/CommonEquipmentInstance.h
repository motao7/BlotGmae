// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CommonEquipmentInstance.generated.h"

struct FCommonEquipmentActorToSpawn;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class COMMONKIT_API UCommonEquipmentInstance : public UObject
{
	GENERATED_BODY()
public:
	//~UObject interface
	virtual bool IsSupportedForNetworking() const override { return true; }
	//~End of UObject interface
	
	void SpawnEquipmentActors(const TArray<FCommonEquipmentActorToSpawn>& ActorsToSpawn);

	virtual void OnEquipped();
	virtual void OnUnequipped();
	UFUNCTION(BlueprintImplementableEvent, Category=Equipment, meta=(DisplayName="OnEquipped"))
	void K2_OnEquipped();
	UFUNCTION(BlueprintImplementableEvent, Category=Equipment, meta=(DisplayName="OnUnequipped"))
	void K2_OnUnequipped();
	
	UFUNCTION(BlueprintPure, Category=Equipment)
	APawn* GetOuterPawn() const;
	
	void DestroyEquipmentActors();
};
