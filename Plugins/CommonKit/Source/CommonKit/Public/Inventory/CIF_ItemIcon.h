// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/CommonInventoryItemFragment.h"
#include "CIF_ItemIcon.generated.h"

/**
 *		Matain Item Icon
 */
UCLASS()
class COMMONKIT_API UCIF_ItemIcon : public UCommonInventoryItemFragment
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance)
	FSlateBrush Brush;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance)
	FText DisplayNameWhenEquipped;
};
