#pragma once
#include "ExperienceGameplayAbility.h"
#include "Abilities/GameplayAbility.h"
#include "BlotGameplayAbility.generated.h"

class UBlotAbilityCost;
class ABlotCharacter;

UCLASS(Abstract)
class UBlotGameplayAbility:public UExperienceGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	ABlotCharacter* GetBlotCharacter() const;

protected:
	virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
	
	// Additional costs that must be paid to activate this ability
	UPROPERTY(EditDefaultsOnly, Instanced, Category = Costs)
	TArray<TObjectPtr<UBlotAbilityCost>> AdditionalCosts;

};
