// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonSignificanceManagedActor.h"

#include "CommonSignificanceSettings.h"
#include "GameFramework/Character.h"


// Called when the game starts or when spawned
void ACommonSignificanceManagedActor::BeginPlay()
{
	Super::BeginPlay();
	
	// ★ 精华10：排除CDO（Class Default Object不需要注册）
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		SignificancePolicy = USignificanceSettings::GetTickIntervalPolicy(SignificanceTag,SignificanceByType);
		if (SignificancePolicy) OnSignificanceManagedObjectBeginPlay(this,SignificanceTag,PostSignificanceType);
	}
}

void ACommonSignificanceManagedActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		OnSignificanceManagedObjectEndPlay(this);
	}
	Super::EndPlay(EndPlayReason);
}

void ACommonSignificanceManagedActor::Destroyed()
{
	Super::Destroyed();
}

float ACommonSignificanceManagedActor::SignificanceFunction(USignificanceManager::FManagedObjectInfo* ObjectInfo, const FTransform& Viewpoint)
{
	if (!SignificancePolicy) return 0.f;

	ACommonSignificanceManagedActor* Self = CastChecked<ACommonSignificanceManagedActor>(ObjectInfo->GetObject());
	if (!Self) return 0.f;

	// ★ 精华11：AttachParent链向上查找OwnerCharacter
	AActor* TempActor = Self;
	ACharacter* OwnerCharacter = nullptr;
	while (TempActor && !OwnerCharacter)
	{
		OwnerCharacter = Cast<ACharacter>(TempActor);
		TempActor = TempActor->GetAttachParentActor();
	}
	
	// ★ 精华12：本地玩家/观战目标 → 最高优先级
	const bool bHighestSignificance = (OwnerCharacter &&
		(OwnerCharacter->IsLocallyControlled() ||
		 OwnerCharacter->GetController() == nullptr)); // NPC等也保护

	if (bHighestSignificance || Self->WasRecentlyRendered())
	{
		// ★ 可见：按计算类型查"可见"阈值表
		switch (SignificanceByType)
		{
		case ESignificanceByType::Distance:
			{
				const float Distance = bHighestSignificance ? 0.f : Self->GetActorDistance(Viewpoint);
				return SignificancePolicy->GetSignificance(true, Distance);
			}
		case ESignificanceByType::Distance2D:
			{
				const float Distance = bHighestSignificance ? 0.f : Self->GetActorDistance2D(Viewpoint);
				return SignificancePolicy->GetSignificance(true, Distance);
			}
		case ESignificanceByType::ScreenSize:
			{
				const float ScreenSize = bHighestSignificance ? FLT_MAX : Self->GetActorScreenSize(Viewpoint);
				return SignificancePolicy->GetSignificance(true, ScreenSize);
			}
		case ESignificanceByType::Custom:
		default:
			break;
		}
	}
	else
	{
		// ★ 不可见：查"不可见"阈值表
		const float Distance = (SignificanceByType == ESignificanceByType::Distance2D) ?
			Self->GetActorDistance2D(Viewpoint) : Self->GetActorDistance(Viewpoint);
		return SignificancePolicy->GetSignificance(false, Distance);
	}

	return 0.f;
}

void ACommonSignificanceManagedActor::PostSignificanceFunction(USignificanceManager::FManagedObjectInfo* ObjectInfo, float OldSignificance, float Significance, bool bFinal)
{
	if (SignificancePolicy && OldSignificance != Significance)
	{
		OnSignificanceChanged(OldSignificance, Significance);
	}
}

void ACommonSignificanceManagedActor::OnSignificanceChanged_Implementation(float OldSignificance, float Significance)
{
	if (!SignificancePolicy) return;

	// ★ 精华8 核心：Significance分值 → TickInterval
	const float TickInterval = SignificancePolicy->GetTickInterval(Significance);
	PrimaryActorTick.TickInterval = TickInterval;

	// ★ 精华9：传播给子组件（排除自身是SignificanceManaged的组件）
	if (SignificancePolicy->PropagateToChildComponent())
	{
		TArray<UActorComponent*> Components;
		GetComponents(Components);
		for (UActorComponent* Comp : Components)
		{
			if (Comp && !Comp->IsA<UCommonSigManagedObjectInterface>())
			{
				Comp->PrimaryComponentTick.TickInterval = TickInterval;
			}
		}
	}
}

float ACommonSignificanceManagedActor::GetActorDistance(const FTransform& Viewpoint)
{
	return (GetActorLocation() - Viewpoint.GetLocation()).Size();
}

float ACommonSignificanceManagedActor::GetActorDistance2D(const FTransform& Viewpoint)
{
	return (GetActorLocation() - Viewpoint.GetLocation()).Size2D();
}

float ACommonSignificanceManagedActor::GetActorScreenSize(const FTransform& Viewpoint)
{
	FVector Origin;
	FVector BoxExtent;
	GetActorBounds(false,Origin,BoxExtent);

	const float BoundRadius = BoxExtent.Size();
	const float Distance = (Origin-Viewpoint.GetLocation()).Size();

	// 角直径 / FOV角度 → 屏占比
	const float AngularRadius = FMath::Atan(BoundRadius / Distance);
	// TODO:假设90度FOV，如果需要精确可从PlayerCameraManager获取
	const float HalfFOV = FMath::DegreesToRadians(45.f);
	return AngularRadius / HalfFOV;
}

// Called every frame
void ACommonSignificanceManagedActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

