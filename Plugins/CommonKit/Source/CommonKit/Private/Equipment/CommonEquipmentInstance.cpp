// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/CommonEquipmentInstance.h"

#include "Equipment/CommonEquipmentDefinition.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

void UCommonEquipmentInstance::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, Instigator);
	DOREPLIFETIME(ThisClass, SpawnedActors);
}

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
			NewActor->AttachToComponent(AttachTarget, FAttachmentTransformRules::KeepRelativeTransform, SpawnInfo.AttachSocket);
			NewActor->SetActorRelativeTransform(SpawnInfo.AttachTransform);
			SpawnedActors.Add(NewActor);
		}
	}
}

void UCommonEquipmentInstance::OnEquipped()
{
	K2_OnEquipped();

	if (ACharacter* Character=Cast<ACharacter>(GetOuterPawn()))
	{
		Character->GetMesh()->LinkAnimClassLayers(AnimLayer);
	}
}

void UCommonEquipmentInstance::OnUnequipped()
{
	K2_OnUnequipped();
}

APawn* UCommonEquipmentInstance::GetOuterPawn() const
{
	return Cast<APawn>(GetOuter());
}

void UCommonEquipmentInstance::DestroyEquipmentActors()
{
	for (AActor* Actor : SpawnedActors)
	{
		if (Actor)
		{
			Actor->Destroy();
		}
	}
}
