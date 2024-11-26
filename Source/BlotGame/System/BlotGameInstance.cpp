// Fill out your copyright notice in the Description page of Project Settings.


#include "System/BlotGameInstance.h"

#include "BlotGameplayTag.h"
#include "Components/GameFrameworkComponentManager.h"


void UBlotGameInstance::Init()
{
	Super::Init();

	// Register our custom init states
	UGameFrameworkComponentManager* ComponentManager = GetSubsystem<UGameFrameworkComponentManager>(this);

	if (ensure(ComponentManager))
	{
		ComponentManager->RegisterInitState(BlotGameplayTags::InitState_Spawned, false, FGameplayTag());
		ComponentManager->RegisterInitState(BlotGameplayTags::InitState_DataAvailable, false, BlotGameplayTags::InitState_Spawned);
		ComponentManager->RegisterInitState(BlotGameplayTags::InitState_DataInitialized, false, BlotGameplayTags::InitState_DataAvailable);
		ComponentManager->RegisterInitState(BlotGameplayTags::InitState_GameplayReady, false, BlotGameplayTags::InitState_DataInitialized);
	}

}
