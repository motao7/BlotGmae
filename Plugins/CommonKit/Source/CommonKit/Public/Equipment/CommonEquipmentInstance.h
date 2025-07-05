// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonEquipmentInstance.generated.h"

struct FCommonEquipmentActorToSpawn;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class COMMONKIT_API UCommonEquipmentInstance : public UObject
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	//~UObject interface
	virtual bool IsSupportedForNetworking() const override { return true; }
	//~End of UObject interface
	
	UFUNCTION(BlueprintPure, Category=Equipment)
	UObject* GetInstigator() const { return Instigator; }

	UFUNCTION(BlueprintPure, Category=Equipment)
	TArray<AActor*> GetSpawnedActors() const { return SpawnedActors; }

	UFUNCTION(BlueprintPure, Category=Equipment)
	APawn* GetOuterPawn() const;

	void SetInstigator(UObject* InInstigator) { Instigator = InInstigator; }
	
	virtual void OnEquipped();
	virtual void OnUnequipped();
	UFUNCTION(BlueprintImplementableEvent, Category=Equipment, meta=(DisplayName="OnEquipped"))
	void K2_OnEquipped();
	UFUNCTION(BlueprintImplementableEvent, Category=Equipment, meta=(DisplayName="OnUnequipped"))
	void K2_OnUnequipped();

	void SpawnEquipmentActors(const TArray<FCommonEquipmentActorToSpawn>& ActorsToSpawn);

	void DestroyEquipmentActors();
	
private:
	UPROPERTY(Replicated)
	TObjectPtr<UObject> Instigator;

	UPROPERTY(Replicated)
	TArray<TObjectPtr<AActor>> SpawnedActors;
};
