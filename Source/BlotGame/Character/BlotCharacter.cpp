// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BlotCharacter.h"

#include "BlotAbilitySystemComponent.h"
#include "BlotCharacterMovementComponent.h"
#include "BlotHealthComponent.h"
#include "BlotPawnExtensionComponent.h"
#include "CommonCameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/BlotPlayerController.h"
#include "Player/BlotPlayerState.h"

static FName NAME_BlotCharacterCollisionProfile_Capsule(TEXT("BlotPawnCapsule"));
static FName NAME_BlotCharacterCollisionProfile_Mesh(TEXT("BlotPawnMesh"));

ABlotCharacter::ABlotCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UBlotCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Character不执行tick事件(网络开销，运算开销的问题)
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->InitCapsuleSize(40.0f, 90.0f);
	CapsuleComp->SetCollisionProfileName(NAME_BlotCharacterCollisionProfile_Capsule);

	USkeletalMeshComponent* MeshComp = GetMesh();
	check(MeshComp);
	MeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));  // Rotate mesh to be X forward since it is exported as Y forward.
	MeshComp->SetCollisionProfileName(NAME_BlotCharacterCollisionProfile_Mesh);
	
	PawnExtensionComponent=CreateDefaultSubobject<UBlotPawnExtensionComponent>(TEXT("PawnExtensionComponent"));
	PawnExtensionComponent->OnAbilitySystemInitialized_RegisterAndCall(FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &ThisClass::OnAbilitySystemInitialized));
	PawnExtensionComponent->SetIsReplicated(true);
	
	CommonCameraComponent=CreateDefaultSubobject<UCommonCameraComponent>(TEXT("CommonCameraComponent"));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	HealthComponent = CreateDefaultSubobject<UBlotHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->SetIsReplicated(true);
	
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
	//ECastCheckedType::NullAllowed,if GetController()==nullptr not invoke assert，only class diffenet invoke
	return CastChecked<ABlotPlayerController>(GetController(),ECastCheckedType::NullAllowed);
}

ABlotPlayerState* ABlotCharacter::GetBlotPlayerState() const
{
	return CastChecked<ABlotPlayerState>(GetPlayerState(),ECastCheckedType::NullAllowed);
}

UAbilitySystemComponent* ABlotCharacter::GetAbilitySystemComponent() const
{
	if (ABlotPlayerState* PS=GetBlotPlayerState())
	{
		return PS->GetAbilitySystemComponent();
	}
	return nullptr;
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

void ABlotCharacter::LinkDefaultAnimLayer()
{
	GetMesh()->LinkAnimClassLayers(DefaultAnimInstance);
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

void ABlotCharacter::OnAbilitySystemInitialized()
{
	UBlotAbilitySystemComponent* BlotASC = Cast<UBlotAbilitySystemComponent>(GetAbilitySystemComponent());
	check(BlotASC);

	HealthComponent->InitializeWithAbilitySystem(BlotASC);
}
