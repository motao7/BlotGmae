// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponSpawner.generated.h"

class UCapsuleComponent;
class UCommonInventoryItemDefinition;
class UCommonWeaponPickupDefinition;

UCLASS()
class COMMONKIT_API AWeaponSpawner : public AActor
{
	GENERATED_BODY()
	
public:
	AWeaponSpawner();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	UFUNCTION(BlueprintNativeEvent)
	void AttemptPickUpWeapon(APawn* Pawn);

	UFUNCTION(BlueprintImplementableEvent, Category = "CommonKit|WeaponPickup")
	bool GiveWeapon(TSubclassOf<UCommonInventoryItemDefinition> WeaponItemDefination, APawn* ReceivingPawn);

	void SetWeaponPickupVisibility(bool bShouldBeVisible);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CommonKit|WeaponPickup")
	TObjectPtr<UCapsuleComponent> CollisionVolume;

	UPROPERTY(BlueprintReadOnly, Category = "CommonKit|WeaponPickup")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

protected:
	UFUNCTION()
	void OnRep_WeaponAvailability();
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "CommonKit|WeaponPickup")
	TObjectPtr<UCommonWeaponPickupDefinition> WeaponPickUpDefinition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, ReplicatedUsing = OnRep_WeaponAvailability, Category = "CommonKit|WeaponPickup")
	bool bIsWeaponAvailable;
};
