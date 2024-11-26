// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExperienceActionSet.generated.h"

class UGameFeatureAction;
/**
 * 
 */
UCLASS(BlueprintType,Const)
class EXPERIENCE_API UExperienceActionSet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly,Category="Action")
	TArray<TObjectPtr<UGameFeatureAction>> Actions;
};
