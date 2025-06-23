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
	void SpawnEquipmentActors(const TArray<FCommonEquipmentActorToSpawn>& ActorsToSpawn);

	UFUNCTION(BlueprintPure, Category=Equipment)
	APawn* GetPawn() const;
	void DestroyEquipmentActors();
};
