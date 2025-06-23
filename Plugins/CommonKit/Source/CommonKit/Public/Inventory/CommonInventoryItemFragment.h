// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CommonInventoryItemFragment.generated.h"

class UCommonInventoryItemInstance;
/**
 *		Represents a fragment of an InventoryItemDefinition
 */
UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class COMMONKIT_API UCommonInventoryItemFragment : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void OnInstanceCreated(UCommonInventoryItemInstance* Instance) const {}
	
};
