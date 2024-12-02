// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "ModularPlayerState.h"
#include "TeamGenericTeamAgentInterface.h"
#include "BlotPlayerState.generated.h"

class UExperienceDefination;
class UExperiencePawnData;
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

	/** Bind Function OnExperienceLoaded */
	virtual void PostInitializeComponents() override;
	
	void SetPawnData(const UExperiencePawnData* PawnData){ExperiencePawnData=PawnData;}
	const UExperiencePawnData* GetPawnData(){return ExperiencePawnData;}

	//~IGenericTeamAgentInterface Start
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual FOnTeamChangedDelegateSignature& GetTeamChangedDelegateChecked() override;
	//~IGenericTeamAgentInterface Ebd

private:
	UFUNCTION()
	void OnRep_TeamId(FGenericTeamId OldMyTeamId);
	
	UPROPERTY(ReplicatedUsing=OnRep_TeamId)
	FGenericTeamId MyTeamId;

	UPROPERTY()
	FOnTeamChangedDelegateSignature OnTeamChangedPlayerStateDelegate; 
	
private:
	UPROPERTY(Replicated)
	TObjectPtr<const UExperiencePawnData> ExperiencePawnData;

	void OnExperienceLoaded(const UExperienceDefination* ExperienceDefination);
	
};
