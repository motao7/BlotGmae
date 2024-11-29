// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularCharacter.h"
#include "BlotCharacter.generated.h"

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
};
