// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Engine/CancellableAsyncAction.h"
#include "AsyncAction_ObserveTeamColors.generated.h"

class UTeamDisplayAsset;
class ITeamGenericTeamAgentInterface;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnObserveTeamChangedSignature, uint8,NewTeamId , UTeamDisplayAsset*, NewDisplayAsset);

/**
 *		异步函数用于监听Player的队伍发生变化时改变角色的外表颜色
 */
UCLASS()
class TEAM_API UAsyncAction_ObserveTeamColors : public UCancellableAsyncAction
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category="Team|AsynicAction", meta=(BlueprintInternalUseOnly="true"))
	static UAsyncAction_ObserveTeamColors* ObserveTeamColors(ACharacter* ObserveCharacte);
	
	UPROPERTY(BlueprintAssignable)
	FOnObserveTeamChangedSignature OnObserveTeamChangedDelegate;
	
	virtual void Activate() override;
	virtual void SetReadyToDestroy() override;

protected:
	UFUNCTION()
	void OnObserveTeamChanged(UObject* ObjectChangingTeam, uint8 OldTeamId, uint8 NewTeamId);

	void BroadcastOnObserveTeamChanged(uint8 NewTeamId) const;
	
	TWeakInterfacePtr<ITeamGenericTeamAgentInterface> GenericTeamAgent;
};
