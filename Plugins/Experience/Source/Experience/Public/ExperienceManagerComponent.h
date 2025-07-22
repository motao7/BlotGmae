// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExperienceDefinition.h"
#include "Components/GameStateComponent.h"
#include "ExperienceManagerComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnExperienceLoaded,const UExperienceDefinition* /* Experience指针 */)

namespace UE::GameFeatures
{
	struct FResult;
}

class UExperienceDefinition;
/**
 *		加载Experience
 *		GameState为客户端和服务器同步的并不代码其身上的组件也同步，需要自己设置网络同步
 */
UCLASS(Blueprintable,Meta=(BlueprintSpawnableComponent))
class EXPERIENCE_API UExperienceManagerComponent : public UGameStateComponent
{
	GENERATED_BODY()
	
public:
	UExperienceManagerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	TObjectPtr<const UExperienceDefinition> GetCurrentExperience() const{return CurrentExperience;}
	bool GetIsExperienceLoadedCompoleted() const { return bExperienceLoadedCompoleted; }

	bool IsExperienceLoaded() const;

	/** TryLoad软引用Experience，获得CDOExperience放入CurrentExperience，便于之后加载CDOExperience中的虚幻指针成员变量 */
	void StartLoadExperience(const TSoftClassPtr<UExperienceDefinition>& ExperienceDef);
	/** 加载Expeirnece虚幻指针成员变量 */
	void LoadExperienceTPtrVariable();
	/** 激活GameFeature */
	void OnExperienceLoadComplete();
	/** 激活GameFeatureAction */
	void OnExperienceFullLoadCompleted(const UE::GameFeatures::FResult& Result, int ReaminLoadingGameFeatureNum);

	//如果ExperienceLoaded直接Broadcats委托，如果没激活等激活后OnExperienceFullLoadCompleted会激活所有的绑定 
	void CallOrReigister_OnExperienceLoaded_HighPriority(FOnExperienceLoaded::FDelegate&& Delegate);
	void CallOrReigister_OnExperienceLoaded(FOnExperienceLoaded::FDelegate&& Delegate);
	/**Initialize BotCreationComponent*/
	void CallOrRegister_OnExperienceLoaded_LowPriority(FOnExperienceLoaded::FDelegate&& Delegate);
	
protected:
	/*客户端执行LoadExperienceTPtrVariable*/
	UFUNCTION()
	void OnRep_CurrentExperience();
	
protected:
	UPROPERTY(ReplicatedUsing=OnRep_CurrentExperience)
	TObjectPtr<const UExperienceDefinition> CurrentExperience;
	
	bool bExperienceLoadedCompoleted=false;

	/**在Experience加载完全后Call */
	FOnExperienceLoaded OnExperienceLoadedDelegate;
	FOnExperienceLoaded OnExperienceLoadedDelegate_HighPriority;
	FOnExperienceLoaded OnExperienceLoadedDelegate_LowPriority;
	
};
