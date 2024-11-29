// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "ModularPlayerState.h"
#include "TeamGenericTeamAgentInterface.h"
#include "BlotPlayerState.generated.h"

class UExperiencePawnData;
class UPawnData;
/**
 * 
 */
UCLASS()
class BLOTGAME_API ABlotPlayerState : public AModularPlayerState,public FGenericTeamId,public ITeamGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	ABlotPlayerState(const FObjectInitializer& ObjectInitialize);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	//~Helper Function
	//~Helper Function End

	////~~Team Start
public:
	//~IGenericTeamAgentInterface Start
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual FOnTeamChangedDelegateSignature& GetTeamChangedDelegateChecked() override;
	//~IGenericTeamAgentInterface Ebd
protected:
	UFUNCTION()
	void OnRep_TeamId(FGenericTeamId OldMyTeamId);
	
	UPROPERTY(ReplicatedUsing=OnRep_TeamId)
	FGenericTeamId MyTeamId;

	UPROPERTY()
	FOnTeamChangedDelegateSignature OnTeamChangedPlayerStateDelegate; 
	////~~Team End
protected:
};
