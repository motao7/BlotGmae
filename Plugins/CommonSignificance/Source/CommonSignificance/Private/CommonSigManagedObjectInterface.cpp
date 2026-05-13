// Fill out your copyright notice in the Description page of Project Settings.

#include "CommonSigManagedObjectInterface.h"

#include "Kismet/KismetSystemLibrary.h"


// Add default functionality here for any ICommonSigManagedObjectInterface functions that are not pure virtual.
void ICommonSigManagedObjectInterface::OnSignificanceManagedObjectBeginPlay(AActor* InActor, FName Tag, EPostSignificanceType InPostType)
{
	if (InActor&&!UKismetSystemLibrary::IsDedicatedServer(InActor))
	{
		InternalRegister(InActor->GetWorld(),InActor,Tag,InPostType);
	}
}

// ★ 精华7：DedicatedServer跳过 — 服务器不需要Significance优化
void ICommonSigManagedObjectInterface::OnSignificanceManagedObjectEndPlay(AActor* InActor)
{
	if (InActor) InternalUnregister(InActor->GetWorld(),InActor);
}

void ICommonSigManagedObjectInterface::OnSignificanceManagedObjectBeginPlay(UActorComponent* InComp, FName Tag, EPostSignificanceType InPostType)
{
	if (InComp && !UKismetSystemLibrary::IsDedicatedServer(InComp))
	{
		InternalRegister(InComp->GetWorld(), InComp, Tag, InPostType);
	}
}

void ICommonSigManagedObjectInterface::OnSignificanceManagedObjectEndPlay(UActorComponent* InComp)
{
	if (InComp)
	{
		InternalUnregister(InComp->GetWorld(), InComp);
	}
}

bool ICommonSigManagedObjectInterface::HadRegisteredObject(AActor* InActor)
{
	if (InActor&&!UKismetSystemLibrary::IsDedicatedServer(InActor))
	{
		if (USignificanceManager* SM = USignificanceManager::Get(InActor->GetWorld()))
		{
			return SM->GetManagedObject(InActor)!=nullptr;
		}
	}

	return false;
}

bool ICommonSigManagedObjectInterface::HadRegisteredObject(UActorComponent* InComp)
{
	if (InComp&&!UKismetSystemLibrary::IsDedicatedServer(InComp))
	{
		if (USignificanceManager* SM = USignificanceManager::Get(InComp->GetWorld()))
		{
			return SM->GetManagedObject(InComp)!=nullptr;
		}
	}

	return false;
}

float ICommonSigManagedObjectInterface::SignificanceFunction(USignificanceManager::FManagedObjectInfo* ObjectInfo, const FTransform& Viewpoint)
{
	return 0.f;
}

void ICommonSigManagedObjectInterface::PostSignificanceFunction(USignificanceManager::FManagedObjectInfo* ObjectInfo, float OldSignificance, float Significance, bool bFinal)
{
}

// ★ 精华6 核心：Lambda桥接 — 将UE的TFunction回调路由到虚函数，子类覆写即可
void ICommonSigManagedObjectInterface::InternalRegister(UWorld* InWorld, UObject* InObject, FName Tag, EPostSignificanceType InPostType)
{
	if (USignificanceManager* SM = USignificanceManager::Get(InWorld))
	{
		auto SignificanceFn = [&](USignificanceManager::FManagedObjectInfo* ObjectInfo,const FTransform& ViewPoint)->float
		{
			checkf(ObjectInfo, TEXT("SignificanceManagedObjectInfo Invalid."));
			checkf(IsValid(ObjectInfo->GetObject()),
				TEXT("Tag=%s, Name=%s"), *ObjectInfo->GetTag().ToString(),
				ObjectInfo->GetObject() ? *ObjectInfo->GetObject()->GetFullName() : TEXT("NAN"));
			return SignificanceFunction(ObjectInfo, ViewPoint);
		};

		auto PostSignificanceFn = [&](USignificanceManager::FManagedObjectInfo* ObjectInfo,
		float OldSignificance, float Significance, bool bFinal)
		{
			checkf(ObjectInfo, TEXT("PostSignificanceManagedObjectInfo Invalid."));
			checkf(IsValid(ObjectInfo->GetObject()),
				TEXT("Post Tag=%s, Name=%s"), *ObjectInfo->GetTag().ToString(),
				ObjectInfo->GetObject() ? *ObjectInfo->GetObject()->GetFullName() : TEXT("NAN"));
			PostSignificanceFunction(ObjectInfo, OldSignificance, Significance, bFinal);
		};

		// 项目枚举 → UE引擎枚举? 好像是为了与引擎解耦
		USignificanceManager::EPostSignificanceType PostType = USignificanceManager::EPostSignificanceType::None;
		switch (InPostType)
		{
		case EPostSignificanceType::Concurrent:
			PostType = USignificanceManager::EPostSignificanceType::Concurrent; break;
		case EPostSignificanceType::Sequential:
			PostType = USignificanceManager::EPostSignificanceType::Sequential; break;
		default:
			PostType = USignificanceManager::EPostSignificanceType::None; break;
		}

		SM->RegisterObject(InObject, Tag, SignificanceFn, PostType, PostSignificanceFn);
	}
}

void ICommonSigManagedObjectInterface::InternalUnregister(UWorld* InWorld, UObject* InObject)
{
	if (USignificanceManager* SM = USignificanceManager::Get(InWorld))
	{
		SM->UnregisterObject(InObject);
	}
}
