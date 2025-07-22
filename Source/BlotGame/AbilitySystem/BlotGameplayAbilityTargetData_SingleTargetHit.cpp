// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BlotGameplayAbilityTargetData_SingleTargetHit.h"

#include "BlotGameplayEffectContext.h"

void FBlotGameplayAbilityTargetData_SingleTargetHit::AddTargetDataToContext(FGameplayEffectContextHandle& ContextHandle, bool bIncludeActorArray) const
{
	FGameplayAbilityTargetData_SingleTargetHit::AddTargetDataToContext(ContextHandle, bIncludeActorArray);

	// Add game-specific data
	if (FBlotGameplayEffectContext* TypedContext = FBlotGameplayEffectContext::ExtractEffectContext(ContextHandle))
	{
		TypedContext->SetCartridgeID(CartridgeID);
		TypedContext->AddHitResults(HitResult);
	}
}

bool FBlotGameplayAbilityTargetData_SingleTargetHit::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	FGameplayAbilityTargetData_SingleTargetHit::NetSerialize(Ar, Map, bOutSuccess);

	Ar << CartridgeID;
	
	return true;
}
