// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "Components/PawnComponent.h"
#include "BlotHeroComponent.generated.h"

class ABlotCharacter;
class UCommonCameraMode;
class UBlotCameraMode;
template <class TClass> class TSubclassOf;

/**
 *		初始化Hero的技能/摄像机/输入系统，依赖PawnExtension协调初始化
 */
UCLASS(Blueprintable, Meta=(BlueprintSpawnableComponent))
class BLOTGAME_API UBlotHeroComponent : public UPawnComponent,public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()

public:
	//~ Begin IGameFrameworkInitStateInterface interface
	virtual FName GetFeatureName() const override { return NAME_ActorFeatureName; }
	virtual bool CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const override;
	/** 调用函数初始化Hero的技能/摄像机/输入系统 */
	virtual void HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) override;
	virtual void OnActorInitStateChanged(const FActorInitStateChangedParams& Params) override;
	virtual void CheckDefaultInitialization() override;
	//~ End IGameFrameworkInitStateInterface interface

	/** GameFrameworkInitState中用于标记Hero组件的标记，在GameFrameworkInitState中用Feature代指组件 */
	static const FName NAME_ActorFeatureName;
	
protected:
	virtual void OnRegister() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
private:
	TSubclassOf<UCommonCameraMode> DetermindCameraModeOnPawnDataSet() const;
};
