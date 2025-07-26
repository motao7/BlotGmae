// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/CommonInventoryItemFragment.h"
#include "CIF_PlaceableItem.generated.h"

/**
 * 
 */
UCLASS()
class COMMONKIT_API UCIF_PlaceableItem : public UCommonInventoryItemFragment
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Placeable")
	TSubclassOf<AActor> PlaceableActorClass;

	/**May make it a global variable? */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Placeable")
	float PlacementDistance = 400.0f;
	
};
