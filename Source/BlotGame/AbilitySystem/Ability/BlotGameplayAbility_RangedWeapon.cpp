// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/BlotGameplayAbility_RangedWeapon.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "BlotGameplayAbilityTargetData_SingleTargetHit.h"
#include "BlotLogChannels.h"
#include "Physics/BlotCollisionChannel.h"
#include "Weapon/CommonRangedWeaponInstance.h"
#include "Weapon/CommonWeaponStateComponent.h"

namespace BlotConsoleVariables
{
	static float DrawBulletTracesDuration = 0.f;
	static FAutoConsoleVariableRef CVarDrawBulletTraceDuraton(
		TEXT("Blot.Weapon.DrawBulletTraceDuration"),
		DrawBulletTracesDuration,
		TEXT("Should we do debug drawing for bullet traces (if above zero, sets how long (in seconds))"),
		ECVF_Default);

	static float DrawBulletHitDuration = 1.f;
	static FAutoConsoleVariableRef CVarDrawBulletHits(
		TEXT("Blot.Weapon.DrawBulletHitDuration"),
		DrawBulletHitDuration,
		TEXT("Should we do debug drawing for bullet impacts (if above zero, sets how long (in seconds))"),
		ECVF_Default);

	static float DrawBulletHitRadius = 3.0f;
	static FAutoConsoleVariableRef CVarDrawBulletHitRadius(
		TEXT("Blot.Weapon.DrawBulletHitRadius"),
		DrawBulletHitRadius,
		TEXT("When bullet hit debug drawing is enabled (see DrawBulletHitDuration), how big should the hit radius be? (in uu)"),
		ECVF_Default);
}

void UBlotGameplayAbility_RangedWeapon::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	// Bind target data callback
	UAbilitySystemComponent* MyAbilityComponent = CurrentActorInfo->AbilitySystemComponent.Get();
	check(MyAbilityComponent);

	OnTargetDataReadyCallbackDelegateHandle = MyAbilityComponent->AbilityTargetDataSetDelegate(CurrentSpecHandle, CurrentActivationInfo.GetActivationPredictionKey()).AddUObject(this, &ThisClass::OnTargetDataReadyCallback);
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UBlotGameplayAbility_RangedWeapon::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (IsEndAbilityValid(Handle, ActorInfo))
	{
		if (ScopeLockCount > 0)
		{
			WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &ThisClass::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
			return;
		}

		UAbilitySystemComponent* MyAbilityComponent = CurrentActorInfo->AbilitySystemComponent.Get();
		check(MyAbilityComponent);

		// When ability ends, consume target data and remove delegate
		MyAbilityComponent->AbilityTargetDataSetDelegate(CurrentSpecHandle, CurrentActivationInfo.GetActivationPredictionKey()).Remove(OnTargetDataReadyCallbackDelegateHandle);
		MyAbilityComponent->ConsumeClientReplicatedTargetData(CurrentSpecHandle, CurrentActivationInfo.GetActivationPredictionKey());

		Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	}
}

UCommonRangedWeaponInstance* UBlotGameplayAbility_RangedWeapon::GetWeaponInstance() const
{
	return Cast<UCommonRangedWeaponInstance>(GetAssociatedEquipment());
}

void UBlotGameplayAbility_RangedWeapon::StartRangedWeaponTargeting()
{
	check(CurrentActorInfo);

	AActor* AvatarActor = CurrentActorInfo->AvatarActor.Get();
	check(AvatarActor);

	UAbilitySystemComponent* MyAbilityComponent = CurrentActorInfo->AbilitySystemComponent.Get();
	check(MyAbilityComponent);

	FScopedPredictionWindow ScopedPrediction(MyAbilityComponent, CurrentActivationInfo.GetActivationPredictionKey());

	TArray<FHitResult> FoundHits;
	PerformLocalTargeting(/*out*/ FoundHits);
	// Fill out the target data from the hit results
	
	FGameplayAbilityTargetDataHandle TargetData;
	TargetData.UniqueId = 0;
	
	if (AController* Controller = GetControllerFromActorInfo())
	{
		UCommonWeaponStateComponent* WeaponStateComponent = Controller->FindComponentByClass<UCommonWeaponStateComponent>();
		if (FoundHits.Num() > 0)
		{
			const int32 CartridgeID = FMath::Rand();

			for (const FHitResult& FoundHit : FoundHits)
			{
				FBlotGameplayAbilityTargetData_SingleTargetHit* NewTargetData = new FBlotGameplayAbilityTargetData_SingleTargetHit();
				NewTargetData->HitResult = FoundHit;
				NewTargetData->CartridgeID = CartridgeID;
		
				TargetData.Add(NewTargetData);
			}

			// Send hit marker information if hit somepawn
			if (WeaponStateComponent != nullptr&&FindFirstPawnHitResult(FoundHits)!=INDEX_NONE)
			{
				WeaponStateComponent->AddLastWeaponDamageScreenLocations(FoundHits);
				WeaponStateComponent->UpdateDamageInstigatedTime();
			}
		}
	}
	
	// Process the target data immediately
	OnTargetDataReadyCallback(TargetData, FGameplayTag());
}

