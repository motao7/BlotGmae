// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/BlotAnimInstance.h"

#include "AbilitySystemGlobals.h"
#include "BlotLogChannels.h"
#include "Character/BlotCharacter.h"
#include "Character/BlotCharacterMovementComponent.h"


void UBlotAnimInstance::InitializeWithAbilitySystem(UAbilitySystemComponent* ASC)
{
	check(ASC);
	GameplayTagPropertyMap.Initialize(this, ASC);
}

void UBlotAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// 防止在编辑器动画预览中崩溃
	if (!GetWorld() || (GetWorld()->WorldType != EWorldType::Game && GetWorld()->WorldType != EWorldType::PIE))
	{
		return;
	}
	
	AActor* OwningActor = GetOwningActor();
	if (!OwningActor)
	{
		UE_LOG(LogBlotAnim, Warning, TEXT("GetOwningActor returned nullptr."));
		return;
	}

	UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor);
	if (!ASC)
	{
		return;
	}

	InitializeWithAbilitySystem(ASC);
}

void UBlotAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	const ABlotCharacter* Character = Cast<ABlotCharacter>(GetOwningActor());
	if (!Character)
	{
		return;
	}

	//Only evalueation when in air
	if (GetOwningActor()->GetVelocity().Z!=0)
	{
		UBlotCharacterMovementComponent* CharMoveComp = CastChecked<UBlotCharacterMovementComponent>(Character->GetCharacterMovement());
		const FBlotCharacterGroundInfo& GroundInfo = CharMoveComp->GetGroundInfo();
 		GroundDistance = GroundInfo.GroundDistance;
	}
}
