#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ExperienceAbilitySet.generated.h"

class UAttributeSet;
struct FActiveGameplayEffectHandle;
struct FGameplayAbilitySpecHandle;
class UAbilitySystemComponent;
class UExperienceGameplayAbility;

USTRUCT(BlueprintType)
struct FExperienceAbilitySet_GameplayAbility
{
	GENERATED_BODY()

public:
	// Gameplay ability to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UExperienceGameplayAbility> Ability = nullptr;

	// Level of ability to grant.
	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;

	// Tag used to process input for the ability.
	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

/**
 * FLyraAbilitySet_GrantedHandles
 *
 *	Data used to store handles to what has been granted by the ability set.
 */
USTRUCT(BlueprintType)
struct EXPERIENCE_API FExperienceAbilitySet_GrantedHandles
{
	GENERATED_BODY()

public:
	void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);
	void AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle);
	void AddAttributeSet(UAttributeSet* Set);

	void TakeFromAbilitySystem(UAbilitySystemComponent* ASC);

protected:

	// Handles to the granted abilities.
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	// Handles to the granted gameplay effects.
	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;

	// Pointers to the granted attribute sets
	UPROPERTY()
	TArray<TObjectPtr<UAttributeSet>> GrantedAttributeSets;
};


UCLASS(BlueprintType, Const)
class EXPERIENCE_API UExperienceAbilitySet: public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	void GiveToAbilitySystem(UAbilitySystemComponent* ASC, FExperienceAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject) const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta=(TitleProperty=Ability))
	TArray<FExperienceAbilitySet_GameplayAbility> GrantedGameplayAbilities;
	
};
