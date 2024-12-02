// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonCameraComponent.h"
#include "CommonCameraMode.h"

UCommonCameraComponent::UCommonCameraComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer),CommonCameraModeStack(nullptr)
{
}

void UCommonCameraComponent::OnRegister()
{
	Super::OnRegister();

	if (!CommonCameraModeStack)
	{
		CommonCameraModeStack = NewObject<UCommonCameraModeStack>(this);
		check(CommonCameraModeStack);
	}
}

void UCommonCameraComponent::GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView)
{
	check(CommonCameraModeStack);
	
	//Get Default CameraMode From PlayerState PanwData then Push In Stack
	if(DetermindCameraModeOnPawnDataSetDelgate.IsBound())
	{
		if(TSubclassOf<UCommonCameraMode>CommonCameraMode=DetermindCameraModeOnPawnDataSetDelgate.Execute())
		{
			CommonCameraModeStack->PushCameraMode(CommonCameraMode);
		}
	}

	CommonCameraModeStack->UpdateCameraModeStack(DeltaTime);

	const FCommonCameraModeView* CameraModeView=GetBestGameModeViewFromStack();
	if(CameraModeView==nullptr) return;
	
	// Keep player controller in sync with the latest view.
	if (const APawn* TargetPawn = Cast<APawn>(GetOwner()))
	{
		if (APlayerController* PC = TargetPawn->GetController<APlayerController>())
		{
			PC->SetControlRotation(CameraModeView->Rotation);
		}
	}

	// Keep camera component in sync with the latest view.
	SetWorldLocationAndRotation(CameraModeView->Location, CameraModeView->Rotation);
	FieldOfView = CameraModeView->FOV;

	//TODO : FLyraCameraModeView可以更新加入下面的所有信息
	// Fill in desired view.
	DesiredView.Location = CameraModeView->Location;
	DesiredView.Rotation = CameraModeView->Rotation;
	DesiredView.FOV = CameraModeView->FOV;
	DesiredView.OrthoWidth = OrthoWidth;
	DesiredView.OrthoNearClipPlane = OrthoNearClipPlane;
	DesiredView.OrthoFarClipPlane = OrthoFarClipPlane;
	DesiredView.AspectRatio = AspectRatio;
	DesiredView.bConstrainAspectRatio = bConstrainAspectRatio;
	DesiredView.bUseFieldOfViewForLOD = bUseFieldOfViewForLOD;
	DesiredView.ProjectionMode = ProjectionMode;

	// See if the CameraActor wants to override the PostProcess settings used.
	DesiredView.PostProcessBlendWeight = PostProcessBlendWeight;
	if (PostProcessBlendWeight > 0.0f)
	{
		DesiredView.PostProcessSettings = PostProcessSettings;
	}
}

const FCommonCameraModeView* UCommonCameraComponent::GetBestGameModeViewFromStack() const
{
	const UCommonCameraMode* CameraMode=CommonCameraModeStack->GetButtonOfStack();
	if(CameraMode!=nullptr) return CameraMode->GetCameraModeView();
	return nullptr;
}

