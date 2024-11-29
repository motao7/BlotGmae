// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamCreateComponent.h"
#include "Engine/World.h"
#include "ExperienceManagerComponent.h"
#include "ModularGameMode.h"
#include "TeamGenericTeamAgentInterface.h"
#include "TeamPublicTeamInfo.h"
#include "GameFramework/GameState.h"
#include "GameFramework/PlayerState.h"


UTeamCreateComponent::UTeamCreateComponent(const FObjectInitializer& ObjectInitialize)
	:Super(ObjectInitialize)
{
	PublicTeamInfoClass=ATeamPublicTeamInfo::StaticClass();
}

void UTeamCreateComponent::BeginPlay()
{
	Super::BeginPlay();

	AGameStateBase* GameStateBase=GetGameState<AGameStateBase>();
	UExperienceManagerComponent* ExperienceManagerComponent=GameStateBase->FindComponentByClass<UExperienceManagerComponent>();
	ExperienceManagerComponent->CallOrReigister_OnExperienceLoaded_HighPriority(FOnExperienceLoaded::FDelegate::CreateUObject(this,&ThisClass::OnExperienceLoaded));
}

void UTeamCreateComponent::OnExperienceLoaded(const UExperienceDefination* ExperienceDefination)
{
#if WITH_SERVER_CODE
	if(HasAuthority())
	{
		ServerCreateTeam();
		ServerAssignPlayerToTeam();
	}
#endif //WITH_SERVER_CODE
}

#if WITH_SERVER_CODE
void UTeamCreateComponent::ServerCreateTeam()
{
	check(HasAuthority());
	//@TODO: ensure the team doesn't already exist
	UWorld* World = GetWorld();

	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride= ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	for(auto TeamSetting:TeamsSetting)
	{	
		check(World);
		ATeamPublicTeamInfo* NewTeamPublicTeamInfo=World->SpawnActor<ATeamPublicTeamInfo>(PublicTeamInfoClass,ActorSpawnParameters);
		NewTeamPublicTeamInfo->SetTeamId(TeamSetting.Key);
		NewTeamPublicTeamInfo->SetDisplayAsset(TeamSetting.Value);
	}
	//TODO : 创建PrivateTeamInfo
}

//如果一个函数中有变量
void UTeamCreateComponent::ServerAssignPlayerToTeam()
{
	//为已经存在玩家分配队伍
	AGameStateBase* GameState=GetGameState<AGameStateBase>();
	for(APlayerState* PlayerState:GameState->PlayerArray)
	{
		ServerSetPlayerStateTeamId(PlayerState);
	}
	
	//监听新加入的玩家，为新加入的玩家分配队伍
	AModularGameModeBase* ModularGameModeBase=GetGameMode<AModularGameModeBase>();
	check(ModularGameModeBase);
	ModularGameModeBase->OnGameModePlayerInitialized.AddUObject(this,&ThisClass::ServerOnPlayerInitilized);
}

void UTeamCreateComponent::ServerSetPlayerStateTeamId(APlayerState* PlayerState) const
{
	if (IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(PlayerState))
	{
		//如果玩家是一个Spectator不设置团队
		if(PlayerState->IsOnlyASpectator())
		{
			TeamAgent->SetGenericTeamId(FGenericTeamId::NoTeam);
		}
		else
		{
			const FGenericTeamId NewBestTeamId=IntegerToGenericTeamId(ServerGetBestTeamIdForPlayer());
			TeamAgent->SetGenericTeamId(NewBestTeamId);	
		}
	}
}

uint8 UTeamCreateComponent::ServerGetBestTeamIdForPlayer() const
{
	//TODO : 分配队伍---这里暂时总是将玩家分配到队伍人数最少的队伍
	uint8 TeamNum = TeamsSetting.Num();
	TMap<uint8, uint8> TeamsCount;

	// 初始化 TeamsCount 字典
	for (const auto& TeamSetting : TeamsSetting)
	{
		TeamsCount.Add(TeamSetting.Key, 0);
	}

	AGameStateBase* GameState = GetGameState<AGameStateBase>();
	check(GameState);

	uint8 MinNumberTeam = 0;

	for (TObjectPtr<APlayerState> PS : GameState->PlayerArray)
	{
		if (const ITeamGenericTeamAgentInterface* GenericTeamPS = Cast<ITeamGenericTeamAgentInterface>(PS))
		{
			const uint8 TeamId = GenericTeamIdToInteger(GenericTeamPS->GetGenericTeamId());

			if (TeamId != 255)  // 只处理有效的 TeamId
			{
				// 更新队伍人数
				TeamsCount[TeamId]++;
			}
		}
	}

	for(const auto& KVP:TeamsCount)
	{
		if(KVP.Value<TeamsCount[MinNumberTeam])
		{
			MinNumberTeam=KVP.Key;
		}
	}

	return MinNumberTeam;
}

void UTeamCreateComponent::ServerOnPlayerInitilized(AGameModeBase* GameMode, AController* NewPlayer)
{
	check(GameMode);
	check(NewPlayer);
	APlayerState* PlayerState=NewPlayer->GetPlayerState<APlayerState>();
	check(PlayerState);
	ServerSetPlayerStateTeamId(PlayerState);
}

#endif //WITH_SERVER_CODE
