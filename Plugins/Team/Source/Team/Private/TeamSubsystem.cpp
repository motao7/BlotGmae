// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamSubsystem.h"

#include "Team.h"
#include "TeamCheatExtension.h"
#include "TeamGenericTeamAgentInterface.h"
#include "GameFramework/CheatManager.h"
#include "GameFramework/PlayerState.h"


void UTeamSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	OnCheatManagerCreatedHandle=UCheatManager::RegisterForOnCheatManagerCreated(FOnCheatManagerCreated::FDelegate::CreateLambda
		([](UCheatManager* CheatManager)
		{
			CheatManager->AddCheatManagerExtension(NewObject<UTeamCheatExtension>(CheatManager));
		}));
}

void UTeamSubsystem::Deinitialize()
{
	UCheatManager::UnregisterFromOnCheatManagerCreated(OnCheatManagerCreatedHandle);

	Super::Deinitialize();
}

void UTeamSubsystem::RegisterTeamInfo(const uint8 TeamId,ATeamInfoBase* TeamInfo)
{
	TeamInfoMap.FindOrAdd(TeamId)=TeamInfo;
}

ATeamInfoBase* UTeamSubsystem::GetTeamInfoForTeamId(const uint8 TeamId)
{
	//uint8最大为255如果为255代表为没有队伍
	if(TeamId==255) return nullptr;
	
	//解决输入的TeamId超过Map范围的问题
	if(ATeamInfoBase* Result=*TeamInfoMap.Find(TeamId))
	{
		return Result;
	}
	else
	{
		return nullptr;
	}
}

void UTeamSubsystem::SetTeamForPlayer(const APlayerController* PC,uint8 TeamId) const
{
	int32 TeamNum=TeamInfoMap.Num();
	if(TeamId>=TeamNum-1||TeamId<0)
	{
		UE_LOG(LogTeam,Type::Error,TEXT("想要设置的TeamId的值超过创建的Team的数量范围，大于Team的数量或为负数"));
		return;
	}
	if(PC!=nullptr)
	{
		if(ITeamGenericTeamAgentInterface* GenericTeamAgent=PC->GetPlayerState<ITeamGenericTeamAgentInterface>())
		{
			GenericTeamAgent->SetGenericTeamId(TeamId);
			return;
		}
	}
	UE_LOG(LogTeam,Type::Error,TEXT("SetTeamForPlayer函数中，不能为玩家控制器:%s设置队伍"),*PC->GetName());
}
