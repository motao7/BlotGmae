// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/BlotGameplayAbility.h"
#include "BlotGameplayAbility_Interact.generated.h"

struct FInteractionOption;
/**
 * 
 */
UCLASS()
class BLOTGAME_API UBlotGameplayAbility_Interact : public UBlotGameplayAbility
{
	GENERATED_BODY()
	
public:
	UBlotGameplayAbility_Interact(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable)
	void UpdateInteractions(const TArray<FInteractionOption>& InteractiveOptions);

	UFUNCTION(BlueprintCallable)
	void TriggerInteraction();

protected:
	UPROPERTY(EditDefaultsOnly)
	float InteractionScanRate = 0.1f;

	UPROPERTY(EditDefaultsOnly)
	float InteractionScanRange = 500;

	UPROPERTY(BlueprintReadWrite)
	TArray<FInteractionOption> CurrentOptions;

};
