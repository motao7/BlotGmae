// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonGameLodComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogCommonGameLOD, Log, All);
DECLARE_STATS_GROUP(TEXT("CommonGameLOD"), STATGROUP_CommonGameLOD, STATCAT_Advanced);
DECLARE_CYCLE_STAT(TEXT("CommonGameLOD OnLodActive"), STAT_CommonGameLOD_OnLodActive, STATGROUP_CommonGameLOD);

// ─── 静态成员初始化 ───
TMap<EGameLODRegionType, FGameLODRegionData> UCommonGameLODComponent::RegionConfigMap;
TArray<UCommonGameLODComponent*> UCommonGameLODComponent::NoRegionComponents;
TMap<EGameLODRegionType, TMap<int32, TMap<int32, TArray<UCommonGameLODComponent*>>>> UCommonGameLODComponent::RegionGrid;

UCommonGameLODComponent::UCommonGameLODComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	RegionType = EGameLODRegionType::NoneRegion;
}

void UCommonGameLODComponent::InitRegionConfig()
{
	if (RegionConfigMap.Num() > 0) return;
	RegionConfigMap.Add(EGameLODRegionType::NoneRegion,
		FGameLODRegionData(EGameLODRegionType::NoneRegion, 1e8f, FLinearColor::Blue));
	RegionConfigMap.Add(EGameLODRegionType::WeaponWrapper,
		FGameLODRegionData(EGameLODRegionType::WeaponWrapper, 1000.f, FLinearColor::Green));
	RegionConfigMap.Add(EGameLODRegionType::Character,
		FGameLODRegionData(EGameLODRegionType::Character, 1300.f, FLinearColor::Yellow));
}

// ─── BeginPlay：仅客户端 SimulatedProxy 注册 ───
void UCommonGameLODComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetNetMode() != NM_Client) return;
	if (GetOwnerRole() != ROLE_SimulatedProxy) return;

	InitRegionConfig();
	OwnerActor = GetOwner();
	MaxLod = LodRate.Num();
	RegisterToGrid();
}

void UCommonGameLODComponent::OnOutOfMaxLodDistance()
{
}

void UCommonGameLODComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (GetNetMode() == NM_Client && GetOwnerRole() == ROLE_SimulatedProxy)
	{
		UnregisterFromGrid();
		OwnerActor = nullptr;
	}
	Super::EndPlay(EndPlayReason);
}

void UCommonGameLODComponent::ProcessDistance(float Distance)
{
	CurrentPlayerDistance = Distance;

	if (Distance>MaxLodDistance)
	{
		if (!bOutOfMaxLodDistance)
		{
			bOutOfMaxLodDistance = true;
			OnOutOfMaxLodDistance();
		}
		return;
	}

	bOutOfMaxLodDistance=false;

	if (LodRate.Num() == 0)
	{
		SetActiveLod(0);
		return;
	}

	// 从远到近累加 LodRate，找到对应 LOD 等级
	float TotalRate = 0.f;
	for (int32 i = LodRate.Num() - 1; i >= 0; i--)
	{
		TotalRate += LodRate[i];
		if (CurrentPlayerDistance > (1.f - TotalRate) * MaxLodDistance)
		{
			SetActiveLod(i + 1);
			return;
		}
	}
	SetActiveLod(0);
}

void UCommonGameLODComponent::SetActiveLod(int32 Lod)
{
	if (CurrentLod == Lod) return;
	CurrentLod = Lod;

	UE_LOG(LogCommonGameLOD, Verbose, TEXT("SetActiveLod %d for %s"), Lod,
		OwnerActor.IsValid() ? *OwnerActor->GetName() : TEXT("Invalid"));

	{
		SCOPE_CYCLE_COUNTER(STAT_CommonGameLOD_OnLodActive);
		OnLodActive(CurrentLod);
	}
}

bool UCommonGameLODComponent::GetRegionComponents(EGameLODRegionType InType, AActor* QueryActor, TArray<UCommonGameLODComponent*>& OutComponents)
{
	if (InType == EGameLODRegionType::NoneRegion)
	{
		OutComponents = NoRegionComponents;
		return OutComponents.Num() > 0;
	}

	const FGameLODRegionData* Config = RegionConfigMap.Find(InType);
	if (!Config || !IsValid(QueryActor)) return false;

	auto* TypeMap = RegionGrid.Find(InType);
	if (!TypeMap) return false;

	const FVector Location = QueryActor->GetActorLocation();
	const int32 CX = WorldToCellIndex(Location.X, Config->SideLength);
	const int32 CY = WorldToCellIndex(Location.Y, Config->SideLength);

	bool bFound = false;
	// 3x3 邻域查询
	auto TryCell = [&](int32 X, int32 Y)
	{
		auto* XMap = TypeMap->Find(X);
		if (!XMap) return;
		auto* YArray = XMap->Find(Y);
		if (!YArray || YArray->Num() == 0) return;
		bFound = true;
		OutComponents.Append(*YArray);
	};

	TryCell(CX,     CY);
	TryCell(CX,     CY - 1);
	TryCell(CX,     CY + 1);
	TryCell(CX - 1, CY);
	TryCell(CX - 1, CY - 1);
	TryCell(CX - 1, CY + 1);
	TryCell(CX + 1, CY);
	TryCell(CX + 1, CY + 1);
	TryCell(CX + 1, CY - 1);

	return bFound;
}

int32 UCommonGameLODComponent::WorldToCellIndex(float Value, float CellSize)
{
	const float AbsVal = FMath::Abs(Value);
	const float Sign = Value < 0 ? -1.f : 1.f;
	const int32 Num = FMath::FloorToInt(AbsVal / CellSize);
	const float Mod = AbsVal - CellSize * Num;
	// 靠近格子中心偏移：超过半格归到下一格
	return (Mod > CellSize * 0.5f) ? (Num + 1) * Sign : Num * Sign;
}

void UCommonGameLODComponent::RegisterToGrid()
{
	if (RegionType == EGameLODRegionType::NoneRegion)
	{
		NoRegionComponents.AddUnique(this);
		return;
	}

	if (!OwnerActor.IsValid()) return;

	const FGameLODRegionData* Config = RegionConfigMap.Find(RegionType);
	if (!Config) return;

	const FVector Location = OwnerActor->GetActorLocation();
	const int32 CurCellX = WorldToCellIndex(Location.X, Config->SideLength);
	const int32 CurCellY = WorldToCellIndex(Location.Y, Config->SideLength);

	// 先从旧格子移除，再注册新格子
	UnregisterFromGrid();

	RegionGrid.FindOrAdd(RegionType)
		.FindOrAdd(CurCellX)
		.FindOrAdd(CurCellY)
		.Add(this);

	CellX = CurCellX;
	CellY = CurCellY;
}

void UCommonGameLODComponent::UnregisterFromGrid()
{
	if (RegionType == EGameLODRegionType::NoneRegion)
	{
		NoRegionComponents.Remove(this);
		return;
	}

	auto* TypeMap = RegionGrid.Find(RegionType);
	if (!TypeMap) return;
	auto* XMap = TypeMap->Find(CellX);
	if (!XMap) return;
	auto* YArray = XMap->Find(CellY);
	if (!YArray) return;

	YArray->Remove(this);
}


