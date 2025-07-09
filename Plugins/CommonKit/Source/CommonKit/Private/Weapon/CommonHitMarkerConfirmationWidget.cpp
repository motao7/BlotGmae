// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/CommonHitMarkerConfirmationWidget.h"

#include "Blueprint/UserWidget.h"
#include "Weapon/SCommonHitMarkerConfirmationWidget.h"


UCommonHitMarkerConfirmationWidget::UCommonHitMarkerConfirmationWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UWidget::SetVisibility(ESlateVisibility::HitTestInvisible);
	bIsVolatile = true;
	AnyHitsMarkerImage.DrawAs = ESlateBrushDrawType::NoDrawType;
}
TSharedRef<SWidget> UCommonHitMarkerConfirmationWidget::RebuildWidget()
{
	UUserWidget* OuterUserWidget = GetTypedOuter<UUserWidget>();
	FLocalPlayerContext DummyContext;
	const FLocalPlayerContext& PlayerContextRef = (OuterUserWidget != nullptr) ? OuterUserWidget->GetPlayerContext() : DummyContext;

	MyMarkerWidget = SNew(SCommonHitMarkerConfirmationWidget, PlayerContextRef)
		.AnyHitsMarkerImage(&(this->AnyHitsMarkerImage))
		.HitNotifyDuration(this->HitNotifyDuration);

	return MyMarkerWidget.ToSharedRef();
}

void UCommonHitMarkerConfirmationWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	MyMarkerWidget.Reset();
}
