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
	UFUNCTION(BlueprintCallable)
	ABlotCharacter* GetBlotCharacter() const;
};
