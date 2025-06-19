#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ExperienceAbilitySet.generated.h"

class UAbilitySystemComponent;
class UExperienceGameplayAbility;

USTRUCT(BlueprintType)
struct FLyraAbilitySet_GameplayAbility
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

UCLASS(BlueprintType, Const)
class EXPERIENCE_API UExperienceAbilitySet: public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	void GiveToAbilitySystem(UAbilitySystemComponent* ASC, UObject* SourceObject) const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta=(TitleProperty=Ability))
	TArray<FLyraAbilitySet_GameplayAbility> GrantedGameplayAbilities;
	
};
