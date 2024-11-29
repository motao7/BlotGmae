// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/BlotPlayerController.h"
//报错:没有将“USING_CHEAT_MANAGER”定义为预处理器宏，用“0”替换“#if/#elif”，
//如果你在BlotCheatManager.h文件中定义了你需要在使用该宏的地方添加头文件
#include "BlotCheatManager.h"


ABlotPlayerController::ABlotPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if USING_CHEAT_MANAGER
	CheatClass = UBlotCheatManager::StaticClass();
#endif // #if USING_CHEAT_MANAGER
}

void ABlotPlayerController::AddCheats(bool bForce)
{
#if USING_CHEAT_MANAGER
	Super::AddCheats(true);
#else //#if USING_CHEAT_MANAGER
	Super::AddCheats(bForce);
#endif // #else //#if USING_CHEAT_MANAGER
}
