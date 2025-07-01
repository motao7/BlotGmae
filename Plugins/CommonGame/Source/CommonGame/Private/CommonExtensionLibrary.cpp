// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonExtensionLibrary.h"

#include "CommonActivatableWidget.h"
#include "CommonGame.h"
#include "CommonGameUIManagerSubsystem.h"
#include "CommonGameUIPolicy.h"
#include "CommonLocalPlayer.h"
#include "CommonPrimaryGameLayout.h"


UCommonActivatableWidget* UCommonExtensionLibrary::PushContentToLayer_ForPlayer(const ULocalPlayer* LocalPlayer, FGameplayTag LayerName, TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	if (!ensure(LocalPlayer) || !ensure(WidgetClass != nullptr))
	{
		return nullptr;
	}

	if (!LocalPlayer)
	{
		UE_LOG(LogCommonUserInterface, Warning, TEXT("LocalPlayer is null."));
		return nullptr;
	}

	UCommonGameUIManagerSubsystem* UIManager = LocalPlayer->GetGameInstance()->GetSubsystem<UCommonGameUIManagerSubsystem>();
	if (!UIManager)
	{
		UE_LOG(LogCommonUserInterface, Warning, TEXT("Failed to get CommonGameUIManagerSubsystem from GameInstance."));
		return nullptr;
	}

	UCommonGameUIPolicy* Policy = UIManager->GetCurrentUIPolicy();
	if (!Policy)
	{
		UE_LOG(LogCommonUserInterface, Warning, TEXT("Failed to get current UI policy from UI manager."));
		return nullptr;
	}

	const UCommonLocalPlayer* CommonLocalPlayer = Cast<UCommonLocalPlayer>(LocalPlayer);
	if (!CommonLocalPlayer)
	{
		UE_LOG(LogCommonUserInterface, Warning, TEXT("LocalPlayer is not a UCommonLocalPlayer."));
		return nullptr;
	}

	UCommonPrimaryGameLayout* RootLayout = Policy->GetRootLayout(CommonLocalPlayer);
	if (!RootLayout)
	{
		UE_LOG(LogCommonUserInterface, Warning, TEXT("Failed to get RootLayout from UI policy."));
		return nullptr;
	}
	
	return RootLayout->PushWidgetToLayerStack(LayerName, WidgetClass);
}
