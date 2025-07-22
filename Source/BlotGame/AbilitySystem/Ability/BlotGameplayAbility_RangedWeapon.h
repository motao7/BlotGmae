// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/BlotGameplayAbility_FromEquipment.h"
#include "Weapon/CommonRangedWeaponInstance.h"
#include "BlotGameplayAbility_RangedWeapon.generated.h"

UENUM(BlueprintType)
enum class EBlotAbilityTargetingSource : uint8
{
	// From the player's camera towards camera focus
	CameraTowardsFocus,
	// From the pawn's center, in the pawn's orientation
	PawnForward,
	// From the pawn's center, oriented towards camera focus
	PawnTowardsFocus,
	// From the weapon's muzzle or location, in the pawn's orientation
	WeaponForward,
	// From the weapon's muzzle or location, towards camera focus
	WeaponTowardsFocus,
};


/**
 * 
 */
UCLASS()
class BLOTGAME_API UBlotGameplayAbility_RangedWeapon : public UBlotGameplayAbility_FromEquipment
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	struct FRangedWeaponFiringInput
	{
		// Start of the trace
		FVector StartTrace;

		// End of the trace if aim were perfect
		FVector EndAim;

		// The direction of the trace if aim were perfect
		FVector AimDir;

		// The weapon instance / source of weapon data
		UCommonRangedWeaponInstance* WeaponData = nullptr;

		// Can we play bullet FX for hits during this trace
		bool bCanPlayBulletFX = false;

		FRangedWeaponFiringInput()
			: StartTrace(ForceInitToZero)
			, EndAim(ForceInitToZero)
			, AimDir(ForceInitToZero)
		{
		}
	};
	
	UCommonRangedWeaponInstance* GetWeaponInstance() const;
	
	UFUNCTION(BlueprintCallable)
	void StartRangedWeaponTargeting();

	/**Client send TargetData to server/,and Commit Abilty*/
	void OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& InData, FGameplayTag ApplicationTag);

	void PerformLocalTargeting(TArray<FHitResult>& OutHits);

	FTransform GetTargetingTransform(APawn* SourcePawn, EBlotAbilityTargetingSource Source) const;

	void TraceBulletsInCartridge(const FRangedWeaponFiringInput& InputData, OUT TArray<FHitResult>& OutHits);
	
	void AddAdditionalTraceIgnoreActors(FCollisionQueryParams& TraceParams) const;

	/**Trace no penetrate*/
	void WeaponLineTraceMulti(const FVector& StartTrace, const FVector& EndTrace, bool bIsSimulated, OUT TArray<FHitResult>& OutHitResults) const;

	UFUNCTION(BlueprintImplementableEvent)
	void OnRangedWeaponTargetDataReady(const FGameplayAbilityTargetDataHandle& TargetData);

	int32 FindFirstPawnHitResult(const TArray<FHitResult>& HitResults);

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	bool CanPenetrate=false;

private:
	FDelegateHandle OnTargetDataReadyCallbackDelegateHandle;
};