void UBlotGameplayAbility_RangedWeapon::OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& InData, FGameplayTag ApplicationTag)
{
	UAbilitySystemComponent* MyAbilityComponent = CurrentActorInfo->AbilitySystemComponent.Get();
	check(MyAbilityComponent);

	if (const FGameplayAbilitySpec* AbilitySpec = MyAbilityComponent->FindAbilitySpecFromHandle(CurrentSpecHandle))
	{
		FScopedPredictionWindow	ScopedPrediction(MyAbilityComponent);

		// Take ownership of the target data to make sure no callbacks into game code invalidate it out from under us
		FGameplayAbilityTargetDataHandle LocalTargetDataHandle(MoveTemp(const_cast<FGameplayAbilityTargetDataHandle&>(InData)));

		if (CurrentActorInfo->IsLocallyControlled() && !CurrentActorInfo->IsNetAuthority())
		{
			MyAbilityComponent->CallServerSetReplicatedTargetData(CurrentSpecHandle, CurrentActivationInfo.GetActivationPredictionKey(), LocalTargetDataHandle, ApplicationTag, MyAbilityComponent->ScopedPredictionKey);
		}

		// See if we still have ammo
		if (CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo))
		{
			OnRangedWeaponTargetDataReady(LocalTargetDataHandle);
		}
		else
		{
			UE_LOG(LogBlot, Warning, TEXT("Weapon ability %s failed to commit "), *GetPathName());
			K2_EndAbility();
		}
	}

	// We've processed the data
	MyAbilityComponent->ConsumeClientReplicatedTargetData(CurrentSpecHandle, CurrentActivationInfo.GetActivationPredictionKey());
}

void UBlotGameplayAbility_RangedWeapon::PerformLocalTargeting(TArray<FHitResult>& OutHits)
{
	APawn* const AvatarPawn = Cast<APawn>(GetAvatarActorFromActorInfo());

	UCommonRangedWeaponInstance* WeaponData = GetWeaponInstance();
	if (AvatarPawn && AvatarPawn->IsLocallyControlled() && WeaponData)
	{
		FRangedWeaponFiringInput InputData;
		InputData.WeaponData = WeaponData;
		InputData.bCanPlayBulletFX = (AvatarPawn->GetNetMode() != NM_DedicatedServer);

		//@TODO: Should do more complicated logic here when the player is close to a wall, etc...
		const FTransform TargetTransform = GetTargetingTransform(AvatarPawn, EBlotAbilityTargetingSource::CameraTowardsFocus);
		InputData.AimDir = TargetTransform.GetUnitAxis(EAxis::X);
		InputData.StartTrace = TargetTransform.GetTranslation();
		InputData.EndAim = InputData.StartTrace + InputData.AimDir * WeaponData->GetMaxDamageRange();
		
		TraceBulletsInCartridge(InputData, /*out*/ OutHits);
	}
}

FTransform UBlotGameplayAbility_RangedWeapon::GetTargetingTransform(APawn* SourcePawn, EBlotAbilityTargetingSource Source) const
{
	check(SourcePawn);
	AController* Controller = SourcePawn->Controller;

	FVector CamLoc;
	FRotator CamRot;

	if ((Controller != nullptr) && Source == EBlotAbilityTargetingSource::CameraTowardsFocus)
	{
		if (APlayerController* PC = Cast<APlayerController>(Controller))
		{
			PC->GetPlayerViewPoint(/*out*/ CamLoc, /*out*/ CamRot);
			return FTransform(CamRot, CamLoc);
		}
		else if (AAIController* AIController = Cast<AAIController>(Controller))
		{
			CamRot = Controller->GetControlRotation();
			CamLoc = SourcePawn->GetActorLocation() + FVector(0, 0, SourcePawn->BaseEyeHeight);
			return FTransform(CamRot, CamLoc);
		}
	}

	UE_LOG(LogBlot, Warning, TEXT("TargetingSource not supported or invalid!"));
	return FTransform();
}

