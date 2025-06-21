// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonGameActivatableWidget.h"
#include "CommonHUDLayout.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class COMMONGAME_API UCommonHUDLayout : public UCommonGameActivatableWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;
	
protected:
	void HandleEscapeAction();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCommonActivatableWidget> EscapeMenuClass;
};
