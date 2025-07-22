// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BlotAICreationComponent.h"

#include "AIController.h"
#include "BlotGameMode.h"
#include "ExperienceManagerComponent.h"
#include "Character/BlotPawnExtensionComponent.h"


void UBlotAICreationComponent::BeginPlay()
{
	Super::BeginPlay();
	
	AGameStateBase* GameState = GetGameStateChecked<AGameStateBase>();
	UExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UExperienceManagerComponent>();
	check(ExperienceComponent);
	ExperienceComponent->CallOrRegister_OnExperienceLoaded_LowPriority(FOnExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

#if WITH_SERVER_CODE
void UBlotAICreationComponent::SpawnOneBot()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.OverrideLevel = GetComponentLevel();
	SpawnInfo.ObjectFlags |= RF_Transient;
	AAIController* NewController = GetWorld()->SpawnActor<AAIController>(BotControllerClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);

	if (NewController != nullptr)
	{
		ABlotGameMode* GameMode = GetGameMode<ABlotGameMode>();
		check(GameMode);
		
		GameMode->GenericPlayerInitialization(NewController);
		GameMode->RestartPlayer(NewController);

		if (NewController->GetPawn() != nullptr)
		{
			if (UBlotPawnExtensionComponent* PawnExtComponent = NewController->GetPawn()->FindComponentByClass<UBlotPawnExtensionComponent>())
			{
				PawnExtComponent->CheckDefaultInitialization();
			}
		}

		SpawnedBotList.Add(NewController);
	}
}

void UBlotAICreationComponent::ServerCreateBots_Implementation()
{
	if (BotControllerClass == nullptr)
	{
		return;
	}
	
	for (int32 Count = 0; Count < NumBotsToCreate; ++Count)
	{
		SpawnOneBot();
	}
}
#endif

void UBlotAICreationComponent::OnExperienceLoaded(const UExperienceDefinition* Experience)
{
#if WITH_SERVER_CODE
	ServerCreateBots();
#endif
}
