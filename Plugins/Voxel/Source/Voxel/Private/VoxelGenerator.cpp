// Fill out your copyright notice in the Description page of Project Settings.

#include "VoxelGenerator.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Async/Async.h"
#include "Kismet/GameplayStatics.h"

AWorldGenerator::AWorldGenerator()
{
    PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bStartWithTickEnabled = false;
}

void AWorldGenerator::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		GenerateVoxelWorldAsync();
	}
}

void AWorldGenerator::GenerateVoxelWorldAsync()
{
	const int32 XMax = SizeX;
	const int32 YMax = SizeY;
	const int32 ZMax = SizeZ;
	const float Scale = NoiseScale;
	const float Threshold = NoiseThreshold;
	const float Space = CubeSpace;
	const float ScaleFactor = CubeScaleFactor;

	// 获取玩家位置
	FVector PlayerLocation = FVector::ZeroVector;
	if (AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		PlayerLocation = PlayerActor->GetActorLocation();
	}

	const float SpawnRadiusSq = SpawnRadius * SpawnRadius;      // 总生成半径平方
	const float NoSpawnRadiusSq = NonSpawnRadius * NonSpawnRadius; // 玩家出生点保护区半径平方

	UWorld* World = GetWorld();
	if (!World || !WorldCollectClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("World or WorldCollectClass not valid!"));
		return;
	}

	for (int32 Y = 0; Y < YMax; ++Y)
	{
		for (int32 Z = 0; Z < ZMax; ++Z)
		{
			for (int32 X = 0; X < XMax; ++X)
			{
				FVector Location = FVector(X * Space, Y * Space, Z * Space);

				// 距离玩家太远不生成
				if (FVector::DistSquared(Location, PlayerLocation) > SpawnRadiusSq)
				{
					continue;
				}

				// 玩家出生点附近保护区不生成方块
				if (FVector::DistSquared(Location, PlayerLocation) < NoSpawnRadiusSq)
				{
					continue;
				}

				FVector NoisePos = FVector(X * Scale, Y * Scale, Z * Scale);
				float NoiseValue = FMath::PerlinNoise3D(NoisePos);

				// 矿洞是噪声值低于阈值的区域，阈值以上生成方块（石头）
				if (NoiseValue > Threshold)
				{
					FTransform Transform;
					Transform.SetLocation(Location);
					Transform.SetScale3D(FVector(ScaleFactor));

					World->SpawnActor<AActor>(WorldCollectClass, Transform);
				}
			}
		}
	}
}
void AWorldGenerator::SpawnWorldCollectActors(const TArray<FTransform>& InstanceTransforms)
{
    UWorld* World = GetWorld();
    if (!World || !WorldCollectClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("World or WorldCollectClass is not valid."));
        return;
    }

    for (const FTransform& Transform : InstanceTransforms)
    {	
    }
}