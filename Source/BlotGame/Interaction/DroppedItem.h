// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPickupable.h"
#include "GameFramework/Actor.h"
#include "DroppedItem.generated.h"

class UBoxComponent;

UCLASS(Blueprintable,Abstract)
class BLOTGAME_API ADroppedItem : public AActor,public IPickupable
{
	GENERATED_BODY()

public:
	ADroppedItem();
	
	UFUNCTION(BlueprintCallable, Category = "Dropped Item")
	virtual FPickupInventory GetPickupInventory() const override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintAuthorityOnly)
	void OnPickupOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, Category = "Dropped Item")
	FPickupInventory StaticPickupInventory;
	
	UPROPERTY(EditDefaultsOnly, Category = "Dropped Item")
	float FloatingAmplitude = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Dropped Item")
	float FloatingFrequency = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Dropped Item")
	float RotationSpeed = 50.0f;

	float RunningTime;

	FVector StartLocation;
};