void UBlotGameplayAbility_RangedWeapon::TraceBulletsInCartridge(const FRangedWeaponFiringInput& InputData, OUT TArray<FHitResult>& OutHits)
{
	UCommonRangedWeaponInstance* WeaponData = InputData.WeaponData;
	check(WeaponData);
	
	const int32 BulletsPerCartridge = WeaponData->GetBulletsPerCartridge();
	const float BulletSpreadDegrees = WeaponData->GetBulletSpread(); 
	const float BulletSpreadRadians = FMath::DegreesToRadians(BulletSpreadDegrees);

	for (int32 BulletIndex = 0; BulletIndex < BulletsPerCartridge; ++BulletIndex)
	{
		TArray<FHitResult> AllImpacts;

		//Add spread
		const FVector ShotDirection = (InputData.EndAim - InputData.StartTrace).GetSafeNormal();
		const FVector SpreadDirection = FMath::VRandCone(ShotDirection, BulletSpreadRadians); 
		const FVector TraceEnd = InputData.StartTrace + SpreadDirection * (InputData.EndAim - InputData.StartTrace).Size();
		
		WeaponLineTraceMulti(InputData.StartTrace, TraceEnd, /*bIsSimulated=*/ false, /*out*/ AllImpacts);

#if ENABLE_DRAW_DEBUG
		if (BlotConsoleVariables::DrawBulletTracesDuration > 0.0f)
		{
			static float DebugThickness = 2.0f;
			DrawDebugLine(GetWorld(), InputData.StartTrace, TraceEnd, FColor::Yellow, false, BlotConsoleVariables::DrawBulletTracesDuration, 0, DebugThickness);
		}
#endif
		
		if (AllImpacts.Num() > 0)
		{
			const AActor* HitActor =AllImpacts.Last().GetActor();
			if (HitActor)
			{
#if ENABLE_DRAW_DEBUG
				if (BlotConsoleVariables::DrawBulletHitDuration > 0.0f)
				{
					DrawDebugPoint(GetWorld(), AllImpacts.Last().ImpactPoint, BlotConsoleVariables::DrawBulletHitRadius, FColor::Red, false, BlotConsoleVariables::DrawBulletHitRadius);
				}
#endif
			}
			
			if (CanPenetrate)
			{
				OutHits.Append(AllImpacts);
				continue;
			}
			
			int32 FirstValidIndex=FindFirstPawnHitResult(AllImpacts);
			if (AllImpacts.IsValidIndex(FirstValidIndex))
			{
				OutHits.Add(AllImpacts[FirstValidIndex]);
				continue;
			}
			else
			{
				//If not hit pawn ,add Last taht is the first block point
				OutHits.Add(AllImpacts.Last());
			}
		}
		else
		{
			// Make sure there's always an entry in OutHits so the direction can be used for tracers, etc...
			FHitResult Hit;
			// Locate the fake 'impact' at the end of the trace
			Hit.Location = TraceEnd;
			Hit.ImpactPoint= TraceEnd;
			Hit.TraceStart = InputData.StartTrace;
			Hit.TraceEnd =TraceEnd;
			OutHits.Add(Hit);	
		}
	}
}

void UBlotGameplayAbility_RangedWeapon::AddAdditionalTraceIgnoreActors(FCollisionQueryParams& TraceParams) const
{
	if (AActor* Avatar = GetAvatarActorFromActorInfo())
	{
		// Ignore any actors attached to the avatar doing the shooting
		TArray<AActor*> AttachedActors;
		Avatar->GetAttachedActors(/*out*/ AttachedActors);
		TraceParams.AddIgnoredActors(AttachedActors);
	}
}

void UBlotGameplayAbility_RangedWeapon::WeaponLineTraceMulti(const FVector& StartTrace, const FVector& EndTrace, bool bIsSimulated, OUT TArray<FHitResult>& OutHitResults) const
{
	TArray<FHitResult> HitResults;
	
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(WeaponTrace), /*bTraceComplex=*/ true, /*IgnoreActor=*/ GetAvatarActorFromActorInfo());
	TraceParams.bReturnPhysicalMaterial = true;
	AddAdditionalTraceIgnoreActors(TraceParams);

	constexpr ECollisionChannel TraceChannel = Blot_TraceChannel_Weapon;

	GetWorld()->LineTraceMultiByChannel(HitResults, StartTrace, EndTrace, TraceChannel, TraceParams);

	FHitResult Hit(ForceInit);
	if (HitResults.Num() > 0)
	{
		// Filter the output list to prevent multiple hits on the same actor;
		// this is to prevent a single bullet dealing damage multiple times to
		// a single actor if using an overlap trace
		for (FHitResult& CurHitResult : HitResults)
		{
			auto Pred = [&CurHitResult](const FHitResult& Other)
			{
				return Other.HitObjectHandle == CurHitResult.HitObjectHandle;
			};

			if (!OutHitResults.ContainsByPredicate(Pred))
			{
				OutHitResults.Add(CurHitResult);
			}
		}
	}
}

int32 UBlotGameplayAbility_RangedWeapon::FindFirstPawnHitResult(const TArray<FHitResult>& HitResults)
{
	for (int32 Idx = 0; Idx < HitResults.Num(); ++Idx)
	{
		const FHitResult& CurHitResult = HitResults[Idx];
		if (CurHitResult.HitObjectHandle.DoesRepresentClass(APawn::StaticClass()))
		{
			// If we hit a pawn, we're good
			return Idx;
		}
		else
		{
			AActor* HitActor = CurHitResult.HitObjectHandle.FetchActor();
			if ((HitActor != nullptr) && (HitActor->GetAttachParentActor() != nullptr) && (Cast<APawn>(HitActor->GetAttachParentActor()) != nullptr))
			{
				// If we hit something attached to a pawn, we're good
				return Idx;
			}
		}
	}

	return INDEX_NONE;
}

