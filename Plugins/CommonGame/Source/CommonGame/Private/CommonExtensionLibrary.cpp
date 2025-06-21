// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonExtensionLibrary.h"

#include "CommonActivatableWidget.h"
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

	if (UCommonGameUIManagerSubsystem* UIManager = LocalPlayer->GetGameInstance()->GetSubsystem<UCommonGameUIManagerSubsystem>())
	{
		if (UCommonGameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
		{
			if (UCommonPrimaryGameLayout* RootLayout = Policy->GetRootLayout(CastChecked<UCommonLocalPlayer>(LocalPlayer)))
			{
				return RootLayout->PushWidgetToLayerStack(LayerName, WidgetClass);
			}
		}
	}

	return nullptr;
}
