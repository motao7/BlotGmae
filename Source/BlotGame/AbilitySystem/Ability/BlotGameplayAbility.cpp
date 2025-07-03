#include "BlotGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "Character/BlotCharacter.h"

ABlotCharacter* UBlotGameplayAbility::GetBlotCharacter() const
{
	return (CurrentActorInfo?Cast<ABlotCharacter>(CurrentActorInfo->AvatarActor.Get()):nullptr);
}

