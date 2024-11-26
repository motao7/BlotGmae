// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExperiencePawnData.h"
#include "ModularGameMode.h"
#include "BlotGameMode.generated.h"

class UExperienceDefination;
class UExperienceManagerComponent;
class UExperiencePawnData;

/**
 * 
 */
UCLASS()
class BLOTGAME_API ABlotGameMode : public AModularGameModeBase
{
	GENERATED_BODY()

public:
	ABlotGameMode(const FObjectInitializer& ObjectInitializer);

	//~Helper Function
	UFUNCTION(Blueprintable,Category="BlotGameModeFuntion")
	AGameStateBase* GetGameState();
	UFUNCTION(Blueprintable,Category="BlotGameModeFuntion")
	bool IsExperienceLoaded() const;
	UFUNCTION(Blueprintable,Category="BlotGameModeFuntion")
	UExperiencePawnData* GetPawnDataFromPlayerStateOrExperience(const AController* Controller) const;
	//~Helper Function End
	
	//~ GameMode Base  interface
	//HandleStartingNewPlayer_Implementation先于InitGame
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void InitGameState() override;
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;
	//~ GameMode Base  interface End

	/** Call Experience Component To Load Experience */
	void LoadExperience() const;

	/* 调用RestartPlayer函数去生成Pawm , RestartPlayer->pawnDefaultPawnAtTransform */
	void OnExperienceLoaded(const UExperienceDefination* ExperienceDefination);

protected:

};
