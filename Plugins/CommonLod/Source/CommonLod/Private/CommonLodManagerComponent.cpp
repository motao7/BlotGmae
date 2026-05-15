// Fill out your copyright notice in the Description page of Project Settings.

#include "CommonLodManagerComponent.h"
#include "CommonGameLodComponent.h"
#include "GameFramework/PlayerController.h"

DECLARE_STATS_GROUP(TEXT("CommonGameLOD"), STATGROUP_CommonGameLOD, STATCAT_Advanced);
DECLARE_CYCLE_STAT(TEXT("CommonGameLOD ProcessLod"), STAT_CommonGameLOD_ProcessLod, STATGROUP_CommonGameLOD);

UCommonGameLODManagerComponent::UCommonGameLODManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCommonGameLODManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerActor = GetOwner();
}

void UCommonGameLODManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 进客户端AutonomousProxy 运行
	if (GetNetMode() == NM_Client && GetOwnerRole() != ROLE_AutonomousProxy) return;

	//限帧
	UpdateAccumulator += DeltaTime;
	if (UpdateAccumulator < UpdateInterval) return;
	UpdateAccumulator = 0.f;

	if (!IsValid(PlayerActor)) return;

	SCOPE_CYCLE_COUNTER(STAT_CommonGameLOD_ProcessLod)

	//遍历每种区域类型，查网格，算距离
	for (const auto& Pair : UCommonGameLODComponent::RegionConfigMap)
	{
		TArray<UCommonGameLODComponent*> Components;
		if (!UCommonGameLODComponent::GetRegionComponents(Pair.Key,PlayerActor,Components)) continue;

		for (UCommonGameLODComponent* LodComp : Components)
		{
			if (!IsValid(LodComp)) continue;
			AActor* TargetActor = LodComp->GetOwner();
			if (!IsValid(TargetActor)) continue;

			const float Distance = FVector::Dist(PlayerActor->GetActorLocation(),TargetActor->GetActorLocation());
			LodComp->ProcessDistance(Distance);
		}
	}
}
