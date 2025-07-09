// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "CommonWeaponInstance.h"
#include "CommonWeaponUserWidget.generated.h"

/**
 *		Can check if WeaponChanged in tick
 */
UCLASS()
class COMMONKIT_API UCommonWeaponUserWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnWeaponChanged(UCommonWeaponInstance* OldWeapon, UCommonWeaponInstance* NewWeapon);

private:
	UPROPERTY(Transient)
	TObjectPtr<UCommonWeaponInstance> CurrentInstance;
	
};
