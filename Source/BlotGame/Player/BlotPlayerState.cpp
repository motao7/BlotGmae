// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BlotPlayerState.h"

#include "ExperienceManagerComponent.h"
#include "GameFramework/GameStateBase.h"
#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"


ABlotPlayerState::ABlotPlayerState(const FObjectInitializer& ObjectInitialize)
	:Super(ObjectInitialize)
{
	// AbilitySystemComponent needs to be updated at a high frequency.
	NetUpdateFrequency = 100.0f;
	
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

void ABlotPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	const UWorld* World = GetWorld();
	const AGameStateBase* GameStateBase = World->GetGameState();
	check(GameStateBase);
	UExperienceManagerComponent* ExperienceManagerComponent=GameStateBase->FindComponentByClass<UExperienceManagerComponent>();
	check(ExperienceManagerComponent);
	ExperienceManagerComponent->CallOrReigister_OnExperienceLoaded(FOnExperienceLoaded::FDelegate::CreateUObject(this,&ThisClass::OnExperienceLoaded));
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

