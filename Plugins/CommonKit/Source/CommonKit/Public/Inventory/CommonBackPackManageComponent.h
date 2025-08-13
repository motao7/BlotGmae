// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/CommonInvnetoryManagerComponent.h"
#include "CommonBackPackManageComponent.generated.h"

/**
 *		Generally for player
 */
UCLASS()
class COMMONKIT_API UCommonBackPackManageComponent : public UCommonInventoryManageComponent
{
	GENERATED_BODY()
	
public:
	virtual UCommonInventoryItemInstance* AddItemByDefinition(TSubclassOf<UCommonInventoryItemDefinition> ItemDef, int32 StackCount = 1) override;

	virtual void ExchangeItems(int32 Index1, int32 Index2) override;
};
