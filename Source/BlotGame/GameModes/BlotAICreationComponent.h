// BlotAICreationComponent.h
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameStateComponent.h"
#include "BlotAICreationComponent.generated.h"

class AAIController;
class UExperienceDefinition;
class APawn;

/**
 * AI Creation Component that spawns bots in a radius around players
 */
UCLASS()
class BLOTGAME_API UBlotAICreationComponent : public UGameStateComponent
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:
	// 定义每个角色类型的生成配置
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Gameplay)
	TMap<TSubclassOf<ACharacter>, int32> CharacterBotConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Gameplay)
	TSubclassOf<AAIController> BotControllerClass;

	// 最大生成半径
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Gameplay, meta=(ClampMin="0.0"))
	float MaxSpawnRadius = 3000.0f;

	// 最小生成半径（避免在玩家附近生成）
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Gameplay, meta=(ClampMin="0.0"))
	float MinSpawnRadius = 500.0f;

	// 生成检查间隔（秒）
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Gameplay, meta=(ClampMin="0.1"))
	float SpawnCheckInterval = 5.0f;

	UPROPERTY(Transient)
	TArray<TObjectPtr<AAIController>> SpawnedBotList;

	/** Creates a single bot with specified character class at a location */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Gameplay)
	virtual AAIController* SpawnOneBot(TSubclassOf<ACharacter> CharacterClass, const FVector& Location);

	/** Spawns bots according to CharacterBotConfig around players */
	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly, Category=Gameplay)
	void ServerCreateBots();

	/** Find a valid spawn location around players */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Gameplay)
	FVector FindSpawnLocation() const;

private:
	void OnExperienceLoaded(const UExperienceDefinition* Experience);
	
	FTimerHandle SpawnCheckTimerHandle;
	
	UFUNCTION()
	void CheckAndSpawnBots();
};
