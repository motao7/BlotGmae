// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/DroppedItem.h"

#include "CommonKitStatics.h"
#include "InteractionStatics.h"
#include "Character/BlotCharacter.h"
#include "Components/BoxComponent.h"

ADroppedItem::ADroppedItem()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = MeshComponent;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetBoundsScale(10.f);
}

FPickupInventory ADroppedItem::GetPickupInventory() const
{
	return StaticPickupInventory;
}

void ADroppedItem::BeginPlay()
{
	Super::BeginPlay();

	StartLocation=GetActorLocation();

	if (HasAuthority())
	{
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADroppedItem::OnPickupOverlap);	
	}
}

void ADroppedItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;
	float Offset = FMath::Sin(RunningTime * FloatingFrequency) * FloatingAmplitude;
	SetActorLocation( StartLocation+ FVector(0, 0, Offset));
	AddActorLocalRotation(FRotator(0, RotationSpeed * DeltaTime, 0));
}

void ADroppedItem::OnPickupOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABlotCharacter* BlotCharacter=Cast<ABlotCharacter>(OtherActor))
	{
		UInteractionStatics::AddPickupToInventory(UCommonKitStatics::GetInventoryManager(BlotCharacter),this);
		Destroy();
	}
}
