// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonGameLODStreamingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "UObject/SoftObjectPath.h"

DECLARE_STATS_GROUP(TEXT("CommonGameLOD"), STATGROUP_CommonGameLOD, STATCAT_Advanced);
DECLARE_CYCLE_STAT(TEXT("CommonGameLOD Streaming"), STAT_CommonGameLOD_Streaming, STATGROUP_CommonGameLOD);


UCommonGameLODStreamingComponent::UCommonGameLODStreamingComponent(const FObjectInitializer& ObjectInitializer)
{
	RegionType = EGameLODRegionType::NoneRegion;
}

void UCommonGameLODStreamingComponent::BeginPlay()
{
	Super::BeginPlay();
	if (GetNetMode() != NM_Client) return;
	if (GetOwnerRole() != ROLE_SimulatedProxy) return;

	CacheMeshComponents();

	// 初始状态：超出距离，先切到低模
	bOutOfMaxLodDistance = true;
	OnOutOfMaxLodDistance();
}

void UCommonGameLODStreamingComponent::OnLodActive(int32 Lod)
{
	SCOPE_CYCLE_COUNTER(STAT_CommonGameLOD_Streaming);

	for (FGameLODStaticMeshData& Data : StaticMeshLodData)
	{
		if (!Data.CachedComponent.IsValid()) continue;
		if (Lod >= Data.LodMeshList.Num() || !Data.LodMeshList[Lod].IsValid()) continue;
		ApplyStaticMesh(Data.CachedComponent, Data.LodMeshList[Lod]);
	}

	for (FGameLODSkeletalMeshData& Data : SkeletalMeshLodData)
	{
		if (!Data.CachedComponent.IsValid()) continue;
		if (Lod >= Data.LodMeshList.Num() || !Data.LodMeshList[Lod].IsValid()) continue;
		ApplySkeletalMesh(Data.CachedComponent, Data.LodMeshList[Lod], Data.bReInitPose);
	}
}

void UCommonGameLODStreamingComponent::OnOutOfMaxLodDistance()
{
	for (FGameLODStaticMeshData& Data : StaticMeshLodData)
	{
		if (!Data.CachedComponent.IsValid()) continue;
		if (!Data.OutOfDistanceMesh.IsValid()) continue;
		ApplyStaticMesh(Data.CachedComponent, Data.OutOfDistanceMesh);
	}

	for (FGameLODSkeletalMeshData& Data : SkeletalMeshLodData)
	{
		if (!Data.CachedComponent.IsValid()) continue;
		if (!Data.OutOfDistanceMesh.IsValid()) continue;
		ApplySkeletalMesh(Data.CachedComponent, Data.OutOfDistanceMesh, Data.bReInitPose);
	}
}

void UCommonGameLODStreamingComponent::CacheMeshComponents()
{
	if (!OwnerActor.IsValid()) return;

	for (FGameLODStaticMeshData& Data : StaticMeshLodData)
	{
		TArray<UActorComponent*> Comps = OwnerActor->GetComponentsByTag(
			UStaticMeshComponent::StaticClass(), Data.ComponentTag);
		if (Comps.Num() > 0)
			Data.CachedComponent = Cast<UStaticMeshComponent>(Comps[0]);
	}

	for (FGameLODSkeletalMeshData& Data : SkeletalMeshLodData)
	{
		TArray<UActorComponent*> Comps = OwnerActor->GetComponentsByTag(
			USkeletalMeshComponent::StaticClass(), Data.ComponentTag);
		if (Comps.Num() > 0)
			Data.CachedComponent = Cast<USkeletalMeshComponent>(Comps[0]);
	}
}

void UCommonGameLODStreamingComponent::ApplyStaticMesh(const TWeakObjectPtr<UStaticMeshComponent>& InComp, const TSoftObjectPtr<UStaticMesh>& InSoftMesh)
{
	UStaticMeshComponent* SMC = InComp.Get();
	if (!IsValid(SMC)) return;

	//已加载:直接设置
	if (InSoftMesh.IsValid())
	{
		UStaticMesh* Mesh = InSoftMesh.Get();
		if (SMC->GetStaticMesh()!=Mesh) SMC->SetStaticMesh(Mesh);
		return;
	}

	//未加载:异步加载
	const int32 RequestedLod = CurrentLod;
	const FSoftObjectPath AssetPath = InSoftMesh.ToSoftObjectPath();
	TWeakObjectPtr<UCommonGameLODComponent> WeakSelf = this;
	TWeakObjectPtr<UStaticMeshComponent> WeakComp = InComp;

	UAssetManager::GetStreamableManager().RequestAsyncLoad(AssetPath,
		FStreamableDelegate::CreateWeakLambda(this,[WeakSelf,RequestedLod,WeakComp,AssetPath]()
		{
			UCommonGameLODComponent* Self = WeakSelf.Get();
			if (!Self || Self->CurrentLod != RequestedLod) return;
			UStaticMeshComponent* Comp = WeakComp.Get();
			if (!Comp) return;

			UStaticMesh* LoadedMesh = Cast<UStaticMesh>(AssetPath.ResolveObject());
			if (!LoadedMesh) return;
			if (Comp->GetStaticMesh() == LoadedMesh) return;
			Comp->SetStaticMesh(LoadedMesh);
		}));
}

void UCommonGameLODStreamingComponent::ApplySkeletalMesh(const TWeakObjectPtr<USkeletalMeshComponent>& InComp, const TSoftObjectPtr<USkeletalMesh>& InSoftMesh, bool bReInitPose)
{
	USkeletalMeshComponent* SMC = InComp.Get();
	if (!IsValid(SMC)) return;

	if (InSoftMesh.IsValid())
	{
		USkeletalMesh* Mesh = InSoftMesh.Get();
		if (SMC->GetSkeletalMeshAsset() != Mesh)
			SMC->SetSkeletalMesh(Mesh, bReInitPose);
		return;
	}

	const int32 RequestedLod = CurrentLod;
	const FSoftObjectPath AssetPath = InSoftMesh.ToSoftObjectPath();
	TWeakObjectPtr<UCommonGameLODStreamingComponent> WeakSelf = this;
	TWeakObjectPtr<USkeletalMeshComponent> WeakComp = InComp;
	const bool bLocalReInitPose = bReInitPose;

	UAssetManager::GetStreamableManager().RequestAsyncLoad(AssetPath,
	FStreamableDelegate::CreateWeakLambda(this,
		[WeakSelf, RequestedLod, WeakComp, AssetPath, bLocalReInitPose]()
		{
			UCommonGameLODStreamingComponent* Self = WeakSelf.Get();
			if (!Self || Self->CurrentLod != RequestedLod) return;
			USkeletalMeshComponent* Comp = WeakComp.Get();
			if (!Comp) return;

			USkeletalMesh* LoadedMesh = Cast<USkeletalMesh>(AssetPath.ResolveObject());
			if (!LoadedMesh) return;
			if (Comp->GetSkeletalMeshAsset() == LoadedMesh) return;
			Comp->SetSkeletalMesh(LoadedMesh, bLocalReInitPose);
		}));
}
