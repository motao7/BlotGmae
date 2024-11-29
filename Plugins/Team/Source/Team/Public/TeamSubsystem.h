// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TeamSubsystem.generated.h"

class ATeamInfoBase;
class UTeamDisplayAsset;
class ATeamPrivateTeamInfo;

//TODO : 有机会让TeamInfoMap注册的资产为FOverAllTeamInfo
// USTRUCT()
// struct FOverAllTeamInfo
// {
// 	GENERATED_BODY()
//
// 	//全部资产都应该为指针
// public:
// 	//存储只有本地玩家可见的TeamInfo
// 	UPROPERTY()
// 	TObjectPtr<ATeamPrivateTeamInfo> PrivateTeamInfo=nullptr;
//
// 	//存储玩家都可见的TeamInfo
// 	UPROPERTY()
// 	TObjectPtr<ATeamPrivateTeamInfo> PublicTeamInfo=nullptr;
//
// public:
// 	
// };

/**
 *		存储记录TeamInfo，提供获取TeamInfo的函数。服务器调用ServerCreateTeam注册信息到TeamInfoMap而客户端也有TeamInfoMap在TeamInfo类中的OnRep_TeamInfo调用注册
 */
UCLASS()
class TEAM_API UTeamSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	//~ Subsystem Statrt
	/** 将TeamCheatExtension注册到CheatManager中 */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	/** 将TeamCheatExtension从CheatManager移除 */
	virtual void Deinitialize() override;
	//~ Subsystem End

	//~ HelpFunction 
	/** 将TeamInfo注册到TeamInfoMap中 */
	void RegisterTeamInfo(uint8 TeamId, ATeamInfoBase* TeamInfo);
	ATeamInfoBase* GetTeamInfoForTeamId(uint8 TeamId);
	void SetTeamForPlayer(const APlayerController* PC, uint8 TeamId) const;
	//~ HelpFunction End
	
	
protected:
	/** 服务器和客户端都有TeamInfoMap存储TeamInfo */
	UPROPERTY()
	TMap<uint8,TObjectPtr<ATeamInfoBase>> TeamInfoMap;

	FDelegateHandle OnCheatManagerCreatedHandle;
	
};
