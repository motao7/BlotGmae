// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CommonGameUIManagerSubsystem.generated.h"

class UCommonLocalPlayer;
class UCommonGameUIPolicy;
/**
 *		Maintain UIPolicy and provide function to switch UIPolicy
 */
UCLASS(config = Game)
class COMMONGAME_API UCommonGameUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void NotifyPlayerAdded(UCommonLocalPlayer* LocalPlayer);
	void SwitchToPolicy(UCommonGameUIPolicy* InPolicy);

	UCommonGameUIPolicy* GetCurrentUIPolicy() { return CurrentPolicy; }

private:
	UPROPERTY(Transient)
	TObjectPtr<UCommonGameUIPolicy> CurrentPolicy = nullptr;

	UPROPERTY(Config, EditAnywhere)
	TSoftClassPtr<UCommonGameUIPolicy> DefaultUIPolicyClass;
	
};
