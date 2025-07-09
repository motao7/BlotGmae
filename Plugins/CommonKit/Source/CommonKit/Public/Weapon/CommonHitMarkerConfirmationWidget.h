// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "CommonHitMarkerConfirmationWidget.generated.h"

class SCommonHitMarkerConfirmationWidget;
/**
 * 
 */
UCLASS()
class COMMONKIT_API UCommonHitMarkerConfirmationWidget : public UWidget
{
	GENERATED_BODY()

public:
	UCommonHitMarkerConfirmationWidget(const FObjectInitializer& ObjectInitializer);

	//~UWidget interface
protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	//~End of UWidget interface

	//~UVisual interface
public:
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	//~End of UVisual interface

public:
	/** The duration (in seconds) to display hit notifies (they fade to transparent over this time)  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance, meta=(ClampMin=0.0, ForceUnits=s))
	float HitNotifyDuration = 0.4f;
	
	/** The marker image to draw if there are any hits at all. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)
	FSlateBrush AnyHitsMarkerImage;

private:
	/** Internal slate widget representing the actual marker visuals */
	TSharedPtr<SCommonHitMarkerConfirmationWidget> MyMarkerWidget;
};
