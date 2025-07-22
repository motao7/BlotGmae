// Fill out your copyright notice in the Description page of Project Settings.


#include "BlotGameplayStatics.h"


ULocalPlayer* UBlotGameplayStatics::GetLocalPlayerFromController(APlayerController* PlayerController)
{
	if (PlayerController)
	{
		return Cast<ULocalPlayer>(PlayerController->Player);
	}

	return nullptr;
}
