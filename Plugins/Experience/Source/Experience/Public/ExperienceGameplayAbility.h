#pragma once
#include "Abilities/GameplayAbility.h"
#include "ExperienceGameplayAbility.generated.h"

/**
 * EAbilityActivationPolicy
 *
 *	Defines how an ability is meant to activate.
 */
UENUM(BlueprintType)
enum class EExperienceAbilityActivationPolicy : uint8
{
	// Try to activate the ability when the input is triggered.
	OnInputTriggered,

	// Continually try to activate the ability while the input is active.
	WhileInputActive,

	// Try to activate the ability when an avatar is assigned.
	OnSpawn
};

/**
 *		Contain ActivationPolicy and as memeber of PawnData
 */
UCLASS(Abstract, HideCategories = Input, Meta = (ShortTooltip = "The base gameplay ability class used by this project."))
class EXPERIENCE_API UExperienceGameplayAbility: public UGameplayAbility
{
	GENERATED_BODY()
public:
	EExperienceAbilityActivationPolicy GetActivationPolicy() const { return ActivationPolicy; }

protected:
	// Defines how this ability is meant to activate.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|Ability Activation")
	EExperienceAbilityActivationPolicy ActivationPolicy;

};
