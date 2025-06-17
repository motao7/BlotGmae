// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BlotGameMode.h"

#include "BlotGameState.h"
#include "BlotLogChannels.h"
#include "BlotWorldSetting.h"
#include "ExperienceDefination.h"
#include "ExperienceManagerComponent.h"
#include "ExperienceWorldSetting.h"
#include "Character/BlotPawnExtensionComponent.h"
#include "Engine/AssetManager.h"
#include "GameFramework/GameStateBase.h"
#include "Player/BlotPlayerController.h"
#include "Player/BlotPlayerState.h"

ABlotGameMode::ABlotGameMode(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	GameStateClass = ABlotGameState::StaticClass();
	PlayerControllerClass = ABlotPlayerController::StaticClass();
	PlayerStateClass = ABlotPlayerState::StaticClass();
}

AGameStateBase* ABlotGameMode::GetGameState()
{
	return GameState;
}

bool ABlotGameMode::IsExperienceLoaded() const
{
	check(GameState);
	UExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UExperienceManagerComponent>();
	check(ExperienceComponent);
	return ExperienceComponent->GetIsExperienceLoadedCompoleted();
}

const UExperiencePawnData* ABlotGameMode::GetPawnDataFromPlayerStateOrExperience(const AController* Controller) const
{
	//从PlayerStata中获取PawnData
	if(Controller!=nullptr)
	{
		if(ABlotPlayerState* BlotPlayerState=Controller->GetPlayerState<ABlotPlayerState>())
		{
			if(const UExperiencePawnData* PawnData = BlotPlayerState->GetPawnData())
			{
				return PawnData;
			}
		}
	}

	//从Experience中获取PawnData
	UExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UExperienceManagerComponent>();
	check(ExperienceComponent);
	return ExperienceComponent->GetCurrentExperience()->DefaultPawnData;
}

void ABlotGameMode::LoadExperience() const
{
	UExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UExperienceManagerComponent>();
	check(ExperienceComponent);
	AExperienceWorldSetting* ExperienceWorldSetting=Cast<AExperienceWorldSetting>(GetWorldSettings());
	ExperienceComponent->StartLoadExperience(ExperienceWorldSetting->GetDefaultExperience());
}

void ABlotGameMode::OnExperienceLoaded(const UExperienceDefination* ExperienceDefination)
{
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PC = Cast<APlayerController>(*Iterator);
		if ((PC != nullptr) && (PC->GetPawn() == nullptr))
		{
			if (PlayerCanRestart(PC))
			{
				RestartPlayer(PC);
			}
		}
	}
	
}

void ABlotGameMode::TravelToStoredMap() const
{
	// // 2. 获取 ExperienceComponent
	// UExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UExperienceManagerComponent>();
	// if (!ExperienceComponent)
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("Missing ExperienceManagerComponent on GameState!"));
	// 	return;
	// }
	//
	// // 3. 获取当前 Experience
	// const UExperienceDefination* Experience = ExperienceComponent->GetCurrentExperience();
	// if (!Experience || !Experience->MapID.IsValid())
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("Invalid Experience or MapID!"));
	// 	return;
	// }
	//
	// FSoftObjectPath MapPath = UAssetManager::Get().GetPrimaryAssetPath(Experience->MapID);
	// if (MapPath.IsValid())
	// {
	// 	ServerTravelToMap(MapPath.GetAssetName());
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("Failed to resolve map path!"));
	// }
}

void ABlotGameMode::ServerTravelToMap(const FString& MapName) const
{
	if (MapName.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("MapName is empty!"));
		return;
	}

	// 格式化为完整地图路径（如 "/Game/Maps/MainMenu?listen"）
	const FString FullPath = FString::Printf(TEXT("/Game/Maps/%s?listen"), *MapName);
	GetWorld()->ServerTravel(FullPath);
}

void ABlotGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	//下一帧开始加载Experience因为此时GameState还没有创建
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::LoadExperience);
}

void ABlotGameMode::InitGameState()
{
	Super::InitGameState();

	UExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UExperienceManagerComponent>();
	check(ExperienceComponent);
	ExperienceComponent->CallOrReigister_OnExperienceLoaded(FOnExperienceLoaded::FDelegate::CreateUObject(this,&ThisClass::OnExperienceLoaded));
}

void ABlotGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	if(IsExperienceLoaded())
	{
		Super::HandleStartingNewPlayer_Implementation(NewPlayer);	
	}
}

APawn* ABlotGameMode::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	// Never save the default player pawns into a map, ensure they don't persist across saves.
	SpawnInfo.ObjectFlags |= RF_Transient;
	SpawnInfo.bDeferConstruction = true;

	// 获取玩家数据并验证
	const UExperiencePawnData* PawnData = GetPawnDataFromPlayerStateOrExperience(NewPlayer);
	if (!PawnData)
	{
		UE_LOG(LogBlot, Error, TEXT("Failed to retrieve PawnData for player."));
		return nullptr;
	}

	if (!PawnData->PawnClass)
	{
		UE_LOG(LogBlot, Error, TEXT("PawnClass is invalid for the player: %s"), *NewPlayer->GetName());
		return nullptr;
	}
	
	// 生成角色
	APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(PawnData->PawnClass, SpawnTransform, SpawnInfo);
	if (!SpawnedPawn)
	{
		UE_LOG(LogBlot, Error, TEXT("Failed to spawn pawn for player: %s"), *NewPlayer->GetName());
		return nullptr;
	}

	UBlotPawnExtensionComponent* PawnExtCom=SpawnedPawn->FindComponentByClass<UBlotPawnExtensionComponent>();
	if (!PawnExtCom)
	{
		UE_LOG(LogBlot, Error, TEXT("UBlotPawnExtensionComponent not found on Pawn %s!"), *GetNameSafe(SpawnedPawn));
		return nullptr; 
	}

	// 完成角色生成
	SpawnedPawn->FinishSpawning(SpawnTransform);

	UE_LOG(LogBlot, Log, TEXT("Successfully spawned pawn for player: %s"), *NewPlayer->GetName());
	return SpawnedPawn;
}

