// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/GameMode.h"

#include "ModularGameMode.generated.h"

class UObject;

/**
 * Post login event, triggered when a player or bot joins the game as well as after seamless and non seamless travel
 *
 *	玩家完成初始化(怎么定义初始化完成?->GenericPlayerInitialization()，这个函数完成初始化Player HUD之类的事情)后触发
 */
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGameModePlayerInitialized, AGameModeBase* /*GameMode*/, AController* /*NewPlayer*/);

/** Pair this with a ModularGameStateBase */
UCLASS(Blueprintable)
class MODULARGAMEPLAYACTORS_API AModularGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AModularGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual void GenericPlayerInitialization(AController* C) override;
	/** 玩家加入函数GenericPlayerInitialization完成后调用，即玩家初始化完成后调用 */
	FOnGameModePlayerInitialized OnGameModePlayerInitialized;
};

/** Pair this with a ModularGameState */
UCLASS(Blueprintable)
class MODULARGAMEPLAYACTORS_API AModularGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AModularGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
