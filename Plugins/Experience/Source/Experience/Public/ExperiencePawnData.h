// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ExperiencePawnData.generated.h"

class AModularCharacter;
/**
 * 
 */
UCLASS(BlueprintType,Const)
class EXPERIENCE_API UExperiencePawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UExperiencePawnData(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(EditAnywhere,Category="Pawn")
	TSubclassOf<APawn> PawnClass;
	
};
