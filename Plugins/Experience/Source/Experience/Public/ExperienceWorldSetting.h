// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "ExperienceWorldSetting.generated.h"

class UExperienceDefinition;
/**
 *		持有每一个Level对应的Expeirnece
 */
UCLASS()
class EXPERIENCE_API AExperienceWorldSetting : public AWorldSettings
{
	GENERATED_BODY()

public:
	AExperienceWorldSetting(const FObjectInitializer& ObjectInitializer);
	
	TSoftClassPtr<UExperienceDefinition>& GetDefaultExperience(){return DefaultExperience;}
	
protected:
	UPROPERTY(EditAnywhere,Category="Experience")
	TSoftClassPtr<UExperienceDefinition> DefaultExperience;
};
