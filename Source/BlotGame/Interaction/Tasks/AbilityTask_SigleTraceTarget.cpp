// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/Tasks/AbilityTask_SigleTraceTarget.h"

#include "AbilitySystemComponent.h"
#include "Ability/BlotGameplayAbility.h"
#include "Character/BlotCharacter.h"
#include "Physics/BlotCollisionChannel.h"
#include "Player/BlotPlayerController.h"

UAbilityTask_SigleTraceTarget* UAbilityTask_SigleTraceTarget::SigleTraceTarget(UGameplayAbility* OwningAbility, float InScanRate, float InTraceDistance)
{
	UAbilityTask_SigleTraceTarget* MyObj = NewAbilityTask<UAbilityTask_SigleTraceTarget>(OwningAbility);
	MyObj->ScanRate=InScanRate;
	MyObj->TraceDistance=InTraceDistance;
	return MyObj;
}

void UAbilityTask_SigleTraceTarget::Activate()
{
	Super::Activate();

	if (UAbilitySystemComponent* AbilitySystem = Ability->GetAbilitySystemComponentFromActorInfo())
	{
		if (APlayerController* PC=Ability->GetCurrentActorInfo()->PlayerController.Get())
		{
			PC->GetWorldTimerManager().SetTimer(
						QueryTimerHandle,
						this,
						&ThisClass::TraceForInteract,
						0.1f,
						true);
		}
	}
}

void UAbilityTask_SigleTraceTarget::TraceForInteract()
{
	if (UBlotGameplayAbility* BlotAbility=Cast<UBlotGameplayAbility>(Ability))
	{
		if (ABlotPlayerController* PC=BlotAbility->GetBlotPlayerControllerFromActorInfo())
		{
			FRotator ViewRot;
			FVector ViewLoc;
			PC->GetPlayerViewPoint(ViewLoc, ViewRot);
			if (ABlotCharacter* BlotCharacter=BlotAbility->GetBlotCharacterFromActorInfo())
			{
				const FVector Start = ViewLoc;
				const FVector End = Start + ViewRot.Vector() * TraceDistance;

				FHitResult Hit;
				FCollisionQueryParams Params;

				GetWorld()->LineTraceSingleByChannel(Hit, Start, End, Blot_TraceChannel_Interaction, Params);

				AActor* HitActor = Hit.GetActor();
		
				if (HitActor != CurrentTarget)
				{
					HitTargetChanged.Broadcast(HitActor, CurrentTarget);
					CurrentTarget = HitActor;
				}
			}
		}
	}
}
