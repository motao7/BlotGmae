// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "TeamCheatExtension.generated.h"

/**
 * 
 */
UCLASS()
class TEAM_API UTeamCheatExtension : public UCheatManagerExtension
{
	GENERATED_BODY()

public:

	UFUNCTION(Exec,BlueprintAuthorityOnly)
	void SetTeam(uint8 TeamId) const;
};
