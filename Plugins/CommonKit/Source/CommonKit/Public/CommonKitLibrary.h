// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CommonKitLibrary.generated.h"

class UCommonWeaponInstance;
/**
 * 
 */
UCLASS()
class COMMONKIT_API UCommonKitLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="KitLibrary")
	static AActor* GetEquipetCommonWeaponInstance(APawn* Pawn);
};
