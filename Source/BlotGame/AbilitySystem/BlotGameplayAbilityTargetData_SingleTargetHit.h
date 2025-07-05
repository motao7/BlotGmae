// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "BlotGameplayAbilityTargetData_SingleTargetHit.generated.h"

/**
 * 
 */
USTRUCT()
struct BLOTGAME_API FBlotGameplayAbilityTargetData_SingleTargetHit:public FGameplayAbilityTargetData_SingleTargetHit
{
	GENERATED_BODY()
	
	FBlotGameplayAbilityTargetData_SingleTargetHit()
		: CartridgeID(-1)
	{ }

	virtual void AddTargetDataToContext(FGameplayEffectContextHandle& ContextHandle, bool bIncludeActorArray) const override;

	/** ID to allow the identification of multiple bullets that were part of the same cartridge */
	UPROPERTY()
	int32 CartridgeID;

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FBlotGameplayAbilityTargetData_SingleTargetHit::StaticStruct();
	}
};

template<>
struct TStructOpsTypeTraits<FBlotGameplayAbilityTargetData_SingleTargetHit> : public TStructOpsTypeTraitsBase2<FBlotGameplayAbilityTargetData_SingleTargetHit>
{
	enum
	{
		WithNetSerializer = true	// For now this is REQUIRED for FGameplayAbilityTargetDataHandle net serialization to work
	};
};