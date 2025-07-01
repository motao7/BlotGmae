// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/CommonEquipmentInstance.h"
#include "CommonWeaponInstance.generated.h"

/**
 * 
 */
UCLASS()
class COMMONKIT_API UCommonWeaponInstance : public UCommonEquipmentInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Animation)
	TSubclassOf<UAnimInstance> AnimLayer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Animation)
	UAnimMontage* EquipMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Animation)
	UAnimMontage* UnEquipMontage;
	
};
