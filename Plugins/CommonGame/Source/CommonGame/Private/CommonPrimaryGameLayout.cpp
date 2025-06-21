// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonPrimaryGameLayout.h"

#include "Widgets/CommonActivatableWidgetContainer.h"


UCommonActivatableWidgetContainerBase* UCommonPrimaryGameLayout::GetLayerWidget(FGameplayTag LayerName)
{
	return Layers.FindRef(LayerName);
}

void UCommonPrimaryGameLayout::RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* LayerWidget)
{
	if (!IsDesignTime())
	{
		LayerWidget->SetTransitionDuration(0.0);
		Layers.Add(LayerTag, LayerWidget);
	}
}
