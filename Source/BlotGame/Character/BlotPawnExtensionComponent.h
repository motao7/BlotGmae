// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "Components/PawnComponent.h"
#include "BlotPawnExtensionComponent.generated.h"

class UExperiencePawnData;
/**
 *		用于协调其他接入IGameFrameworkInitStateInterface接口的组件的初始化的进行
 */
UCLASS()
class BLOTGAME_API UBlotPawnExtensionComponent : public UPawnComponent,public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()

public:
	//~ Begin IGameFrameworkInitStateInterface interface
	virtual FName GetFeatureName() const override { return NAME_ActorFeatureName; }
	virtual bool CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const override;
	virtual void HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) override;
	virtual void OnActorInitStateChanged(const FActorInitStateChangedParams& Params) override;
	virtual void CheckDefaultInitialization() override;
	//~ End IGameFrameworkInitStateInterface interface

	/** 状态链中用于标记Hero组件 */
	static const FName NAME_ActorFeatureName;

	/** This Function is used to call CheckDefaultInitialization() On Controller Changed */
	void HandleOnControllerChanged();
	/** This Function is used to call CheckDefaultInitialization() On PlayerStateReplicated */
	void HandleOnPlayerStateReplicated();
	/** This Function is used to call CheckDefaultInitialization() On OnSetupPlayerInputComponent */
	void HandleOnSetupPlayerInputComponent();

protected:
	virtual void OnRegister() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
};
