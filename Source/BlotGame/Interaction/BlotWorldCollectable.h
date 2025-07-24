// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableTarget.h"
#include "InteractionOption.h"
#include "IPickupable.h"
#include "GameFramework/Actor.h"
#include "BlotWorldCollectable.generated.h"


class ADroppedItem;
class UCommonCollectInstance;
enum class ECollectType : uint8;

/**
 *		
 */
UCLASS(Blueprintable,Abstract)
class BLOTGAME_API ABlotWorldCollectable : public AActor
{
	GENERATED_BODY()

public:
	ABlotWorldCollectable(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable,BlueprintCosmetic,Category="WorldCollectable")
	void SetHighlight(bool bEnable);

	UFUNCTION(BlueprintCallable,BlueprintCosmetic,Category="WorldCollectable")
	void StartDamage(UCommonCollectInstance* CollectInstance);

	/**Back to Initialize State*/
	UFUNCTION(BlueprintCallable,BlueprintCosmetic,Category="WorldCollectable")
	void EndDamage();

protected:
	void TickDamage();

	UFUNCTION(BlueprintAuthorityOnly)
	void OnOutOfDurablity();

	UFUNCTION(BlueprintImplementableEvent,Category="WorldCollectable")
	void K2_OnOutOfDurablity();
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditAnywhere,Category="WorldCollectable")
	int32 MaxDurability=100;

	UPROPERTY(BlueprintReadOnly,Category="WorldCollectable")
	int32 Durability=100;
	
	UPROPERTY(EditAnywhere,Category="WorldCollectable")
	float HandDamageRate=1.f;

	UPROPERTY(EditAnywhere,Category="WorldCollectable")
	TSubclassOf<ADroppedItem> DropItemClass;

	UPROPERTY(EditAnywhere,Category="WorldCollectable")
	FGameplayTag CollectType;

	UPROPERTY(EditAnywhere,Category="WorldCollectable")
	UMaterialInterface* OverlyMaterial;
	
	UPROPERTY(Transient)
	UMaterialInstanceDynamic* CollectOverlayDynamicMaterial;
	
	FTimerHandle DamageTimerHandle;
	
};
