// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BlotCharacter.h"

#include "BlotPawnExtensionComponent.h"
#include "CommonCameraComponent.h"
#include "Player/BlotPlayerController.h"
#include "Player/BlotPlayerState.h"


ABlotCharacter::ABlotCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	// Character不执行tick事件(网络开销，运算开销的问题)
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	PawnExtensionComponent=CreateDefaultSubobject<UBlotPawnExtensionComponent>(TEXT("PawnExtensionComponent"));
	CommonCameraComponent=CreateDefaultSubobject<UCommonCameraComponent>(TEXT("CommonCameraComponent"));
}

ABlotPlayerController* ABlotCharacter::GetBlotPlayerController() const
{
	return CastChecked<ABlotPlayerController>(GetController());
}

ABlotPlayerState* ABlotCharacter::GetBlotPlayerState() const
{
	return CastChecked<ABlotPlayerState>(GetPlayerState());
}

void ABlotCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	PawnExtensionComponent->HandleOnControllerChanged();
}

void ABlotCharacter::UnPossessed()
{
	Super::UnPossessed();

	PawnExtensionComponent->HandleOnControllerChanged();
}

void ABlotCharacter::OnRep_Controller()
{
	Super::OnRep_Controller();

	PawnExtensionComponent->HandleOnControllerChanged();
}

void ABlotCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	PawnExtensionComponent->HandleOnPlayerStateReplicated();
}

void ABlotCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PawnExtensionComponent->HandleOnSetupPlayerInputComponent();
}

void ABlotCharacter::OnPlayerStateChanged(APlayerState* NewPlayerState, APlayerState* OldPlayerState)
{
	Super::OnPlayerStateChanged(NewPlayerState, OldPlayerState);

	ListenForTeamChange();
}
