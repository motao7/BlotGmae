// BlotAICreationComponent.cpp
// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/BlotAICreationComponent.h"

#include "AIController.h"
#include "BlotGameMode.h"
#include "ExperienceManagerComponent.h"
#include "Character/BlotPawnExtensionComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

void UBlotAICreationComponent::BeginPlay()
{
	Super::BeginPlay();
	
	AGameStateBase* GameState = GetGameStateChecked<AGameStateBase>();
	UExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UExperienceManagerComponent>();
	check(ExperienceComponent);
	ExperienceComponent->CallOrRegister_OnExperienceLoaded_LowPriority(FOnExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

#if WITH_SERVER_CODE
AAIController* UBlotAICreationComponent::SpawnOneBot(TSubclassOf<ACharacter> CharacterClass, const FVector& Location)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnInfo.OverrideLevel = GetComponentLevel();
	SpawnInfo.ObjectFlags |= RF_Transient;
	
	FRotator SpawnRotation = FRotator::ZeroRotator;
	FVector SpawnLocation = Location;
	
	// 尝试在地面上生成
	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	TraceParams.bTraceComplex = false;
	TraceParams.bReturnPhysicalMaterial = false;
	
	const FVector Start = SpawnLocation + FVector(0.f, 0.f, 100.f);
	const FVector End = SpawnLocation - FVector(0.f, 0.f, 1000.f);
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, TraceParams))
	{
		SpawnLocation = HitResult.Location + FVector(0.f, 0.f, 50.f);
	}
	
	AAIController* NewController = GetWorld()->SpawnActor<AAIController>(BotControllerClass, SpawnLocation, SpawnRotation, SpawnInfo);

	if (NewController != nullptr)
	{
		ABlotGameMode* GameMode = GetGameMode<ABlotGameMode>();
		check(GameMode);

		ACharacter* NewCharacter=GetWorld()->SpawnActor<ACharacter>(CharacterClass, SpawnLocation, SpawnRotation, SpawnInfo);
		
		// 设置控制器的默认 Pawn 类
		if (NewCharacter)
		{
			NewController->SetPawn(NewCharacter);
		}
		
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
		return NewController;
	}
	
	return nullptr;
}

FVector UBlotAICreationComponent::FindSpawnLocation() const
{
	// 获取所有玩家Pawn
	TArray<AActor*> PlayerPawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawn::StaticClass(), PlayerPawns);
	
	if (PlayerPawns.Num() > 0)
	{
		// 随机选择一个玩家作为生成中心
		int32 RandomIndex = FMath::RandRange(0, PlayerPawns.Num() - 1);
		APawn* CenterPawn = Cast<APawn>(PlayerPawns[RandomIndex]);
		
		if (CenterPawn)
		{
			FVector CenterLocation = CenterPawn->GetActorLocation();
			
			// 在最小和最大半径之间随机选择距离
			float Distance = FMath::RandRange(MinSpawnRadius, MaxSpawnRadius);
			
			// 随机角度
			float Angle = FMath::RandRange(0.0f, 2.0f * PI);
			
			// 计算生成位置
			FVector Offset(Distance * FMath::Cos(Angle), Distance * FMath::Sin(Angle), 0.0f);
			FVector SpawnLocation = CenterLocation + Offset;
			
			return SpawnLocation;
		}
	}
	
	// 如果没有找到玩家，则在世界原点附近生成
	return FVector::ZeroVector;
}

void UBlotAICreationComponent::ServerCreateBots_Implementation()
{
	if (BotControllerClass == nullptr)
	{
		return;
	}
	
	// 遍历配置的每个角色类及其数量
	for (const auto& CharacterConfig : CharacterBotConfig)
	{
		TSubclassOf<ACharacter> CharacterClass = CharacterConfig.Key;
		int32 NumToSpawn = CharacterConfig.Value;
		
		// 生成指定数量的该角色类的机器人
		for (int32 Count = 0; Count < NumToSpawn; ++Count)
		{
			FVector SpawnLocation = FindSpawnLocation();
			SpawnOneBot(CharacterClass, SpawnLocation);
		}
	}
	
	// 设置定时器定期检查并生成AI
	if (SpawnCheckInterval > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(
			SpawnCheckTimerHandle,
			this,
			&UBlotAICreationComponent::CheckAndSpawnBots,
			SpawnCheckInterval,
			true // 重复执行
		);
	}
}

void UBlotAICreationComponent::CheckAndSpawnBots()
{
	// 检查是否需要生成更多AI（可以在此添加逻辑来维持特定数量的AI）
	// 目前只是简单地重新生成一次配置中的AI
	ServerCreateBots();
}
#endif

void UBlotAICreationComponent::OnExperienceLoaded(const UExperienceDefinition* Experience)
{
#if WITH_SERVER_CODE
	ServerCreateBots();
#endif
}
