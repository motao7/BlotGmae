// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonGameInstance.h"
#include "Engine/GameInstance.h"
#include "BlotGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BLOTGAME_API UBlotGameInstance : public UCommonGameInstance
{
	GENERATED_BODY()

public:

protected:
	virtual void Init() override;
};
