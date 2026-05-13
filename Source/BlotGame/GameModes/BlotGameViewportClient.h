// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonGameViewportClient.h"
#include "BlotGameViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class BLOTGAME_API UBlotGameViewportClient : public UCommonGameViewportClient
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

private:
	TWeakObjectPtr<APlayerController> CachedPC;
};
