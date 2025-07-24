// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/BlotGameplayAbility.h"
#include "BlotGameplayAbility_Interact.generated.h"

struct FInteractionOption;

/**
 *		Interact InteractableActor and Hilight WorldColleableActor
 */
UCLASS()
class BLOTGAME_API UBlotGameplayAbility_Interact : public UBlotGameplayAbility
{
	GENERATED_BODY()
	
public:
	UBlotGameplayAbility_Interact(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	void OnHitTargetChanged(AActor* NewTarget, AActor* OldTarget);
	void OnInteractableTargetChanged(AActor* NewTarget, AActor* OldTarget);
	
	UFUNCTION(BlueprintCallable)
	void TriggerInteraction();

protected:
	UPROPERTY(BlueprintReadOnly,Category="Interaction")
	TArray<FInteractionOption> CurrentOptions;

	UPROPERTY(BlueprintReadOnly,Category="Interaction")
	AActor* CurrentTarget=nullptr;

	TMap<FObjectKey, FGameplayAbilitySpecHandle> InteractionAbilityCache;
};
