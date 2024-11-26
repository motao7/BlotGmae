// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "BlotGameState.generated.h"

class UExperienceManagerComponent;
/**
 * 
 */
UCLASS()
class BLOTGAME_API ABlotGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	ABlotGameState(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY()
	TObjectPtr<UExperienceManagerComponent> ExperienceManagerComponent;
};
