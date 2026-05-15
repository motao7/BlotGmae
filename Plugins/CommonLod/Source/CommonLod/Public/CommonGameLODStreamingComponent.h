// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonGameLodComponent.h"
#include "CommonGameLODStreamingComponent.generated.h"

// ─── 静态 Mesh LOD 数据 ───
USTRUCT(BlueprintType)
struct FGameLODStaticMeshData
{
	GENERATED_BODY()

	/** 运行时缓存，通过 Tag 查找 */
	TWeakObjectPtr<UStaticMeshComponent> CachedComponent;

	/** 在 Owner 上查找对应 StaticMeshComponent 的 Tag */
	UPROPERTY(EditAnywhere)
	FName ComponentTag;

	/** 每级 LOD 对应的 StaticMesh，索引 = LOD 等级 */
	UPROPERTY(EditAnywhere)
	TArray<TSoftObjectPtr<UStaticMesh>> LodMeshList;

	/** 超出 MaxLodDistance 时的替代 Mesh */
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UStaticMesh> OutOfDistanceMesh;
};

// ─── 骨骼 Mesh LOD 数据 ───
USTRUCT(BlueprintType)
struct FGameLODSkeletalMeshData
{
	GENERATED_BODY()

	TWeakObjectPtr<USkeletalMeshComponent> CachedComponent;

	UPROPERTY(EditAnywhere)
	FName ComponentTag;

	UPROPERTY(EditAnywhere)
	bool bReInitPose = false;

	UPROPERTY(EditAnywhere)
	TArray<TSoftObjectPtr<USkeletalMesh>> LodMeshList;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<USkeletalMesh> OutOfDistanceMesh;
};

/**
 * 
 */
UCLASS()
class COMMONLOD_API UCommonGameLODStreamingComponent : public UCommonGameLODComponent
{
	GENERATED_BODY()
	
public:
	UCommonGameLODStreamingComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** Cache its own static mesh components */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FGameLODStaticMeshData> StaticMeshLodData;

	/** Cache its own skeletal mesh components */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FGameLODSkeletalMeshData> SkeletalMeshLodData;

protected:
	virtual void BeginPlay() override;
	virtual void OnLodActive(int32 Lod) override;
	virtual void OnOutOfMaxLodDistance() override;

private:
	void CacheMeshComponents();

	// ─── StaticMesh 异步切换 ───
	void ApplyStaticMesh(
		const TWeakObjectPtr<UStaticMeshComponent>& InComp,
		const TSoftObjectPtr<UStaticMesh>& InSoftMesh);

	// ─── SkeletalMesh 异步切换 ───
	void ApplySkeletalMesh(
		const TWeakObjectPtr<USkeletalMeshComponent>& InComp,
		const TSoftObjectPtr<USkeletalMesh>& InSoftMesh,
		bool bReInitPose);
	
};
