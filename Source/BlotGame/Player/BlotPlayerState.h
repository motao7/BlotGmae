// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularPlayerState.h"
#include "BlotPlayerState.generated.h"

class UExperiencePawnData;
class UPawnData;
/**
 * 
 */
UCLASS()
class BLOTGAME_API ABlotPlayerState : public AModularPlayerState
{
	GENERATED_BODY()
	
public:
	ABlotPlayerState(const FObjectInitializer& ObjectInitialize);

	//~Helper Function
	//~Helper Function End
protected:
};
