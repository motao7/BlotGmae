// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "CommonCameraComponent.generated.h"

struct FCommonCameraModeView;
class UCommonCameraMode;
class UCommonCameraModeStack;

DECLARE_DELEGATE_RetVal(TSubclassOf<UCommonCameraMode>,FDetermindCameraModeOnPawnDataSetDelgateSiganture)

/**
 * 
 */
UCLASS()
class COMMONCAMERA_API UCommonCameraComponent : public UCameraComponent
{
	GENERATED_BODY()
	
public:
	explicit UCommonCameraComponent(const FObjectInitializer& ObjectInitializer);

	/** Create  CameraModeStack */
	virtual void OnRegister() override;
	/** Call per frmae ,Modify DesiredView that give to Engine to Update CameraView */
	virtual void GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView) override;

	FDetermindCameraModeOnPawnDataSetDelgateSiganture DetermindCameraModeOnPawnDataSetDelgate;
	
private:
	const FCommonCameraModeView* GetBestGameModeViewFromStack() const;
	UPROPERTY()
	TObjectPtr<UCommonCameraModeStack> CommonCameraModeStack;
	
};
