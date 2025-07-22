// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "IPickupable.generated.h"

class UCommonInventoryItemDefinition;
class UCommonInventoryItemInstance;

USTRUCT(BlueprintType)
struct FPickupInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ItemCount;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UCommonInventoryItemInstance> Item = nullptr;
};

USTRUCT(BlueprintType)
struct FPickupTemplate
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int32 StackCount = 1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCommonInventoryItemDefinition> ItemDef;
};

USTRUCT(BlueprintType)
struct FPickupInventory
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FPickupInstance> Instances;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FPickupTemplate> Templates;
};


UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UPickupable : public UInterface
{
	GENERATED_BODY()
	
};

/**
 *		
 */
class BLOTGAME_API IPickupable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual FPickupInventory GetPickupInventory() const = 0;
	
};
