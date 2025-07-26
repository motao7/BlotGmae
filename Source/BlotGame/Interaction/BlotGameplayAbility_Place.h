// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/BlotGameplayAbility_FromEquipment.h"
#include "BlotGameplayAbility_Place.generated.h"

/**
 * 
 */
UCLASS()
class BLOTGAME_API UBlotGameplayAbility_Place : public UBlotGameplayAbility_FromEquipment
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	bool PlaceActor(TSubclassOf<AActor> ActorClassToPlace, float PlacementDistance);
	
	bool CalculatePlacementTransform(FTransform& OutTransform, float PlacementDistance);
};
