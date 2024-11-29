// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncAction_ObserveTeamColors.h"

#include "Team.h"
#include "TeamGenericTeamAgentInterface.h"
#include "TeamInfoBase.h"
#include "TeamSubsystem.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerState.h" 

UAsyncAction_ObserveTeamColors* UAsyncAction_ObserveTeamColors::ObserveTeamColors(ACharacter* ObserveCharacte)
{
	UAsyncAction_ObserveTeamColors* Action = nullptr;

	if (ObserveCharacte != nullptr)
	{
		Action = NewObject<UAsyncAction_ObserveTeamColors>();
		if(ITeamGenericTeamAgentInterface* GenericTeamAgent=Cast<ITeamGenericTeamAgentInterface>(ObserveCharacte->GetPlayerState()))
		{
			Action->GenericTeamAgent = TWeakInterfacePtr<ITeamGenericTeamAgentInterface>(GenericTeamAgent);
			Action->RegisterWithGameInstance(ObserveCharacte);
		}
	}
	return Action;
}

void UAsyncAction_ObserveTeamColors::Activate()
{
	bool bCouldSucceed = false;
	ITeamGenericTeamAgentInterface* TeamAgent=GenericTeamAgent.Get();
	if(TeamAgent!=nullptr)
	{
		//第一次激活直接Broadcast
		BroadcastOnObserveTeamChanged(TeamAgent->GetGenericTeamId());
	
		//绑定PlayerState上的委托，聆听后续TeamId的变化
		FOnTeamChangedDelegateSignature& OnTeamChangedDelegate=TeamAgent->GetTeamChangedDelegateChecked();
		OnTeamChangedDelegate.AddDynamic(this,&ThisClass::OnObserveTeamChanged);

		bCouldSucceed = true;
	}
	
	// We weren't able to bind to a delegate so we'll never get any additional updates
	if (!bCouldSucceed)
	{
		SetReadyToDestroy();
	}
}

void UAsyncAction_ObserveTeamColors::SetReadyToDestroy()
{
	Super::SetReadyToDestroy();

	// 如果这个异步节点准备Destory了我们将绑定到TeamInterface委托上的回调函数都清除
	if (ITeamGenericTeamAgentInterface* TeamInterface = GenericTeamAgent.Get())
	{
		TeamInterface->GetTeamChangedDelegateChecked().RemoveAll(this);
	}
}

void UAsyncAction_ObserveTeamColors::BroadcastOnObserveTeamChanged(uint8 NewTeamId) const
{
	//因为这里为异步函数所以不能直接使用GetWorld()而是GetWorldFromContextObject
	UWorld* World = GEngine->GetWorldFromContextObject(GenericTeamAgent.GetObject(), EGetWorldErrorMode::LogAndReturnNull);
	UTeamSubsystem* TeamSubsystem = UWorld::GetSubsystem<UTeamSubsystem>(World);

	check(TeamSubsystem);
	if(ATeamInfoBase* TeamInfoBase=TeamSubsystem->GetTeamInfoForTeamId(NewTeamId); TeamInfoBase!=nullptr)
	{
		OnObserveTeamChangedDelegate.Broadcast(NewTeamId,TeamInfoBase->GetDisplayAsset());
	}
}

void UAsyncAction_ObserveTeamColors::OnObserveTeamChanged(UObject* ObjectChangingTeam, uint8 OldTeamId, uint8 NewTeamId)
{
	BroadcastOnObserveTeamChanged(NewTeamId);
}

