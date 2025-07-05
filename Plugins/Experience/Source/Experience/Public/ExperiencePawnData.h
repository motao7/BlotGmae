// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonCameraMode.h"
#include "TagInputConfig.h"
#include "Engine/DataAsset.h"
#include "ExperiencePawnData.generated.h"

class UExperienceAbilitySet;
class UInputMappingContext;
class UTagInputConfig;
class AModularCharacter;

USTRUCT()
struct FInputMappingContextAndPriority
{
	GENERATED_BODY()

	//这里的意思是只对InputMapping进行软引用?真正加载需要addInputMapping进行加载是吗?
	UPROPERTY(EditAnywhere, Category="Input", meta=(AssetBundles="Client,Server"))
	TSoftObjectPtr<UInputMappingContext> InputMapping;

	// Higher priority input mappings will be prioritized over mappings with a lower priority.
	UPROPERTY(EditAnywhere, Category="Input")
	int32 Priority = 0;
};

/**
 *		
 */
UCLASS(BlueprintType,Const)
class EXPERIENCE_API UExperiencePawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UExperiencePawnData(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere,Category="Pawn")
	TSubclassOf<APawn> PawnClass;

	UPROPERTY(EditAnywhere,Category="Camera")
	TSubclassOf<UCommonCameraMode> DefaultCameraMode;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UTagInputConfig> InputConfig;

	UPROPERTY(EditAnywhere,Category="Input")
	TArray<FInputMappingContextAndPriority> InputMappingAndPrioritys;

	// Ability sets to grant to this pawn's ability system.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<TObjectPtr<UExperienceAbilitySet>> AbilitySets;
};
