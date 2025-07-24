// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonPlayerController.h"
#include "ModularPlayerController.h"
#include "BlotPlayerController.generated.h"

class ABlotCharacter;
class ABlotWorldCollectable;
/**
 * 
 */
UCLASS()
class BLOTGAME_API ABlotPlayerController : public ACommonPlayerController
{
	GENERATED_BODY()

public:
	ABlotPlayerController(const FObjectInitializer& ObjectInitializer);

	ABlotCharacter* GetBlotCharacter() const;
	
	//~ PlayerController 
	virtual void BeginPlay() override;
	virtual void AddCheats(bool bForce) override;
	virtual void PostProcessInput(float DeltaTime, bool bGamePaused) override;
	//~ PlayerController End

protected:
	void TraceForCollectable();

	//~ PlayerController
	FTimerHandle HighlightTraceTimerHandle;

	UPROPERTY()
	ABlotWorldCollectable* HighlightedTarget = nullptr;
	
};
