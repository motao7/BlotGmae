// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */
class  SCommonHitMarkerConfirmationWidget:public SLeafWidget
{
	/**Define the FArguments in Consturct*/
	SLATE_BEGIN_ARGS(SCommonHitMarkerConfirmationWidget)
		:_AnyHitsMarkerImage(nullptr)
		, _HitNotifyDuration(0.4f)
		{
		}
		/** The marker image to draw if there are any hits at all. */
		SLATE_ARGUMENT(const FSlateBrush*, AnyHitsMarkerImage)
		/** The duration (in seconds) to display hit notifies (they fade to transparent over this time)  */
		SLATE_ATTRIBUTE(float, HitNotifyDuration)
	SLATE_END_ARGS()

public:
	SCommonHitMarkerConfirmationWidget(){}
	
	/**Be use by Snew*/
	void Construct(const FArguments& InArgs, const FLocalPlayerContext& InContext);

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	virtual FVector2D ComputeDesiredSize(float) const override;

private:
	/** The marker image to draw if there are any hits at all. */
	const FSlateBrush* AnyHitsMarkerImage = nullptr;

	/** The opacity for the hit markers */
	float HitNotifyOpacity = 0.0f;

	/** The duration (in seconds) to display hit notifies (they fade to transparent over this time)  */
	float HitNotifyDuration = 0.4f;

	/** Player context for the owning HUD */
	FLocalPlayerContext MyContext;
};
