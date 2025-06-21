// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonGameActivatableWidget.h"


TOptional<FUIInputConfig> UCommonGameActivatableWidget::GetDesiredInputConfig() const
{
	switch (InputConfig)
	{
	case ECommonWidgetInputMode::GameAndMenu:
		return FUIInputConfig(ECommonInputMode::All, GameMouseCaptureMode);
	case ECommonWidgetInputMode::Game:
		return FUIInputConfig(ECommonInputMode::Game, GameMouseCaptureMode);
	case ECommonWidgetInputMode::Menu:
		return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
	case ECommonWidgetInputMode::Default:
	default:
		return TOptional<FUIInputConfig>();
	}
}
