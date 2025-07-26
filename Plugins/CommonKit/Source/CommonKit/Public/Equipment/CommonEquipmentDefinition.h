// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CommonEquipmentDefinition.generated.h"

class UExperienceAbilitySet;
class UCommonEquipmentInstance;

USTRUCT()
struct FCommonEquipmentActorToSpawn
{
	GENERATED_BODY()

	FCommonEquipmentActorToSpawn(){}

	UPROPERTY(EditAnywhere, Category=Equipment)
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, Category=Equipment)
	FName AttachSocket;

	UPROPERTY(EditAnywhere, Category=Equipment)
	FTransform AttachTransform;
};

/**
 *		Contains general configuration information related to equipment operations
 */
UCLASS(Blueprintable, Const, Abstract, BlueprintType)
class COMMONKIT_API UCommonEquipmentDefinition : public UObject
{
	GENERATED_BODY()
public:
	// Class to spawn
	UPROPERTY(EditDefaultsOnly, Category=Equipment)
	TSubclassOf<UCommonEquipmentInstance> InstanceType;

	// Gameplay ability sets to grant when this is equipped
	UPROPERTY(EditDefaultsOnly, Category=Equipment)
	TArray<TObjectPtr<const UExperienceAbilitySet>> AbilitySetsToGrant;

	// Actors to spawn on the pawn when this is equipped
	UPROPERTY(EditDefaultsOnly, Category=Equipment)
	TArray<FCommonEquipmentActorToSpawn> ActorsToSpawn;
};
