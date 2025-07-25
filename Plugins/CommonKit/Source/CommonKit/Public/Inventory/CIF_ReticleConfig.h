// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/CommonInventoryItemFragment.h"
#include "CIF_ReticleConfig.generated.h"


class UCommonUserWidget;
/**
 * 
 */
UCLASS()
class COMMONKIT_API UCIF_ReticleConfig : public UCommonInventoryItemFragment
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Reticle)
	TArray<TSubclassOf<UCommonUserWidget>> ReticleWidgets;
};
