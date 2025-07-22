// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Components/GameStateComponent.h"
#include "TeamCreateComponent.generated.h"

class ATeamPublicTeamInfo;
class UTeamDisplayAsset;
class UExperienceDefinition;
/**
 * 
 */
UCLASS()
class TEAM_API UTeamCreateComponent : public UGameStateComponent
{
	GENERATED_BODY()

public:
	UTeamCreateComponent(const FObjectInitializer& ObjectInitialize);
	virtual void BeginPlay() override;

protected:
	void OnExperienceLoaded(const UExperienceDefinition* ExperienceDefination);

#if WITH_SERVER_CODE
	/** 根据组件中的TeamSetting，在服务器中创建TeamInfo，并将TeamInfo注册到TeamSubsystem中 */
	void ServerCreateTeam();
	/** 服务器为已经存在的玩家分配队伍，并监听新Player的加入，当新玩家登入后分配队伍 */
	void ServerAssignPlayerToTeam();
	/** 真正设置PlayerStateTeamId的地方 */
	void ServerSetPlayerStateTeamId(APlayerState* PlayerState) const;
	uint8 ServerGetBestTeamIdForPlayer() const;
	void ServerOnPlayerInitilized(AGameModeBase* GameMode, AController* NewPlayer);
#endif	//WITH_SERVER_CODE

	//TODO : TeamSetting的Tmap结构应该更改分为PublicDisplayAsset和PrivateDisplayAsset当然有需要的时候在用
	UPROPERTY(EditAnywhere,Category="Team")
	TMap<uint8,TObjectPtr<UTeamDisplayAsset>> TeamsSetting;

	UPROPERTY(EditAnywhere,Category="Team")
	TSubclassOf<ATeamPublicTeamInfo> PublicTeamInfoClass;
};
