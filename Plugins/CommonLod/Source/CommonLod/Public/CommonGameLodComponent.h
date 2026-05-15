// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CommonGameLodComponent.generated.h"

// ─── 区域类型 ───
UENUM(BlueprintType)
enum class EGameLODRegionType : uint8
{
	NoneRegion,
	WeaponWrapper,
	Character,
	// 可扩展
};

// ─── 区域配置 ───
struct FGameLODRegionData
{
	EGameLODRegionType Type = EGameLODRegionType::NoneRegion;
	float SideLength = 0.f;
	FLinearColor DebugColor;

	FGameLODRegionData() = default;
	FGameLODRegionData(EGameLODRegionType InType, float InSideLength, FLinearColor InColor)
		: Type(InType), SideLength(InSideLength), DebugColor(InColor) {}
};

// ─── 性能适配委托（外部可绑定，如接入自己的性能监控） ───
DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FOnPerformanceAdaptationCheck);

//每个 SimulatedProxy 角色挂一个
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMMONLOD_API UCommonGameLODComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCommonGameLODComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** LOD 最大作用距离 (cm) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxLodDistance = 100.f;

	/** 每级 LOD 占 MaxLodDistance 的比例，从近到远累加
	 *  例: [0.3, 0.3, 0.4] → 近30%为LOD0, 中30%为LOD1, 远40%为LOD2 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<float> LodRate;

	UPROPERTY(EditAnywhere)
	bool bEnableLog = false;

	UPROPERTY(EditAnywhere)
	bool bEnableDebug = false;

	// ─── 运行时状态 ───
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentPlayerDistance = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentLod = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 MaxLod = -1;

	bool bOutOfMaxLodDistance = false;

	// ─── 虚函数接口（子类覆写） ───
	virtual void OnLodActive(int32 Lod) {}
	virtual void OnOutOfMaxLodDistance();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	TWeakObjectPtr<AActor> OwnerActor;

public:
	/** 由 Manager 调用：根据距离计算并设置 LOD 等级 */
	void ProcessDistance(float Distance);

private:
	void SetActiveLod(int32 Lod);

	// ═══════════════════════════════════════
	//  2D 空间网格（静态，所有实例共享）
	// ═══════════════════════════════════════
public:
	UPROPERTY(EditAnywhere)
	EGameLODRegionType RegionType = EGameLODRegionType::NoneRegion;

	static bool GetRegionComponents(
		EGameLODRegionType InType,
		AActor* QueryActor,
		TArray<UCommonGameLODComponent*>& OutComponents);

public:
	// 全局配置
	static TMap<EGameLODRegionType, FGameLODRegionData> RegionConfigMap;
	// 不分区域的组件列表
	static TArray<UCommonGameLODComponent*> NoRegionComponents;
	// 三级嵌套：RegionType → X → Y → Component[]
	static TMap<EGameLODRegionType, TMap<int32, TMap<int32, TArray<UCommonGameLODComponent*>>>> RegionGrid;

	static void InitRegionConfig();

	/** 世界坐标值（Value）X.Y.Z - 转换成格子索引（Cell Index） */
	static int32 WorldToCellIndex(float Value, float CellSize);
	void RegisterToGrid();
	void UnregisterFromGrid();

	int32 CellX = 0;
	int32 CellY = 0;
};
