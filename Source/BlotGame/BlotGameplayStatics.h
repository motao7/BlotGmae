// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "BlotGameplayStatics.generated.h"

/**
 * 
 */
UCLASS()
class BLOTGAME_API UBlotGameplayStatics : public UGameplayStatics
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "BlotGame")
	static ULocalPlayer* GetLocalPlayerFromController(APlayerController* PlayerController);

};
