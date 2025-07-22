// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/BlotGameplayAbility_SlientWalk.h"

#include "AbilitySystemComponent.h"
#include "Character/BlotCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


bool UBlotGameplayAbility_SlientWalk::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	// 例如：判断是否是玩家决定死亡
	ABlotCharacter* Character = Cast<ABlotCharacter>(GetBlotCharacterFromActorInfo());
	if (!Character || Character->IsPendingKillPending())
	{
		return false;
	}

	// 示例：检查是否已经处于静步状态（避免重复开启）
	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	if (ASC && ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.SilentWalking")))
	{
		return false;
	}

	// 示例：不能在空中使用
	if (Character->GetCharacterMovement()->IsFalling())
	{
		return false;
	}

	return true;
}
