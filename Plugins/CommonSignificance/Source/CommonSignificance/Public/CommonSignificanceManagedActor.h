// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonSigManagedObjectInterface.h"
#include "GameFramework/Actor.h"
#include "CommonSignificanceManagedActor.generated.h"

struct FSignificanceTickIntervalPolicy;
/**
 * ★ 精华总结（此基类集成了所有精华技术点）:
 * - 精华7: DedicatedServer跳过
 * - 精华10: CDO排除(!HasAnyFlags(RF_ClassDefaultObject))
 * - 精华8: Tag查表获取策略
 * - 精华11: AttachParent链向上查找OwnerCharacter
 * - 精华12: 本地玩家HighestSignificance特殊处理
 * - 精华9: PropagateToChildComponent传播（排除自身是SignificanceManaged的组件）
 * - 精华5: SignificanceFunction按可见性+计算类型查表
 * - 精华8: PostSignificanceFunction → OnSignificanceChanged → SetActorTickInterval
 */
UCLASS(BlueprintType)
class COMMONSIGNIFICANCE_API ACommonSignificanceManagedActor : public AActor,public ICommonSigManagedObjectInterface
{
	GENERATED_BODY()
	
public:	
	ACommonSignificanceManagedActor() {};

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Destroyed() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ★ 精华8：配置标签 — 对应SignificanceSettings中的策略
	UPROPERTY(EditDefaultsOnly, Category = Significance)
	FName SignificanceTag = TEXT("DefaultActor");

	// ★ 精华2：计算方式
	UPROPERTY(EditDefaultsOnly, Category = Significance)
	ESignificanceByType SignificanceByType = ESignificanceByType::Distance;

	// ★ 精华1：Post回调方式
	UPROPERTY(EditDefaultsOnly, Category = Significance)
	EPostSignificanceType PostSignificanceType = EPostSignificanceType::Sequential;

	// ★ 精华5：Significance计算 — 由UE SignificanceManager每帧调用
	virtual float SignificanceFunction(
	USignificanceManager::FManagedObjectInfo* ObjectInfo, const FTransform& Viewpoint) override;

	// ★ 精华5：Post回调 — 分值变化时触发
	virtual void PostSignificanceFunction(
	USignificanceManager::FManagedObjectInfo* ObjectInfo,
	float OldSignificance, float Significance, bool bFinal) override;

	// ★ 子类可覆写，蓝图可实现
	UFUNCTION(BlueprintNativeEvent, Category = Significance)
	void OnSignificanceChanged(float OldSignificance, float Significance);
	
protected:
	// ★ 精华2：不同计算方式的距离/屏占比获取
	virtual float GetActorDistance(const FTransform& Viewpoint);
	virtual float GetActorDistance2D(const FTransform& Viewpoint);
	virtual float GetActorScreenSize(const FTransform& Viewpoint);

protected:
	const FSignificanceTickIntervalPolicy* SignificancePolicy = nullptr;	
};
