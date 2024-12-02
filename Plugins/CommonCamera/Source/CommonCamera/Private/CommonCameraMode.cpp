// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonCameraMode.h"

#include "CommonCameraComponent.h"

///////////////////////////////////////////////
///CameraMode
//////////////////////////////////////////////

UCommonCameraMode::UCommonCameraMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, CameraModeView()
	, BlendWeight(0)
{
}

void UCommonCameraMode::UpdateCameraMode(float DelatTime)
{
	UpdateView();
	UpdateBlend(DelatTime);
}

UCommonCameraComponent* UCommonCameraMode::GetCameraComponent() const
{
	return CastChecked<UCommonCameraComponent>(GetOuter());
}

AActor* UCommonCameraMode::GetTarget() const
{
	return GetCameraComponent()->GetOwner();
}

void UCommonCameraMode::UpdateView()
{
	CameraModeView.Location=GetPivotLocation();
	CameraModeView.Rotation=GetPivotRotation();
	CameraModeView.FOV=FOV;
}

void UCommonCameraMode::UpdateBlend(float DelatTime)
{
	BlendWeight+=DelatTime/BlendTime;
}

FVector UCommonCameraMode::GetPivotLocation() const
{
	AActor* Target=GetTarget();
	check(Target);
	if(const APawn* PawnTarget=Cast<APawn>(Target))
	{
		return PawnTarget->GetPawnViewLocation();
	}
	else
	{
		return Target->GetActorLocation();
	}
}

FRotator UCommonCameraMode::GetPivotRotation() const
{
	AActor* Target=GetTarget();
	check(Target);
	if(const APawn* PawnTarget=Cast<APawn>(Target))
	{
		return PawnTarget->GetViewRotation();
	}
	else
	{
		return Target->GetActorRotation();
	}
}

///////////////////////////////////////////////
///CameraModeStack
//////////////////////////////////////////////

void UCommonCameraModeStack::PushCameraMode(const TSubclassOf<UCommonCameraMode>& CameraModeClass)
{
	if (!CameraModeClass)
	{
		return;
	}
	UCommonCameraMode* CameraMode=GetOnlyCameraModInstance(CameraModeClass);
	check(CameraMode);
	int32 StackSize = CameraModeStack.Num();
	if ((StackSize > 0) && (CameraModeStack[0] == CameraMode))
	{
		// Already top of stack.
		return;
	}

	// Add new entry to top of stack.造成后面的元素移动
	CameraModeStack.Insert(CameraMode, 0);
}

UCommonCameraMode* UCommonCameraModeStack::GetButtonOfStack()
{
	const int32 StackSize = CameraModeStack.Num();
	if (StackSize <= 0)
	{
		return nullptr;
	}
	return CameraModeStack[StackSize - 1];
}

void UCommonCameraModeStack::UpdateCameraModeStack(float DeltaTime)
{
	const int32 StackSize = CameraModeStack.Num();
	if (StackSize <= 0)
	{
		return;
	}
	
	int32 RemoveCount = 0;
	int32 RemoveIndex = INDEX_NONE;

	for (int32 StackIndex = 0; StackIndex < StackSize; ++StackIndex)
	{
		UCommonCameraMode* CameraMode = CameraModeStack[StackIndex];
		check(CameraMode);

		CameraMode->UpdateCameraMode(DeltaTime);

		if (CameraMode->GetBlendWeight() >= 1.0f)
		{
			// Everything below this mode is now irrelevant and can be removed.
			RemoveIndex = (StackIndex + 1);
			RemoveCount = (StackSize - RemoveIndex);
			break;
		}
	}

	if (RemoveCount >0)
	{
		//对于权重刚满足>1.f的不删
		CameraModeStack.RemoveAt(RemoveIndex, RemoveCount);
	}
}

UCommonCameraMode* UCommonCameraModeStack::GetOnlyCameraModInstance(const TSubclassOf<UCommonCameraMode>& CameraModeClass)
{
	//check if already exist
	for(auto CameraMode:CameraModeInstances)
	{
		check(CameraMode);
		if(CameraMode&&CameraModeClass==CameraMode->GetClass())
		{
			return CameraMode;
		}
	}

	// Not found, so we need to create it.
	UCommonCameraMode* NewCameraMode = NewObject<UCommonCameraMode>(GetOuter(), CameraModeClass, NAME_None, RF_NoFlags);
	check(NewCameraMode);

	CameraModeInstances.Add(NewCameraMode);

	return NewCameraMode;
}
