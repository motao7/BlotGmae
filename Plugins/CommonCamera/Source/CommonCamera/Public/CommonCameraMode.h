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
	virtual void UpdateView();
	virtual void UpdateBlend(float DelatTime);

private:
	/** Return Pawn View Location or actor location*/
	FVector GetPivotLocation() const;
	/** Return Pawn View Rotation or actor Rotation*/
	FRotator GetPivotRotation() const;
	
	/** Finally return to CameraComponent,Use This View To Set Engine DesiredView */
	FCommonCameraModeView CameraModeView;

	UPROPERTY(EditAnywhere,Category="Camera")
	float FOV=90.f;
	UPROPERTY(EditAnywhere,Category="Camera")
	float BlendTime=2.f;
	
	/** When 0.f indicate that CameraMode just put  in stack,When 1.f indicate that CameraMode should be Remove */
	float BlendWeight;
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

	//这两个属性我们希望长时间存在，如果不加UPROPERTY(),会导致莫名其妙的内存问题即这两个TArray被GC系统莫名其妙回收了
	//当你在使用一个指针前check了它，如果使用过程中报错，那大概率就是该指针被垃圾系统回收了，用UPORPERTY()可以让GC系统追踪其的生命周期保持与class一致?
	//优化性能：不必要的 UPROPERTY() 会增加序列化和反射负担，尽量避免滥用。
	//引擎中的 UObject 类型变量，如果没有 UPROPERTY() 修饰，垃圾回收系统（GC）无法识别它，可能导致其意外被回收。
	//如果指针的尽头为UObject对象，那么该属性就应该标记为UPROPERTY()
	UPROPERTY()
	TArray<TObjectPtr<UCommonCameraMode>> CameraModeInstances;
	UPROPERTY()
	//0为Stack的顶，Last元素为Stack的底
	TArray<TObjectPtr<UCommonCameraMode>> CameraModeStack;
};

