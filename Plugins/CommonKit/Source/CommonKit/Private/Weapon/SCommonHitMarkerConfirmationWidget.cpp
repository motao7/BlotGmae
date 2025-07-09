// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/SCommonHitMarkerConfirmationWidget.h"

#include "Weapon/CommonWeaponStateComponent.h"

void SCommonHitMarkerConfirmationWidget::Construct(const FArguments& InArgs, const FLocalPlayerContext& InContext)
{
	AnyHitsMarkerImage = InArgs._AnyHitsMarkerImage;
	MyContext = InContext;
}

int32 SCommonHitMarkerConfirmationWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	const FVector2D LocalCenter = AllottedGeometry.GetLocalPositionAtCoordinates(FVector2D(0.5f, 0.5f));
	constexpr ESlateDrawEffect DrawEffects = ESlateDrawEffect::None;

	if (const bool bDrawMarkers = (HitNotifyOpacity > KINDA_SMALL_NUMBER))
	{
		if (AnyHitsMarkerImage != nullptr)
		{
			FLinearColor MarkerColor =(InWidgetStyle.GetColorAndOpacityTint() * AnyHitsMarkerImage->GetTint(InWidgetStyle));
			MarkerColor.A *= HitNotifyOpacity;

			// Otherwise show the hit notify in the center of the reticle
			const FPaintGeometry Geometry(AllottedGeometry.ToPaintGeometry(AnyHitsMarkerImage->ImageSize, FSlateLayoutTransform(LocalCenter - (AnyHitsMarkerImage->ImageSize * 0.5f))));
			FSlateDrawElement::MakeBox(OutDrawElements, LayerId, Geometry, AnyHitsMarkerImage,DrawEffects, MarkerColor);
		}
	}

	return LayerId;
}

void SCommonHitMarkerConfirmationWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	HitNotifyOpacity = 0.0f;

	if (APlayerController* PC = MyContext.IsInitialized() ? MyContext.GetPlayerController() : nullptr)
	{
		if (UCommonWeaponStateComponent* DamageMarkerComponent = PC->FindComponentByClass<UCommonWeaponStateComponent>())
		{
			const double TimeSinceLastHitNotification = DamageMarkerComponent->GetTimeSinceLastHitNotification();
			if (TimeSinceLastHitNotification < HitNotifyDuration)
			{
				HitNotifyOpacity = FMath::Clamp(1.0f - (float)(TimeSinceLastHitNotification / HitNotifyDuration), 0.0f, 1.0f);
			}
		}
	}
}

FVector2D SCommonHitMarkerConfirmationWidget::ComputeDesiredSize(float) const
{
	return FVector2D(100.0f, 100.0f);
}


