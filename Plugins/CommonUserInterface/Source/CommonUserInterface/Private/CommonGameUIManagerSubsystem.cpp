// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonGameUIManagerSubsystem.h"

#include "CommonGameUIPolicy.h"


void UCommonGameUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (!CurrentPolicy && !DefaultUIPolicyClass.IsNull())
	{
		if(TSubclassOf<UCommonGameUIPolicy> PolicyClass = DefaultUIPolicyClass.LoadSynchronous())
		{
			SwitchToPolicy(NewObject<UCommonGameUIPolicy>(this, PolicyClass));
		}
	}
}

void UCommonGameUIManagerSubsystem::NotifyPlayerAdded(UCommonLocalPlayer* LocalPlayer)
{
	if (ensure(LocalPlayer) && CurrentPolicy)
	{
		CurrentPolicy->NotifyPlayerAdded(LocalPlayer);
	}
}

void UCommonGameUIManagerSubsystem::SwitchToPolicy(UCommonGameUIPolicy* InPolicy)
{
	if (CurrentPolicy != InPolicy)
	{
		CurrentPolicy = InPolicy;
	}
}