// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BlotCharacterMovementComponent.generated.h"

USTRUCT(BlueprintType)
struct FBlotCharacterGroundInfo
{
	GENERATED_BODY()

	FBlotCharacterGroundInfo()
		: LastUpdateFrame(0)
		, GroundDistance(0.0f)
	{}

	/**Use to avoid repet calculation*/
	uint64 LastUpdateFrame;

	UPROPERTY(BlueprintReadOnly)
	FHitResult GroundHitResult;

	UPROPERTY(BlueprintReadOnly)
	float GroundDistance;
};

/**
 * 
 */
UCLASS()
class BLOTGAME_API UBlotCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY() 

public:
	// Returns the current ground info.  Calling this will update the ground info if it's out of date.(Lazy Evaluation)
	UFUNCTION(BlueprintCallable, Category = "Lyra|CharacterMovement")
	const FBlotCharacterGroundInfo& GetGroundInfo();

protected:
	FBlotCharacterGroundInfo CachedGroundInfo;
};
