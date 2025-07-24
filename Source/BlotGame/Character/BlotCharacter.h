// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "BlotPawnExtensionComponent.h"
#include "ModularCharacter.h"
#include "BlotCharacter.generated.h"

class UBlotHealthComponent;
class UCommonCameraComponent;
class ABlotPlayerController;
class ABlotPlayerState;
class UBlotPawnExtensionComponent;
/**
 * 
 */
UCLASS(Config=Game)
class BLOTGAME_API ABlotCharacter : public AModularCharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABlotCharacter(const FObjectInitializer& ObjectInitializer);

	ABlotPlayerController* GetBlotPlayerController() const;
	ABlotPlayerState* GetBlotPlayerState() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void ToggleCrouch();
	
protected:
	virtual void OnAbilitySystemInitialized();
	
	//~ Pawn
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	virtual void OnRep_Controller() override;
	virtual void OnRep_PlayerState() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	/** 用于在设置完PlayerState后ObserTeamColor异步节点对象聆听新的PlayerState中TeamId的改变 */
	virtual void OnPlayerStateChanged(APlayerState* NewPlayerState, APlayerState* OldPlayerState) override;
	//~ Pawn End

	UFUNCTION(BlueprintImplementableEvent,Category="Team|AsyncAction")
	void ListenForTeamChange();

	UFUNCTION(BlueprintCallable,Category="Blot|Character")
	void LinkDefaultAnimLayer();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blot|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBlotPawnExtensionComponent> PawnExtensionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blot|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCommonCameraComponent> CommonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blot|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBlotHealthComponent> HealthComponent;
	
	UPROPERTY(BlueprintReadOnly,Category= "Blot|Character",Config, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UAnimInstance> DefaultAnimInstance;

};

