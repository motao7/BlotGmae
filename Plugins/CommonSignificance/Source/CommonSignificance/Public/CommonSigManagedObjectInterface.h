// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SignificanceManager.h"
#include "CommonSigManagedObjectInterface.generated.h"

// ★ 精华1：PostSignificanceType — 控制Post回调的并行/串行
UENUM()
enum class EPostSignificanceType : uint8
{
	None,
	Concurrent,
	Sequential
};

// ★ 精华2：SignificanceByType — 支持4种计算方式
UENUM()
enum class ESignificanceByType : uint8
{
	Distance,
	Distance2D,
	ScreenSize,
	Custom
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCommonSigManagedObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COMMONSIGNIFICANCE_API ICommonSigManagedObjectInterface
{
	GENERATED_BODY()

public:
	// Actor 版注册/反注册
	virtual void OnSignificanceManagedObjectBeginPlay(AActor* InActor, FName Tag, EPostSignificanceType InPostType);
	virtual void OnSignificanceManagedObjectEndPlay(AActor* InActor);

	// Component 版注册/反注册
	virtual void OnSignificanceManagedObjectBeginPlay(UActorComponent* InComp, FName Tag, EPostSignificanceType InPostType);
	virtual void OnSignificanceManagedObjectEndPlay(UActorComponent* InComp);

	// ★ 精华4：查询是否已注册（防重复注册）
	virtual bool HadRegisteredObject(AActor* InActor);
	virtual bool HadRegisteredObject(UActorComponent* InComp);

	// ★ 精华5：Significance计算 + Post回调，子类必须覆写
	virtual float SignificanceFunction(USignificanceManager::FManagedObjectInfo* ObjectInfo, const FTransform& Viewpoint)=0;
	virtual void PostSignificanceFunction(USignificanceManager::FManagedObjectInfo* ObjectInfo, float OldSignificance, float Significance, bool bFinal)=0;
	
protected:
	// ★ 精华6：内部注册 — 用Lambda桥接UE的C函数指针到虚函数
	void InternalRegister(UWorld* InWorld, UObject* InObject, FName Tag, EPostSignificanceType InPostType);
	void InternalUnregister(UWorld* InWorld, UObject* InObject);
};
