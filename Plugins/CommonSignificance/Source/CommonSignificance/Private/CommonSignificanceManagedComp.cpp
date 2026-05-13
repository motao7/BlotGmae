// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonSignificanceManagedComp.h"

#include "CommonSignificanceSettings.h"
#include "GameFramework/Character.h"

// Called when the game starts
void UCommonSignificanceManagedComp::BeginPlay()
{
	Super::BeginPlay();
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		SignificancePolicy = USignificanceSettings::GetTickIntervalPolicy(SignificanceTag, SignificanceByType);
		if (SignificancePolicy)
		{
			OnSignificanceManagedObjectBeginPlay(this, SignificanceTag, PostSignificanceType);
		}
	}
}

void UCommonSignificanceManagedComp::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		OnSignificanceManagedObjectEndPlay(this);
	}
	Super::EndPlay(EndPlayReason);
}

void UCommonSignificanceManagedComp::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

float UCommonSignificanceManagedComp::SignificanceFunction(USignificanceManager::FManagedObjectInfo* ObjectInfo, const FTransform& Viewpoint)
{
	if (!SignificancePolicy) return 0.f;

	UCommonSignificanceManagedComp* Self = CastChecked<UCommonSignificanceManagedComp>(ObjectInfo->GetObject());
	if (!Self) return 0.f;

	AActor* OwnerActor = Self->GetOwner();
	if (!OwnerActor) return 0.f;

	// ★ 精华11：AttachParent链查找OwnerCharacter
	AActor* TempActor = OwnerActor;
	ACharacter* OwnerCharacter = nullptr;
	while (TempActor && !OwnerCharacter)
	{
		OwnerCharacter = Cast<ACharacter>(TempActor);
		TempActor = TempActor->GetAttachParentActor();
	}

	// ★ 精华12：本地玩家最高优先级
	const bool bHighestSignificance = (OwnerCharacter && OwnerCharacter->IsLocallyControlled());

	if (bHighestSignificance || OwnerActor->WasRecentlyRendered())
	{
		switch (SignificanceByType)
		{
		case ESignificanceByType::Distance:
			{
				const float Distance = bHighestSignificance ? 0.f : Self->GetOwnerDistance(Viewpoint);
				return SignificancePolicy->GetSignificance(true, Distance);
			}
		case ESignificanceByType::Distance2D:
			{
				const float Distance = bHighestSignificance ? 0.f : Self->GetOwnerDistance2D(Viewpoint);
				return SignificancePolicy->GetSignificance(true, Distance);
			}
		case ESignificanceByType::ScreenSize:
			{
				const float ScreenSize = bHighestSignificance ? FLT_MAX : Self->GetOwnerScreenSize(Viewpoint);
				return SignificancePolicy->GetSignificance(true, ScreenSize);
			}
		case ESignificanceByType::Custom:
		default:
			break;
		 }
	 }
	 else
	 {
		 const float Distance = Self->GetOwnerDistance(Viewpoint);
		 return SignificancePolicy->GetSignificance(false, Distance);
	 }

	return 0.f;
}

void UCommonSignificanceManagedComp::PostSignificanceFunction(USignificanceManager::FManagedObjectInfo* ObjectInfo, float OldSignificance, float Significance, bool bFinal)
{
	if (SignificancePolicy && OldSignificance != Significance)
	{
		OnSignificanceChanged(OldSignificance, Significance);
	}
}

void UCommonSignificanceManagedComp::OnSignificanceChanged_Implementation(float OldSignificance, float Significance)
{
	if (!SignificancePolicy) return;
	const float TickInterval = SignificancePolicy->GetTickInterval(Significance);
	SetComponentTickInterval(TickInterval);
}

float UCommonSignificanceManagedComp::GetOwnerDistance(const FTransform& Viewpoint)
{
	AActor* Owner = GetOwner();
	return Owner ? (Owner->GetActorLocation() - Viewpoint.GetLocation()).Size() : 0.f;
}

float UCommonSignificanceManagedComp::GetOwnerDistance2D(const FTransform& Viewpoint)
{
	AActor* Owner = GetOwner();
	return Owner ? (Owner->GetActorLocation() - Viewpoint.GetLocation()).Size2D() : 0.f;
}

float UCommonSignificanceManagedComp::GetOwnerScreenSize(const FTransform& Viewpoint)
{
	AActor* Owner = GetOwner();
	if (!Owner) return 0.f;

	FVector Origin;
	FVector BoxExtent;
	Owner->GetActorBounds(false, Origin, BoxExtent);

	const float BoundRadius = BoxExtent.Size();
	const float Distance = (Origin - Viewpoint.GetLocation()).Size();

	if (Distance < BoundRadius) return FLT_MAX;
	if (Distance < KINDA_SMALL_NUMBER) return FLT_MAX;

	const float AngularRadius = FMath::Atan(BoundRadius / Distance);
	const float HalfFOV = FMath::DegreesToRadians(45.f);
	return AngularRadius / HalfFOV;
}


