// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/CommonInventoryItemFragment.h"
#include "GameplayTagContainer.h"
#include "CIF_SetStats.generated.h"

/**
 * 
 */
UCLASS()
class COMMONKIT_API UCIF_SetStats : public UCommonInventoryItemFragment
{
	GENERATED_BODY()
	
public:
	virtual void OnInstanceCreated(UCommonInventoryItemInstance* Instance) const override;

	int32 GetItemStatByTag(FGameplayTag Tag) const;	

protected:
	UPROPERTY(EditDefaultsOnly, Category=Equipment)
	TMap<FGameplayTag, int32> InitialItemStats;

	
};
