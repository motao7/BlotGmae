// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExperienceAbilitySet.h"
#include "GameplayAbilitySpecHandle.h"
#include "Components/ActorComponent.h"
#include "BlotParryComponent.generated.h"


class UGameplayEffect;
struct FGameplayTag;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActiveParrySignature,bool,SuccessParry);

/**
 *		Attach to Character
 */
UCLASS(Blueprintable, Meta=(BlueprintSpawnableComponent))
class BLOTGAME_API UBlotParryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category="Parry")
	void OpenParryWindow(AActor* HitActor);

	UFUNCTION(BlueprintCallable,Category="Parry")
	void CloseParryWindow();

	UFUNCTION(BlueprintCallable,Category="Parry")
	void OnActiveParr(bool SuccessParry);
	
	UPROPERTY(BlueprintAssignable,Category="Parry")
	FOnActiveParrySignature OnActiveParryDelegate;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Parry")
	FExperienceAbilitySet_GameplayAbility ParryAbilitySet;

	UPROPERTY(BlueprintReadOnly,Category="Parry")
	TArray<AActor*> HitActors;
	
	FGameplayAbilitySpecHandle CurrentParryAbilitySpec;

	bool bSuccessParry;
	
};
