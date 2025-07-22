// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableTarget.h"
#include "InteractionOption.h"
#include "IPickupable.h"
#include "GameFramework/Actor.h"
#include "BlotWorldCollectable.generated.h"


enum class ECollectType : uint8;

/**
 *		
 */
UCLASS(Blueprintable,Abstract)
class BLOTGAME_API ABlotWorldCollectable : public AActor
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void ApplyMining(float Damage, AActor* Instigator);
	
protected:
	void UpdateMaterialBasedOnDurability();

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Collection")
	float MaxDurability = 100.0f;

	UPROPERTY(BlueprintReadWrite,Category="Collection")
	float CurrentDurability;

	UPROPERTY(EditAnywhere,Category="Collection")
	TSubclassOf<AActor> DropItemClass;

	UPROPERTY(EditAnywhere,Category="Collection")
	ECollectType CollectType;
	
};
