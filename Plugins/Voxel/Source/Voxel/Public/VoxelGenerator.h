// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoxelGenerator.generated.h"

USTRUCT()
struct FChunkKey
{
    GENERATED_BODY()
    int32 X, Y, Z;
    bool operator==(FChunkKey const& Other) const { return X==Other.X && Y==Other.Y && Z==Other.Z; }
};
FORCEINLINE uint32 GetTypeHash(const FChunkKey& K)
{
    return HashCombine(HashCombine(::GetTypeHash(K.X), ::GetTypeHash(K.Y)), ::GetTypeHash(K.Z));
}

USTRUCT()
struct FCollectableSpawnInfo
{
    GENERATED_BODY()
    FVector Location;
    FRotator Rotation;
    TSubclassOf<AActor> CollectableClass;
    int32 InstanceID; // optional id for pooling
};

UCLASS(Blueprintable)
class VOXEL_API AWorldGenerator : public AActor
{
    GENERATED_BODY()
public:
    AWorldGenerator();

protected:
    virtual void BeginPlay() override;
    void GenerateVoxelWorldAsync();
	void SpawnWorldCollectActors(const TArray<FTransform>& InstanceTransforms);

    // 体素大小
	UPROPERTY(EditAnywhere, Category="Voxel")
	int32 SizeX = 32;

	UPROPERTY(EditAnywhere, Category="Voxel")
	int32 SizeY = 32;

	UPROPERTY(EditAnywhere, Category="Voxel")
	int32 SizeZ = 32;

	// 噪声缩放和阈值
	UPROPERTY(EditAnywhere, Category="Voxel")
	float NoiseScale = 0.05f;

	UPROPERTY(EditAnywhere, Category="Voxel")
	float NoiseThreshold = 0.3f;

	// 方块间距，世界坐标单位，比如100代表1米
	UPROPERTY(EditAnywhere, Category="Voxel")
	float CubeSpace = 100.0f;

	// 方块缩放比例
	UPROPERTY(EditAnywhere, Category="Voxel")
	float CubeScaleFactor = 1.0f;

	// 用于Spawn的WorldCollect蓝图类
	UPROPERTY(EditAnywhere, Category="Voxel")
	TSubclassOf<AActor> WorldCollectClass;

	UPROPERTY(EditAnywhere, Category="Voxel")
	float SpawnRadius=5000.0f;

	UPROPERTY(EditAnywhere, Category="Voxel")
	float NonSpawnRadius=500.0f;
};