// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CommonLodManagerComponent.generated.h"

/**
 * 挂在 PlayerController 上（AutonomousProxy）。
 * 定期查询空间网格，计算每个 SimulatedProxy 角色的距离，
 * 调用其 InGameLODComponent::ProcessDistance 驱动 LOD 降级。
 */

UCLASS(ClassGroup = Performance, meta = (BlueprintSpawnableComponent))
class UCommonGameLODManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCommonGameLODManagerComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float UpdateInterval = 1.0f;

	UPROPERTY()
	TObjectPtr<AActor> PlayerActor = nullptr;

	UPROPERTY(EditAnywhere)
	bool bEnableDebug = false;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

private:
	float UpdateAccumulator = 0.f;
};