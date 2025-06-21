// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonHUDLayout.h"

#include "CommonExtensionLibrary.h"
#include "NativeGameplayTags.h"
#include "UITag.h"
#include "Input/CommonUIInputTypes.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_LAYER_MENU, "UI.Layer.Menu");
UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_ACTION_ESCAPE, "UI.Action.Escape");

void UCommonHUDLayout::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	RegisterUIActionBinding(FBindUIActionArgs(FUIActionTag::ConvertChecked(TAG_UI_ACTION_ESCAPE), false, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleEscapeAction)));
}

void UCommonHUDLayout::HandleEscapeAction()
{if (ensure(EscapeMenuClass.Get()))
{
	UCommonExtensionLibrary::PushContentToLayer_ForPlayer(GetOwningLocalPlayer(), TAG_UI_LAYER_MENU, EscapeMenuClass);
}
}


