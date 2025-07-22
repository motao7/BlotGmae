// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFeatureAction.h"
#include "Engine/DataAsset.h"
#include "ExperienceDefinition.generated.h"

class UExperiencePawnData;
class UExperienceActionSet;
/**
 *		包含基本的Experience需要加载的东西---指针为TObjectPtr，到要加载ExperienceDefination的阶段就全部加载进来
 */
UCLASS(BlueprintType,Const)
class EXPERIENCE_API UExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,Category="URL")
	TArray<FString> GameFeatureToEnable;
	
	UPROPERTY(EditAnywhere,Category="PawnData")
	TObjectPtr<UExperiencePawnData> DefaultPawnData;
	
	UPROPERTY(EditDefaultsOnly, Category="Action")
	TArray<TObjectPtr<UExperienceActionSet>> ActionSets;
	
	UPROPERTY(EditDefaultsOnly, Category="Actions")
	TArray<TObjectPtr<UGameFeatureAction>> Actions;
};
