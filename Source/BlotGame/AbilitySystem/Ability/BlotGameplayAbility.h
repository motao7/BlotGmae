#pragma once
#include "ExperienceGameplayAbility.h"
#include "Abilities/GameplayAbility.h"
#include "Character/BlotParryComponent.h"
#include "BlotGameplayAbility.generated.h"

class ABlotPlayerController;
class UBlotAbilitySystemComponent;
class UBlotHeroComponent;
class UBlotAbilityCost;
class ABlotCharacter;

UCLASS(Abstract)
class UBlotGameplayAbility:public UExperienceGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Blot|Ability")
	ABlotCharacter* GetBlotCharacterFromActorInfo() const;
	
	UFUNCTION(BlueprintCallable, Category = "Blot|Ability")
	UBlotAbilitySystemComponent* GetBlotAbilitySystemComponentFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Blot|Ability")
	ABlotPlayerController* GetBlotPlayerControllerFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Blot|Ability")
	AController* GetControllerFromActorInfo() const;
	
	UFUNCTION(BlueprintCallable, Category = "Blot|Ability")
	UBlotHeroComponent* GetHeroComponentFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Blot|Ability")
	UBlotParryComponent* GetParryComponentFromActorInfo() const;

	
protected:
	virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
	
	// Additional costs that must be paid to activate this ability
	UPROPERTY(EditDefaultsOnly, Instanced, Category = Costs)
	TArray<TObjectPtr<UBlotAbilityCost>> AdditionalCosts;

private:
	friend class UBlotAbilitySystemComponent;
};
