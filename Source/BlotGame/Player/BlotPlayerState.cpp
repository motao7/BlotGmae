// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BlotPlayerState.h"

#include "BlotCombatAttributeSet.h"
#include "BlotAbilitySystemComponent.h"
#include "ExperienceAbilitySet.h"
#include "ExperienceManagerComponent.h"
#include "ExperiencePawnData.h"
#include "GameFramework/GameStateBase.h"
#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"


ABlotPlayerState::ABlotPlayerState(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	// AbilitySystemComponent needs to be updated at a high frequency.
	NetUpdateFrequency = 100.0f;

	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UBlotAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	CombatAttributeSet=CreateDefaultSubobject<UBlotCombatAttributeSet>(TEXT("CombatAttributeSet"));
	
	MyTeamId=FGenericTeamId::NoTeam;
}

void ABlotPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//只有在属性变化的时候进行同步
	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased=true;

	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass,MyTeamId,SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass,ExperiencePawnData,SharedParams);
}

UBlotAbilitySystemComponent* ABlotPlayerState::GetBlotAbilitySystemComponent()
{
	return Cast<UBlotAbilitySystemComponent>(AbilitySystemComponent);
}

UAbilitySystemComponent* ABlotPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABlotPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	check(AbilitySystemComponent);
	const UWorld* World = GetWorld();
	
	//Client only need get PawnData，so only server bind OnExperienceLoaded,client only Replicated PawnData
	//Another reason World->GetNetMode() != NM_Client is GameState is Replicated to client,so in this time client may be not get GameState
	if (World && World->IsGameWorld() && World->GetNetMode() != NM_Client)
	{
		AGameStateBase* GameState = GetWorld()->GetGameState();
		check(GameState);
		UExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UExperienceManagerComponent>();
		check(ExperienceComponent);
		ExperienceComponent->CallOrReigister_OnExperienceLoaded(FOnExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
	}
}

void ABlotPlayerState::SetPawnData(const UExperiencePawnData* PawnData)
{
	ExperiencePawnData=PawnData;

	for (const TObjectPtr<UExperienceAbilitySet> AbilitySet : ExperiencePawnData->AbilitySets)
	{
		if (AbilitySet)
		{
			AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr);
		}
	}
}

void ABlotPlayerState::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	if (HasAuthority())
	{
		const FGenericTeamId OldTeamID = MyTeamId;

		MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, MyTeamId, this);
		MyTeamId = NewTeamID;
		ConditionalBroadcastTeamChanged(this, OldTeamID, NewTeamID);
	}
}

FGenericTeamId ABlotPlayerState::GetGenericTeamId() const
{
	return MyTeamId;
}

FOnTeamChangedDelegateSignature& ABlotPlayerState::GetTeamChangedDelegateChecked()
{
	check(&OnTeamChangedPlayerStateDelegate);
	return OnTeamChangedPlayerStateDelegate;
}

void ABlotPlayerState::OnRep_TeamId(FGenericTeamId OldMyTeamId)
{
	ConditionalBroadcastTeamChanged(this, OldMyTeamId, MyTeamId);
}

void ABlotPlayerState::OnExperienceLoaded(const UExperienceDefination* ExperienceDefination)
{
	const UExperiencePawnData* PawnData=ExperienceDefination->DefaultPawnData;
	check(PawnData);
	SetPawnData(PawnData);
}

