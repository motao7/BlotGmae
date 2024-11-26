// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularCharacter.h"
#include "BlotCharacter.generated.h"

class UBlotPawnExtensionComponent;
/**
 * 
 */
UCLASS()
class BLOTGAME_API ABlotCharacter : public AModularCharacter
{
	GENERATED_BODY()

public:
	ABlotCharacter(const FObjectInitializer& ObjectInitializer);
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lyra|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBlotPawnExtensionComponent> PawnExtensionComponent;
};
