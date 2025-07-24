// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/BlotWorldCollectable.h"

#include "DroppedItem.h"
#include "NativeGameplayTags.h"
#include "Collection/CommonCollectInstance.h"
#include "Inventory/CommonInventoryItemInstance.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(Blot_Collect_Speed,"Blot.Collect.Speed");

ABlotWorldCollectable::ABlotWorldCollectable(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, MeshComponent(nullptr)
	, CollectType()
{
	RootComponent=MeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

void ABlotWorldCollectable::SetHighlight(bool bEnable)
{
	if (MeshComponent)
	{
		if (bEnable)
		{
			CollectOverlayDynamicMaterial = UMaterialInstanceDynamic::Create(OverlyMaterial, this);
			MeshComponent->SetOverlayMaterial(CollectOverlayDynamicMaterial);
		}
		else
		{
			MeshComponent->SetOverlayMaterial(nullptr);
		}
	}
}

void ABlotWorldCollectable::StartDamage(UCommonCollectInstance* CollectInstance)
{
	if (CollectInstance==nullptr)
	{
		GetWorldTimerManager().SetTimer(DamageTimerHandle,this,&ThisClass::TickDamage,HandDamageRate,true);
	}
	else
	{
		if (UCommonInventoryItemInstance* InventoryInstance=CollectInstance->GetAssociateInventoryInstance())
		{
			if (InventoryInstance->HasStatTag(Blot_Collect_Speed))
			{
				float CollectSpeed=InventoryInstance->GetStatTagStackCount(Blot_Collect_Speed);
				float ResultSpeed=1/CollectSpeed;
				GetWorldTimerManager().SetTimer(DamageTimerHandle,this,&ThisClass::TickDamage,ResultSpeed,true);
			}
		}
	}
}

void ABlotWorldCollectable::EndDamage()
{
	GetWorldTimerManager().ClearTimer(DamageTimerHandle);
	
	if (OverlyMaterial&&CollectOverlayDynamicMaterial)
	{
		FLinearColor CurrentColor(1,1,1);
		CollectOverlayDynamicMaterial->SetVectorParameterValue("Color", CurrentColor);
	}
}

void ABlotWorldCollectable::TickDamage()
{
	Durability -=10;

	if (CollectOverlayDynamicMaterial)
	{
		FLinearColor CurrentColor;
		CollectOverlayDynamicMaterial->GetVectorParameterValue(FMaterialParameterInfo("Color"), CurrentColor);
		
		CurrentColor.R = (MaxDurability-Durability)/4;
		CollectOverlayDynamicMaterial->SetVectorParameterValue("Color", CurrentColor);
	}

	if (HasAuthority())
	{
		if (Durability<=0)
		{
			OnOutOfDurablity();	
		}
	}
}

void ABlotWorldCollectable::OnOutOfDurablity()
{
	K2_OnOutOfDurablity();

	if (DropItemClass) 
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ADroppedItem* DropItem = GetWorld()->SpawnActor<ADroppedItem>(DropItemClass, GetActorLocation(), FRotator::ZeroRotator, Params);
	}

	Destroy();
}

