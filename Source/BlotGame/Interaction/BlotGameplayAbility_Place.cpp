// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/BlotGameplayAbility_Place.h"

#include "CommonKitStatics.h"
#include "Equipment/CommonEquipmentInstance.h"
#include "Equipment/CommonQuickBarComponent.h"
#include "Inventory/CIF_PlaceableItem.h"
#include "Inventory/CommonInventoryItemInstance.h"
#include "Physics/BlotCollisionChannel.h"


void UBlotGameplayAbility_Place::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (HasAuthority(&ActivationInfo))
	{
		if (UCommonInventoryItemInstance* InventoryItem = GetAssociatedItem())
		{
			if (const UCIF_PlaceableItem* PlaceableInfo = InventoryItem->FindFragmentByClass<UCIF_PlaceableItem>())
			{
				PlaceActor(PlaceableInfo->PlaceableActorClass, PlaceableInfo->PlacementDistance);
			}
		}
	}
    
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

bool UBlotGameplayAbility_Place::PlaceActor(TSubclassOf<AActor> ActorClassToPlace, float PlacementDistance)
{
	if (!ActorClassToPlace)
	{
		return false;
	}
	
	FTransform SpawnTransform;
	if (!CalculatePlacementTransform(SpawnTransform,PlacementDistance))
	{
		return false;
	}
	
	UWorld* World = GetWorld();
	if (World && World->IsGameWorld())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		if (AActor* SpawnedActor = World->SpawnActor<AActor>(ActorClassToPlace, SpawnTransform, SpawnParams))
		{
			if(UCommonInventoryItemInstance* InventoryItem = GetAssociatedItem())
			{
				if (AController* Controller = GetControllerFromActorInfo())
				{
					if (UCommonInventoryManageComponent* InventoryManager = UCommonKitStatics::GetInventoryManager(Controller->GetPawn()))
					{
						int32 Index=InventoryManager->GetIndexForItemInstance(InventoryItem);
						
						// DecreaseItem
						if (InventoryManager->DecreaseItem(Index,1)==0)
						{
							GetAssociatedEquipment()->DestroyEquipmentActors();
							if (UCommonQuickBarComponent* QuickBar=UCommonKitStatics::GetQuickBarManagerFromController(Controller))
							{
								QuickBar->RemoveItemFromSlot(Index);
							}
						}
					}
				}
			}
			
			return true;
		}
	}

	return false;
}

bool UBlotGameplayAbility_Place::CalculatePlacementTransform(FTransform& OutTransform,float PlacementDistance)
{
	AController* Controller = GetControllerFromActorInfo();
	if (!Controller)
	{
		return false;
	}

	APawn* Pawn = Controller->GetPawn();
	if (!Pawn)
	{
		return false;
	}

	// 获取玩家视角位置和方向
	FVector ViewLocation;
	FRotator ViewRotation;
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    
	FVector ViewDirection = ViewRotation.Vector();
	FVector TraceStart = ViewLocation;
	FVector TraceEnd = TraceStart + (ViewDirection * PlacementDistance);

	// 执行射线检测
	FHitResult HitResult;
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(PlaceActor), true, Pawn);
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.bTraceComplex = false;

	UWorld* World = GetWorld();
	if (!World)
	{
		return false;
	}

	bool bHit = World->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, Blot_TraceChannel_Interaction, TraceParams);

	// 如果没有击中任何物体，则不放置
	if (!bHit || !HitResult.bBlockingHit)
	{
		return false;
	}
	
	FVector HitLocation = HitResult.ImpactPoint;
	FVector HitNormal = HitResult.ImpactNormal;

	// 计算放置位置（在碰撞表面外侧）
	const float GridSize = 100.0f; // 假设方块大小为100单位
	FVector PlacementLocation = HitLocation + (HitNormal * (GridSize * 0.5f));

	// 将位置对齐到网格（Minecraft风格）
	PlacementLocation.X = FMath::GridSnap(PlacementLocation.X, GridSize);
	PlacementLocation.Y = FMath::GridSnap(PlacementLocation.Y, GridSize);
	PlacementLocation.Z = FMath::GridSnap(PlacementLocation.Z, GridSize);

	// 确保方块不会生成在玩家内部
	FVector PlayerLocation = Pawn->GetActorLocation();
	float DistanceToPlayer = FVector::Distance(PlacementLocation, PlayerLocation);
    
	if (DistanceToPlayer < 50.0f) // 避免放置在太靠近玩家的位置
	{
		return false;
	}

	// 设置变换信息：位置对齐到网格，无旋转（Minecraft风格）
	OutTransform.SetLocation(PlacementLocation);
	OutTransform.SetRotation(FQuat::Identity); // 无旋转，保持方正

	return true;
}
