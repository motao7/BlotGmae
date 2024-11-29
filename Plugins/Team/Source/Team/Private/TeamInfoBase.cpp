// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamInfoBase.h"

#include "TeamSubsystem.h"
#include "Net/UnrealNetwork.h"

ATeamInfoBase::ATeamInfoBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, TeamId(INDEX_NONE)
{
	bReplicates = true;
	bAlwaysRelevant = true;
	NetPriority = 3.0f;
	SetReplicatingMovement(false);
}

void ATeamInfoBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//COND_InitialOnly只有在初始化的时候复制到客户端!!!
	DOREPLIFETIME_CONDITION(ThisClass, TeamId, COND_InitialOnly);
	DOREPLIFETIME_CONDITION(ThisClass, DisplayAsset, COND_InitialOnly);
}
void ATeamInfoBase::SetTeamId(const uint8 NewTeamId)
{
	TeamId=NewTeamId;
	RegisterToTeamSubsystem();
}

void ATeamInfoBase::SetDisplayAsset(UTeamDisplayAsset* NewDisplayAsset)
{
	DisplayAsset=NewDisplayAsset;
	RegisterToTeamSubsystem();
}

void ATeamInfoBase::RegisterToTeamSubsystem()
{
	UTeamSubsystem* TeamSubsystem=GetWorld()->GetSubsystem<UTeamSubsystem>();
	check(TeamSubsystem);
	TeamSubsystem->RegisterTeamInfo(TeamId, this);
}

void ATeamInfoBase::OnRep_TeamId()
{
	RegisterToTeamSubsystem();
}

void ATeamInfoBase::OnRep_DisplayAsset()
{
	RegisterToTeamSubsystem();
}
