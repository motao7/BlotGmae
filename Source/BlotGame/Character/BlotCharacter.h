// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlotPawnExtensionComponent.h"
#include "ModularCharacter.h"
#include "BlotCharacter.generated.h"

class UCommonCameraComponent;
class ABlotPlayerController;
class ABlotPlayerState;
class UBlotPawnExtensionComponent;
/**
 * 
 */
UCLASS()
class BLOTGAME_API ABlotCharacter : public AModularCharacter
{
	GENERATED_BODY()

public:
	ABlotCharacter(const FObjectInitializer& ObjectInitializer);

	ABlotPlayerController* GetBlotPlayerController() const;
	ABlotPlayerState* GetBlotPlayerState() const;

	//PawnExtensionComponent updates the initialization chain when these following function called.
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	virtual void OnRep_Controller() override;
	virtual void OnRep_PlayerState() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void ToggleCrouch();
	
protected:
	//~ Pawn
	/** 用于在设置完PlayerState后ObserTeamColor异步节点对象聆听新的PlayerState中TeamId的改变 */
	virtual void OnPlayerStateChanged(APlayerState* NewPlayerState, APlayerState* OldPlayerState) override;
	//~ Pawn End

	UFUNCTION(BlueprintImplementableEvent,Category="Team|AsyncAction")
	void ListenForTeamChange();
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lyra|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBlotPawnExtensionComponent> PawnExtensionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lyra|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCommonCameraComponent> CommonCameraComponent;
};

