// Fill out your copyright notice in the Description page of Project Settings.

#include "VoxelGenerator.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Async/Async.h"

AVoxelGenerator::AVoxelGenerator()
{
	PrimaryActorTick.bCanEverTick = false;

	HISM = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("VoxelHISM"));
	SetRootComponent(HISM);
	HISM->SetMobility(EComponentMobility::Static);
}

void AVoxelGenerator::BeginPlay()
{
	Super::BeginPlay();
	GenerateVoxelWorldAsync();
}

void AVoxelGenerator::GenerateVoxelWorldAsync()
{
	const int32 XMax = SizeX;
	const int32 YMax = SizeY;
	const int32 ZMax = SizeZ;
	const float Scale = NoiseScale;
	const float Threshold = NoiseThreshold;
	const float Space = CubeSpace;
	const float ScaleFactor = CubeScaleFactor;

	// 多线程任务
	Async(EAsyncExecution::ThreadPool, [this, XMax, YMax, ZMax, Scale, Threshold, Space, ScaleFactor]()
	{
		TArray<FTransform> Transforms;
		FCriticalSection Mutex;

		ParallelFor(XMax, [=, &Transforms, &Mutex](int32 X)
		{
			TArray<FTransform> LocalTransforms; // 每个线程独立本地数组
			for (int32 Y = 0; Y < YMax; ++Y)
			{
				for (int32 Z = 0; Z < ZMax; ++Z)
				{
					const FVector NoisePos = FVector(X * Scale, Y * Scale, Z * Scale);
					const float NoiseValue = FMath::PerlinNoise3D(NoisePos);

					if (NoiseValue > Threshold)
					{
						const FVector Location = FVector(X * Space, Y * Space, Z * Space);
						FTransform Transform;
						Transform.SetLocation(Location);
						Transform.SetScale3D(FVector(ScaleFactor));
						LocalTransforms.Add(Transform);
					}
				}
			}

			// 合并当前线程的结果进共享数组
			FScopeLock Lock(&Mutex);
			Transforms.Append(LocalTransforms);
		});

		AsyncTask(ENamedThreads::GameThread, [this,Transforms]()
		{
			ApplyVoxelInstances(Transforms);
		});
	});
}

void AVoxelGenerator::ApplyVoxelInstances(const TArray<FTransform>& InstanceTransforms)
{
	if (!HISM->GetStaticMesh())
	{
		UE_LOG(LogTemp, Warning, TEXT("VoxelMesh is not set."));
		return;
	}

	//TODO:裁决天中的Instance的位置
	HISM->AddInstances(InstanceTransforms, false,true,false);
	HISM->MarkRenderStateDirty();         // 最后再更新一次
}
