#pragma once
#include "BlotGameplayAbility.h"
#include "BlotGameplayAbility_HeroJump.generated.h"

UCLASS(Abstract)
class UBlotGameplayAbility_HeroJump:public UBlotGameplayAbility
{
	GENERATED_BODY()
public:
	UBlotGameplayAbility_HeroJump(const FObjectInitializer& ObjectInitializer);
	virtual bool CanActivateAbility(FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;

	UFUNCTION(BlueprintCallable)
	void CharacterJumpStart();
	UFUNCTION(BlueprintCallable)
	void CharacterJumpStop();
};
