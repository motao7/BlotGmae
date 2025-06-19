#include "BlotGameplayAbility_HeroJump.h"

#include "Character/BlotCharacter.h"

UBlotGameplayAbility_HeroJump::UBlotGameplayAbility_HeroJump(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

bool UBlotGameplayAbility_HeroJump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!ActorInfo || !ActorInfo->AvatarActor.IsValid())
	{
		return false;
	}

	const ABlotCharacter* BlotCharacter = GetBlotCharacter();
	if (!BlotCharacter || !BlotCharacter->CanJump())
	{
		return false;
	}

	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	return true;
}

void UBlotGameplayAbility_HeroJump::CharacterJumpStart()
{
	if (ABlotCharacter* LyraCharacter = GetBlotCharacter())
	{
		if (LyraCharacter->IsLocallyControlled() && !LyraCharacter->bPressedJump)
		{
			LyraCharacter->UnCrouch();
			LyraCharacter->Jump();
		}
	}
}

void UBlotGameplayAbility_HeroJump::CharacterJumpStop()
{
	if (ABlotCharacter* LyraCharacter = GetBlotCharacter())
	{
		if (LyraCharacter->IsLocallyControlled() && LyraCharacter->bPressedJump)
		{
			LyraCharacter->StopJumping();
		}
	}
}