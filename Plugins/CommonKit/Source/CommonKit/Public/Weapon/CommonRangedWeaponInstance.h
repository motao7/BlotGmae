// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/CommonWeaponInstance.h"
#include "CommonRangedWeaponInstance.generated.h"

/**
 * 
 */
UCLASS()
class COMMONKIT_API UCommonRangedWeaponInstance : public UCommonWeaponInstance
{
	GENERATED_BODY()

public:
	float GetMaxDamageRange() const
	{
		return MaxDamageRange;
	}
	int32 GetBulletsPerCartridge() const
	{
		return BulletsPerCartridge;
	}
	
protected:
	// Number of bullets to fire in a single cartridge (typically 1, but may be more for shotguns)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon Config")
	int32 BulletsPerCartridge = 1;

	// The maximum distance at which this weapon can deal damage
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon Config", meta=(ForceUnits=cm))
	float MaxDamageRange = 25000.0f;
};
