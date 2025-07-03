// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BlotAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class BLOTGAME_API UBlotAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UBlotAbilitySystemComponent();
	
	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;
	void TryActivateAbilitiesOnSpawn();

	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	void ProcessAbilityInput(float DeltaTime, bool bGamePaused);
	void ClearAbilityInput();

protected:
	// We don't support UGameplayAbility::bReplicateInputDirectly. So use these function below to Invoke WaitInputReleased/Pressed 
	virtual void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) override;
	virtual void AbilitySpecInputReleased(FGameplayAbilitySpec& Spec) override;

	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;
	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;
	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;

};

