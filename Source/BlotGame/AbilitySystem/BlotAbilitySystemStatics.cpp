// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BlotAbilitySystemStatics.h"

#include "BlotGameplayEffectContext.h"

TArray<FHitResult> UBlotAbilitySystemStatics::EffectContextGetHitResults(FGameplayEffectContextHandle EffectContext)
{
	TArray<FHitResult> OutHits;

	const FBlotGameplayEffectContext* TypedContext = FBlotGameplayEffectContext::ExtractEffectContext(EffectContext);
	if (TypedContext)
	{
		for (auto Hit:TypedContext->GetHitResults())
		{
			OutHits.Add(*Hit.Get());
		}
	}

	return OutHits;
}
