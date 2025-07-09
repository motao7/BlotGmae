// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ControllerComponent.h"
#include "CommonWeaponStateComponent.generated.h"

/**
 *		Tracks weapon state and recent confirmed hit markers to display on screen
 */
UCLASS()
class COMMONKIT_API UCommonWeaponStateComponent : public UControllerComponent
{	
	GENERATED_BODY()

public:
	double GetTimeSinceLastHitNotification() const;
	void UpdateDamageInstigatedTime();

	void GetLastWeaponDamageScreenLocations(TArray<FVector2D>& WeaponDamageScreenLocations)
	{
		WeaponDamageScreenLocations = LastWeaponDamageScreenLocations;
	}

	void AddLastWeaponDamageScreenLocations(const TArray<FHitResult>& FoundHits);

protected:
private:
	TArray<FVector2D> LastWeaponDamageScreenLocations;

	double LastWeaponDamageInstigatedTime = 0.0;

};
