// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonSigManagedObjectInterface.h"
#include "UObject/NoExportTypes.h"
#include "CommonSignificanceSettings.generated.h"

// ★ 精华8：数据驱动 — 距离阈值表（Significance分值 + 最大距离）
USTRUCT(BlueprintType)
struct FSignificanceDistanceThresholds
{
	GENERATED_BODY()

	FSignificanceDistanceThresholds(float InSignificance = 0, float InMaxDistance = 0)
		: Significance(InSignificance), MaxDistance(InMaxDistance) {}

	UPROPERTY(EditAnywhere) float Significance;
	UPROPERTY(EditAnywhere) float MaxDistance;
};

// ★ 精华8：数据驱动 — 屏占比阈值表（Significance分值 + 屏占比阈值）
USTRUCT(BlueprintType)
struct FSignificanceScreenSizeThresholds
{
	GENERATED_BODY()

	FSignificanceScreenSizeThresholds(float InSignificance = 0, float InScreenSize = 0)
		: Significance(InSignificance), ScreenSize(InScreenSize) {}

	UPROPERTY(EditAnywhere) float Significance;
	UPROPERTY(EditAnywhere) float ScreenSize;
};

// ★ 精华8：数据驱动 — Significance分值 → TickInterval 映射
USTRUCT(BlueprintType)
struct FSignificanceTickInterval
{
	GENERATED_BODY()

	FSignificanceTickInterval(float InSignificance = 0, float InTickInterval = 0)
		: Significance(InSignificance), TickInterval(InTickInterval) {}

	UPROPERTY(EditAnywhere) float Significance;
	UPROPERTY(EditAnywhere) float TickInterval;
};

// 可见时的阈值设置
USTRUCT(BlueprintType)
struct FSignificanceDistanceThresholdSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FSignificanceDistanceThresholds> Thresholds;

	float GetSignificanceByDistance(float Distance) const;
};

USTRUCT(BlueprintType)
struct FSignificanceScreenSizeThresholdSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FSignificanceScreenSizeThresholds> Thresholds;

	float GetSignificanceByScreenSize(float ScreenSize) const;
};

// TickInterval映射 + 传播开关
USTRUCT(BlueprintType)
struct FSignificanceTickIntervalSettings
{
	GENERATED_BODY()

	FSignificanceTickIntervalSettings() : bPropagateToChildComponent(true) {}

	UPROPERTY(EditAnywhere)
	TArray<FSignificanceTickInterval> TickIntervalMap;

	// ★ 精华9：传播开关 — 是否将TickInterval传播给子组件
	UPROPERTY(EditAnywhere)
	uint8 bPropagateToChildComponent : 1;

	float GetTickIntervalBySignificance(float Significance) const;
};

// ★ 精华8 核心：策略基类 — 策略模式，子类实现不同的"条件→分值"映射
USTRUCT(BlueprintType)
struct FSignificanceTickIntervalPolicy
{
	GENERATED_BODY()

	virtual float GetSignificance(bool bIsVisible, float InCondition) const { return 0.f; }
	virtual float GetTickInterval(float InSignificance) const { return 0.f; }
	virtual bool PropagateToChildComponent() const { return false; }
	virtual ~FSignificanceTickIntervalPolicy() {}
};

USTRUCT(BlueprintType)
struct FSignificanceTickIntervalByDistancePolicy : public FSignificanceTickIntervalPolicy
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FName Tag;

	UPROPERTY(EditDefaultsOnly)
	FSignificanceDistanceThresholdSettings VisibleSettings;
	
	UPROPERTY(EditDefaultsOnly)
	FSignificanceDistanceThresholdSettings InvisibleSettings;
	
	UPROPERTY(EditDefaultsOnly)
	FSignificanceTickIntervalSettings TickSettings;

	virtual float GetSignificance(bool bIsVisible, float InCondition) const override
	{
		return bIsVisible ?
			VisibleSettings.GetSignificanceByDistance(InCondition) :
			InvisibleSettings.GetSignificanceByDistance(InCondition);
	}

	virtual float GetTickInterval(float InSignificance) const override
	{
		return TickSettings.GetTickIntervalBySignificance(InSignificance);
	}

	virtual bool PropagateToChildComponent() const override
	{
		return TickSettings.bPropagateToChildComponent;
	}
};

// ★ 精华8：按屏占比的策略 — 可见用屏占比表，不可见用距离表
USTRUCT(BlueprintType)
struct FSignificanceTickIntervalByScreenSizePolicy : public FSignificanceTickIntervalPolicy
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly) FName Tag;

	UPROPERTY(EditDefaultsOnly) FSignificanceScreenSizeThresholdSettings VisibleSettings;
	UPROPERTY(EditDefaultsOnly) FSignificanceDistanceThresholdSettings InvisibleSettings;
	UPROPERTY(EditDefaultsOnly) FSignificanceTickIntervalSettings TickSettings;

	virtual float GetSignificance(bool bIsVisible, float InCondition) const override
	{
		return bIsVisible ?
			VisibleSettings.GetSignificanceByScreenSize(InCondition) :
			InvisibleSettings.GetSignificanceByDistance(InCondition);
	}

	virtual float GetTickInterval(float InSignificance) const override
	{
		return TickSettings.GetTickIntervalBySignificance(InSignificance);
	}
	virtual bool PropagateToChildComponent() const override
	{
		return TickSettings.bPropagateToChildComponent;
	}
};

// ★ 精华8 核心：配置容器 — 存在DefaultEngine.ini中，运行时查表
UCLASS(Config = Engine, defaultconfig)
class USignificanceSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = Significance)
	TArray<FSignificanceTickIntervalByDistancePolicy> DistancePolicies;

	UPROPERTY(Config, EditAnywhere, Category = Significance)
	TArray<FSignificanceTickIntervalByScreenSizePolicy> ScreenSizePolicies;

	// ★ 精华8 核心：按Tag+Type查策略
	static const FSignificanceTickIntervalPolicy* GetTickIntervalPolicy(FName InTag, ESignificanceByType InType);
};
