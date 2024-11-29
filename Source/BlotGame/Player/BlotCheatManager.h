// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "BlotCheatManager.generated.h"

//用于告诉引擎启动CheatManager
#ifndef USING_CHEAT_MANAGER
#define USING_CHEAT_MANAGER (1 && !UE_BUILD_SHIPPING)
#endif // #ifndef USING_CHEAT_MANAGER

/**
 * 
 */
UCLASS()
class BLOTGAME_API UBlotCheatManager : public UCheatManager
{
	GENERATED_BODY()
	
};
