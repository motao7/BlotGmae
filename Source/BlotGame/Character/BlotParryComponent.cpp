// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BlotParryComponent.h"

#include "AbilitySystemComponent.h"
#include "BlotCharacter.h"
#include "GameplayTagContainer.h"
#include "Ability/BlotGameplayAbility.h"


void UBlotParryComponent::OpenParryWindow(AActor* HitActor)
{
	//提供Duration，在Duration结束了调用CloseWindow
	//增加GE，并保存看是否触发SuccessParry，有则不执行GE，无则执行GE
	if (ABlotCharacter* Character= Cast<ABlotCharacter>(GetOwner()))
	{
		if (Character->GetLocalRole()==ROLE_Authority)
		{
			if (UAbilitySystemComponent* ASC=Character->GetAbilitySystemComponent())
			{
				if (UBlotGameplayAbility* AbilityCDO = ParryAbilitySet.Ability->GetDefaultObject<UBlotGameplayAbility>())
				{
					FGameplayAbilitySpec AbilitySpec(AbilityCDO, 1);
					AbilitySpec.Level=ParryAbilitySet.AbilityLevel;
					AbilitySpec.DynamicAbilityTags.AddTag(ParryAbilitySet.InputTag);
					CurrentParryAbilitySpec = ASC->GiveAbility(AbilitySpec);

					bSuccessParry=false;
					HitActors.AddUnique(HitActor);
				}
			}
		}
	}
}

void UBlotParryComponent::CloseParryWindow()
{
	if (ABlotCharacter* Character= Cast<ABlotCharacter>(GetOwner()))
	{
		if (Character->GetLocalRole()==ROLE_Authority)
		{
			if (UAbilitySystemComponent* ASC=Character->GetAbilitySystemComponent())
			{
				if (CurrentParryAbilitySpec.IsValid())
				{
					ASC->ClearAbility(CurrentParryAbilitySpec);
					if (!bSuccessParry)
					{
						OnActiveParryDelegate.Broadcast(false);
					}
				}
			}
		}
	}

	CurrentParryAbilitySpec=FGameplayAbilitySpecHandle();
}

void UBlotParryComponent::OnActiveParr(bool SuccessParry)
{
	bSuccessParry=SuccessParry;
	OnActiveParryDelegate.Broadcast(SuccessParry);
}
