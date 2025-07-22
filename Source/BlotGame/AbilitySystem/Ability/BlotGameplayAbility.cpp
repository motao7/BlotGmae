#include "BlotGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "BlotAbilityCost.h"
#include "BlotAbilitySystemComponent.h"
#include "Character/BlotCharacter.h"
#include "Character/BlotHeroComponent.h"
#include "Character/BlotParryComponent.h"
#include "Player/BlotPlayerController.h"

ABlotCharacter* UBlotGameplayAbility::GetBlotCharacterFromActorInfo() const
{
	return (CurrentActorInfo?Cast<ABlotCharacter>(CurrentActorInfo->AvatarActor.Get()):nullptr);
}

UBlotAbilitySystemComponent* UBlotGameplayAbility::GetBlotAbilitySystemComponentFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<UBlotAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent.Get()) : nullptr);
}

ABlotPlayerController* UBlotGameplayAbility::GetBlotPlayerControllerFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<ABlotPlayerController>(CurrentActorInfo->PlayerController.Get()) : nullptr);
}

AController* UBlotGameplayAbility::GetControllerFromActorInfo() const
{
	if (CurrentActorInfo)
	{
		if (AController* PC = CurrentActorInfo->PlayerController.Get())
		{
			return PC;
		}

		// Look for a player controller or pawn in the owner chain.
		AActor* TestActor = CurrentActorInfo->OwnerActor.Get();
		while (TestActor)
		{
			if (AController* C = Cast<AController>(TestActor))
			{
				return C;
			}

			if (APawn* Pawn = Cast<APawn>(TestActor))
			{
				return Pawn->GetController();
			}

			TestActor = TestActor->GetOwner();
		}
	}

	return nullptr;
}

UBlotHeroComponent* UBlotGameplayAbility::GetHeroComponentFromActorInfo() const
{
	return (CurrentActorInfo ? (CurrentActorInfo->AvatarActor.Get()->FindComponentByClass<UBlotHeroComponent>()) : nullptr);
}

UBlotParryComponent* UBlotGameplayAbility::GetParryComponentFromActorInfo() const
{
	return (CurrentActorInfo ? (CurrentActorInfo->AvatarActor.Get()->FindComponentByClass<UBlotParryComponent>()) : nullptr);
}

bool UBlotGameplayAbility::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CheckCost(Handle, ActorInfo, OptionalRelevantTags) || !ActorInfo)
	{
		return false;
	}

	// Verify we can afford any additional costs
	for (const TObjectPtr<UBlotAbilityCost>& AdditionalCost : AdditionalCosts)
	{
		if (AdditionalCost != nullptr)
		{
			if (!AdditionalCost->CheckCost(this, Handle, ActorInfo))
			{
				return false;
			}
		}
	}

	return true;
}

void UBlotGameplayAbility::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);

	check(ActorInfo);

	// Used to determine if the ability actually hit a target (as some costs are only spent on successful attempts)
	auto DetermineIfAbilityHitTarget = [&]()
	{
		if (ActorInfo->IsNetAuthority())
		{
			if (UBlotAbilitySystemComponent* ASC = Cast<UBlotAbilitySystemComponent>(ActorInfo->AbilitySystemComponent.Get()))
			{
				FGameplayAbilityTargetDataHandle TargetData;
				ASC->GetAbilityTargetData(Handle, ActivationInfo, TargetData);
				for (int32 TargetDataIdx = 0; TargetDataIdx < TargetData.Data.Num(); ++TargetDataIdx)
				{
					if (UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetData, TargetDataIdx))
					{
						return true;
					}
				}
			}
		}

		return false;
	};

	// Pay any additional costs
	bool bAbilityHitTarget = false;
	bool bHasDeterminedIfAbilityHitTarget = false;
	for (const TObjectPtr<UBlotAbilityCost>& AdditionalCost : AdditionalCosts)
	{
		if (AdditionalCost != nullptr)
		{
			if (AdditionalCost->ShouldOnlyApplyCostOnHit())
			{
				if (!bHasDeterminedIfAbilityHitTarget)
				{
					bAbilityHitTarget = DetermineIfAbilityHitTarget();
					bHasDeterminedIfAbilityHitTarget = true;
				}

				if (!bAbilityHitTarget)
				{
					continue;
				}
			}

			AdditionalCost->ApplyCost(this, Handle, ActorInfo, ActivationInfo);
		}
	}
}

