// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/CommonWeaponInstance.h"
#include "CommonCollectInstance.generated.h"

UENUM(BlueprintType)
enum class ECollectType : uint8
{
	None         UMETA(DisplayName = "None"),
	Dirt         UMETA(DisplayName = "Dirt"),
	Stone        UMETA(DisplayName = "Stone"),
	Wood         UMETA(DisplayName = "Wood"),
	MetalOre     UMETA(DisplayName = "Metal Ore"),
	Sand         UMETA(DisplayName = "Sand"),
	Gravel       UMETA(DisplayName = "Gravel"),
	Plant        UMETA(DisplayName = "Plant"),
	WaterPlant   UMETA(DisplayName = "Water Plant"),
	Ice          UMETA(DisplayName = "Ice"),
	Obsidian     UMETA(DisplayName = "Obsidian"),
	Crystal      UMETA(DisplayName = "Crystal"),
};

/**
 * 
 */
UCLASS(Blueprintable,Abstract)
class COMMONKIT_API UCommonCollectInstance : public UCommonWeaponInstance
{
	GENERATED_BODY()

public:
	bool CanCollect(ECollectType Type) const{return EffectiveTypes.Contains(Type);}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CollectSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<ECollectType> EffectiveTypes;

};
