// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BlotAbilitySystemGlobals.h"

#include "BlotGameplayEffectContext.h"


FGameplayEffectContext* UBlotAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FBlotGameplayEffectContext();
}
