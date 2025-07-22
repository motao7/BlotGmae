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
	FGameplayEffectContext::NetSerialize(Ar, Map, bOutSuccess);

	Ar<<CartridgeID;
	
	if (Ar.IsLoading())
	{
		for (auto Hit:HitResults)
		{
			if (!Hit.IsValid())
			{
				Hit = TSharedPtr<FHitResult>(new FHitResult());
			}
			Hit->NetSerialize(Ar, Map, bOutSuccess);
		}
	}
	return true;
}
