// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoxelGenerator.generated.h"

class UHierarchicalInstancedStaticMeshComponent;

UCLASS()
class VOXEL_API AVoxelGenerator : public AActor
{
	GENERATED_BODY()

public:
	AVoxelGenerator();

protected:
	virtual void BeginPlay() override;

	// 异步生成地形数据
	void GenerateVoxelWorldAsync();

	// 添加体素实例
	void ApplyVoxelInstances(const TArray<FTransform>& InstanceTransforms);

public:
	UPROPERTY(EditAnywhere, Category = "Voxel")
	int32 SizeX = 64;

	UPROPERTY(EditAnywhere, Category = "Voxel")
	int32 SizeY = 64;

	UPROPERTY(EditAnywhere, Category = "Voxel")
	int32 SizeZ = 32;

	UPROPERTY(EditAnywhere, Category = "Voxel")
	float NoiseScale = 0.05f;

	UPROPERTY(EditAnywhere, Category = "Voxel")
	float NoiseThreshold = 0.3f;

	UPROPERTY(EditAnywhere, Category = "Voxel")
	float CubeSpace = 50.f;

	UPROPERTY(EditAnywhere, Category = "Voxel")
	float CubeScaleFactor = 2.0f;

private:
	UPROPERTY(VisibleAnywhere, Category = "Voxel")
	UHierarchicalInstancedStaticMeshComponent* HISM;

	// 维护一个映射：方块坐标→HISM实例索引
	TMap<FIntVector, int32> VoxelInstanceMap;
};