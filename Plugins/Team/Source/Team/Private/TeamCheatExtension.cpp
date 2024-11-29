// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamCheatExtension.h"

#include "Team.h"
#include "TeamSubsystem.h"


void UTeamCheatExtension::SetTeam(const uint8 TeamId) const
{
	if(const UTeamSubsystem* TeamSubsystem=GetWorld()->GetSubsystem<UTeamSubsystem>())
	{
		check(TeamSubsystem);
		TeamSubsystem->SetTeamForPlayer(GetPlayerController(),TeamId);
		return;
	}
	else
	{
		UE_LOG(LogTeam,Type::Error,TEXT("TeamCheat中SetTeam函数报错,获取UTeamSubsystem失败"));
	}
}
