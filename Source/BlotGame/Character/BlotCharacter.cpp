// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BlotCharacter.h"

#include "BlotCharacterMovementComponent.h"
#include "BlotPawnExtensionComponent.h"
#include "CommonCameraComponent.h"
#include "Player/BlotPlayerController.h"
#include "Player/BlotPlayerState.h"


ABlotCharacter::ABlotCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UBlotCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Character不执行tick事件(网络开销，运算开销的问题)
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	PawnExtensionComponent=CreateDefaultSubobject<UBlotPawnExtensionComponent>(TEXT("PawnExtensionComponent"));
	CommonCameraComponent=CreateDefaultSubobject<UCommonCameraComponent>(TEXT("CommonCameraComponent"));
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	UBlotCharacterMovementComponent* MoveComp = CastChecked<UBlotCharacterMovementComponent>(GetCharacterMovement());
	MoveComp->GravityScale = 1.0f;
	MoveComp->MaxAcceleration = 2400.0f;
	MoveComp->BrakingFrictionFactor = 1.0f;
	MoveComp->BrakingFriction = 6.0f;
	MoveComp->GroundFriction = 8.0f;
	MoveComp->BrakingDecelerationWalking = 1400.0f;
	MoveComp->bUseControllerDesiredRotation = false;
	MoveComp->bOrientRotationToMovement = false;
	MoveComp->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	MoveComp->bAllowPhysicsRotationDuringAnimRootMotion = false;
	MoveComp->GetNavAgentPropertiesRef().bCanCrouch = true;
	MoveComp->bCanWalkOffLedgesWhenCrouching = true;
	MoveComp->SetCrouchedHalfHeight(65.0f);

	BaseEyeHeight = 80.0f;
	CrouchedEyeHeight = 50.0f;
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

	// ListenForTeamChange();
}

void ABlotCharacter::ToggleCrouch()
{
	const UBlotCharacterMovementComponent* MoveComp = CastChecked<UBlotCharacterMovementComponent>(GetCharacterMovement());

	if (bIsCrouched || MoveComp->bWantsToCrouch)
	{
		UnCrouch();
	}
	else if (MoveComp->IsMovingOnGround())
	{
		Crouch();
	}
}
