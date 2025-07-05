// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BlotGameplayEffectContext.h"


FBlotGameplayEffectContext* FBlotGameplayEffectContext::ExtractEffectContext(struct FGameplayEffectContextHandle Handle)
{
	FGameplayEffectContext* BaseEffectContext = Handle.Get();
	if ((BaseEffectContext != nullptr) && BaseEffectContext->GetScriptStruct()->IsChildOf(FBlotGameplayEffectContext::StaticStruct()))
	{
		return (FBlotGameplayEffectContext*)BaseEffectContext;
	}

	return nullptr;
}

bool FBlotGameplayEffectContext::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	return FGameplayEffectContext::NetSerialize(Ar, Map, bOutSuccess);
}
