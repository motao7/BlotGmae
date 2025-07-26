// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_SigleTraceTarget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHitTargetChangedEvent, AActor*, NewTarget,AActor*,OldTarget);

/**
 *		Continuous! radiation detection
 */
UCLASS()
class BLOTGAME_API UAbilityTask_SigleTraceTarget : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_SigleTraceTarget* SigleTraceTarget(UGameplayAbility* OwningAbility,float InScanRate=0.1f,float InTraceDistance=1000.f);

	virtual void Activate() override;
	
	UPROPERTY(BlueprintAssignable)
	FHitTargetChangedEvent HitTargetChanged;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	float ScanRate = 0.1f;
	
	/** Player Interaction Max Distance */
	UPROPERTY(EditDefaultsOnly)
	float TraceDistance = 350.f;

	UPROPERTY()
	AActor* CurrentTarget=nullptr;
	
	FTimerHandle QueryTimerHandle;

	void TraceForInteract();
};
