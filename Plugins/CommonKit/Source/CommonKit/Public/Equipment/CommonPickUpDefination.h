// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CommonPickUpDefination.generated.h"

class UCommonInventoryItemDefinition;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class COMMONKIT_API UCommonPickUpDefination : public UDataAsset
{
	GENERATED_BODY()
public:
	//Defines the pickup's actors to spawn, abilities to grant, and tags to add
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CommonKit|Pickup|Equipment")
	TSubclassOf<UCommonInventoryItemDefinition> InventoryItemDefinition;

	//Visual representation of the pickup
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CommonKit|Pickup|Mesh")
	TObjectPtr<UStaticMesh> DisplayMesh;
};

UCLASS(Blueprintable, BlueprintType, Const)
class COMMONKIT_API UCommonWeaponPickupDefinition : public UCommonPickUpDefination
{
	GENERATED_BODY()

public:
	//Sets the height of the display mesh above the Weapon spawner
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CommonKit|Pickup|Mesh")
	FVector WeaponMeshOffset;

	//Sets the height of the display mesh above the Weapon spawner
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CommonKit|Pickup|Mesh")
	FVector WeaponMeshScale = FVector(1.0f, 1.0f, 1.0f);
};
