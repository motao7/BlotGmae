#pragma once
#include "ExperienceGameplayAbility.h"
#include "Abilities/GameplayAbility.h"
#include "BlotGameplayAbility.generated.h"

class ABlotCharacter;

UCLASS(Abstract)
class UBlotGameplayAbility:public UExperienceGameplayAbility
{
	GENERATED_BODY()
public:
	/**Helper function to get information from ActorInfo */
	ABlotCharacter* GetBlotCharacter() const;

	/**Check ASC and ActorInfo*/
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
};
