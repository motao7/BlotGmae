// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableTarget.generated.h"


struct FInteractionOption;

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UInteractableTarget : public UInterface
{
	GENERATED_BODY()
};

/**
 *		For those can collect object,when player foucus these actor can grant ability to player 
 */
class IInteractableTarget
{
	GENERATED_BODY()

public:
	virtual void GatherInteractionOptions(TArray<FInteractionOption>& Options) = 0;
};
