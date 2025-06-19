// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularPlayerController.h"
#include "BlotPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BLOTGAME_API ABlotPlayerController : public AModularPlayerController
{
	GENERATED_BODY()

public:
	ABlotPlayerController(const FObjectInitializer& ObjectInitializer);
	
	//~ PlayerControoler 
	virtual void AddCheats(bool bForce) override;
	virtual void PostProcessInput(float DeltaTime, bool bGamePaused) override;
	//~ PlayerControoler End
	
};
