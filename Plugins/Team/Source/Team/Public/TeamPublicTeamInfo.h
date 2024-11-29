// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TeamInfoBase.h"
#include "TeamPublicTeamInfo.generated.h"

class UTeamDisplayAsset;
/**
 * 
 */
UCLASS()
class TEAM_API ATeamPublicTeamInfo : public ATeamInfoBase
{
	GENERATED_BODY()

private:
	/** 展示给所有玩家看的DisplayAsset */
	TObjectPtr<UTeamDisplayAsset> PublicDisplayAsset;
};
