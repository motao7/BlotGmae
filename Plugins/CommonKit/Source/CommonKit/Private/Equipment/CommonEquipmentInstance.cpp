// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/CommonEquipmentInstance.h"

#include "Equipment/CommonEquipmentDefinition.h"
#include "GameFramework/Character.h"

void UCommonEquipmentInstance::SpawnEquipmentActors(const TArray<FCommonEquipmentActorToSpawn>& ActorsToSpawn)
{
	if (APawn* OwningPawn = GetOuterPawn())
	{
		USceneComponent* AttachTarget = OwningPawn->GetRootComponent();
		if (ACharacter* Char = Cast<ACharacter>(OwningPawn))
		{
			AttachTarget = Char->GetMesh();
		}

		for (const FCommonEquipmentActorToSpawn& SpawnInfo : ActorsToSpawn)
		{
			AActor* NewActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnInfo.ActorToSpawn, FTransform::Identity, OwningPawn);
			NewActor->FinishSpawning(FTransform::Identity, /*bIsDefaultTransform=*/ true);
			NewActor->SetActorRelativeTransform(SpawnInfo.AttachTransform);
			NewActor->AttachToComponent(AttachTarget, FAttachmentTransformRules::KeepRelativeTransform, SpawnInfo.AttachSocket);
		}
	}
}

void UCommonEquipmentInstance::OnEquipped()
{
	K2_OnEquipped();
}

void UCommonEquipmentInstance::OnUnequipped()
{
	K2_OnUnequipped();
}

APawn* UCommonEquipmentInstance::GetOuterPawn() const
{
	return Cast<APawn>(GetOuter());
}
