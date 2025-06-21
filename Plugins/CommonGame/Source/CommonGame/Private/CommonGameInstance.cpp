// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonGameInstance.h"

#include "CommonGameUIManagerSubsystem.h"
#include "CommonLocalPlayer.h"

int32 UCommonGameInstance::AddLocalPlayer(ULocalPlayer* NewPlayer, FPlatformUserId UserId)
{
	int32 RetValue=Super::AddLocalPlayer(NewPlayer, UserId);
	if (UCommonGameUIManagerSubsystem* UIManagerSubsystem=GetSubsystem<UCommonGameUIManagerSubsystem>())
	{
		UIManagerSubsystem->NotifyPlayerAdded(Cast<UCommonLocalPlayer>(NewPlayer));
	}
	return RetValue;
}


