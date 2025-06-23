// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GenericTeamAgentInterface.h"
#include "ModularPlayerState.h"
#include "TeamGenericTeamAgentInterface.h"
#include "BlotPlayerState.generated.h"

class UBlotCombatAttributeSet;
class UBlotAbilitySystemComponent;
class UExperienceDefination;
class UExperiencePawnData;

/**
 * 
 */
UCLASS()
class BLOTGAME_API ABlotPlayerState : public AModularPlayerState,public FGenericTeamId,public ITeamGenericTeamAgentInterface,public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ABlotPlayerState(const FObjectInitializer& ObjectInitializeR);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Bind Function OnExperienceLoaded */
	virtual void PostInitializeComponents() override;
	
	void SetPawnData(const UExperiencePawnData* PawnData); 
	const UExperiencePawnData* GetPawnData(){return ExperiencePawnData;}

	UFUNCTION(BlueprintCallable)
	UBlotAbilitySystemComponent* GetBlotAbilitySystemComponent();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	//~IGenericTeamAgentInterface Start
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual FOnTeamChangedDelegateSignature& GetTeamChangedDelegateChecked() override;
	//~IGenericTeamAgentInterface Ebd

private:
	UFUNCTION()
	void OnRep_TeamId(FGenericTeamId OldMyTeamId);
	
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_TeamId)
	FGenericTeamId MyTeamId;

	UPROPERTY()
	FOnTeamChangedDelegateSignature OnTeamChangedPlayerStateDelegate; 
	
	UPROPERTY(VisibleAnywhere,Replicated)
	TObjectPtr<const UExperiencePawnData> ExperiencePawnData;

	void OnExperienceLoaded(const UExperienceDefination* ExperienceDefination);

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBlotAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBlotCombatAttributeSet> CombatAttributeSet;
};
