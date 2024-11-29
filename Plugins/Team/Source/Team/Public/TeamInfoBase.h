// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "TeamInfoBase.generated.h"

class UTeamDisplayAsset;
/**
 * 
 */
UCLASS()
class TEAM_API ATeamInfoBase : public AInfo
{
	GENERATED_BODY()
	
public:
	explicit ATeamInfoBase(const FObjectInitializer& ObjectInitializer);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	uint8 GetTeamId() const {return TeamId;}
	void SetTeamId(const uint8 NewTeamId);
	void SetDisplayAsset(UTeamDisplayAsset* NewDisplayAsset);
	UTeamDisplayAsset* GetDisplayAsset(){return DisplayAsset;}
	
private:
	/** 中间函数用于调用Subsystem中的RegisterTeamInfo */
	void RegisterToTeamSubsystem();
	
	UPROPERTY(ReplicatedUsing=OnRep_TeamId)
	uint8 TeamId;
	UFUNCTION()
	void OnRep_TeamId();
	
	UPROPERTY(ReplicatedUsing=OnRep_DisplayAsset)
	TObjectPtr<UTeamDisplayAsset> DisplayAsset;
	UFUNCTION()
	void OnRep_DisplayAsset();
};
