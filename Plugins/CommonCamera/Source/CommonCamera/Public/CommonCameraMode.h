// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonCameraMode.generated.h"

class UCommonCameraComponent;

struct FCommonCameraModeView
{
public:
	FVector Location;
	FRotator Rotation;
	float FOV;
};

/**
 * 
 */
UCLASS(Blueprintable)
class COMMONCAMERA_API UCommonCameraMode : public UObject
{
	GENERATED_BODY()

public:
	UCommonCameraMode(const FObjectInitializer& ObjectInitializer);
	
	const FCommonCameraModeView* GetCameraModeView() const {return &CameraModeView;}
	UCommonCameraComponent* GetCameraComponent() const;
	/** Return Camera Target  aka Object that Camera Follows */
	AActor* GetTarget() const;
	float GetBlendWeight() const {return BlendWeight;}

	/** UpdateView And Blend */
	void UpdateCameraMode(float DelatTime);

protected:
	/** Update CameraModeView accroding to Pivot Transfrom */
	virtual void UpdateView(float DeltaTime);
	virtual void UpdateBlend(float DelatTime);

	/** Current Just Set CrouchOffset when Crouched or not Coruched*/
	void UpdateForTarget(float DeltaTime);
	void SetTargetCrouchOffset(FVector NewTargetOffset);
	/** Smoothly Update CurrentCrouchOffset*/
	void UpdateCrouchOffset(float DeltaTime);

	FVector GetPivotLocation() const;
	FRotator GetPivotRotation() const;
	
	/** Finally return to CameraComponent,Use This View To Set Engine DesiredView */
	FCommonCameraModeView CameraModeView;

	UPROPERTY(EditAnywhere,Category="Camera")
	float FOV=90.f;
	UPROPERTY(EditAnywhere,Category="Camera")
	float BlendTime=2.f;
	// Alters the speed that a crouch offset is blended in or out
	UPROPERTY(EditAnywhere, Category = "Third Camera")
	float CrouchOffsetBlendMultiplier = 5.0f;

	/** When 0.f indicate that CameraMode just put  in stack,When 1.f indicate that CameraMode should be Remove */
	float BlendWeight;

	FVector InitialCrouchOffset = FVector::ZeroVector;
	FVector TargetCrouchOffset = FVector::ZeroVector;
	float CrouchOffsetBlendPct = 1.0f;
	FVector CurrentCrouchOffset = FVector::ZeroVector;
	
};

UCLASS()
class COMMONCAMERA_API UCommonCameraModeStack : public UObject
{
	GENERATED_BODY()

public:
	/** Local Var only Passing Type */
	void PushCameraMode(const TSubclassOf<UCommonCameraMode>& CameraModeClass);
	/** Return CameraStack[0],aka The Button of Stack */
	UCommonCameraMode* GetButtonOfStack();
	/** UpdateAllCameraMode in Stack then remove useless CameraMode */
	void UpdateCameraModeStack(float DeltaTime);

private:
	/** If Already In Stack Get it ,if Not in Stack Create New One And!!!Push in Stack , When Create New CameraMode Set Outer is CameraComponent */
	UCommonCameraMode* GetOnlyCameraModInstance(const TSubclassOf<UCommonCameraMode>& CameraModeClass);
	
	UPROPERTY()
	TArray<TObjectPtr<UCommonCameraMode>> CameraModeInstances;
	UPROPERTY()
	
	//0为Stack的顶，Last元素为Stack的底
	TArray<TObjectPtr<UCommonCameraMode>> CameraModeStack;

};

