// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExperienceDefination.h"
#include "Components/GameStateComponent.h"
#include "ExperienceManagerComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnExperienceLoaded,const UExperienceDefination* /* Experience指针 */)

namespace UE::GameFeatures
{
	struct FResult;
}

class UExperienceDefination;
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

	//~Helper Function
	TObjectPtr<const UExperienceDefination> GetCurrentExperience() const{return CurrentExperience;}
	bool GetIsExperienceLoadedCompoleted() const { return bExperienceLoadedCompoleted; }
	//~Helper Function End
	
	//~加载Experience主流程
	/** TryLoad软引用Experience，获得CDOExperience放入CurrentExperience，便于之后加载CDOExperience中的虚幻指针成员变量 */
	void StartLoadExperience(const TSoftClassPtr<UExperienceDefination>& ExperienceDef);
	/** 加载Expeirnece虚幻指针成员变量 */
	void LoadExperienceTPtrVariable();
	/** 激活GameFeature */
	void OnExperienceLoadComplete();
	/** 激活GameFeatureAction */
	void OnExperienceFullLoadCompleted(const UE::GameFeatures::FResult& Result, int ReaminLoadingGameFeatureNum);
	//~加载Experience主流程

	void CallOrReigister_OnExperienceLoaded_HighPriority(FOnExperienceLoaded::FDelegate&& Delegate);
	/** 注册或执行委托，使用右值引用防止委托绑定回调函数采用Lamda这种包含闭包数据的函数，减少拷贝消耗 */
	void CallOrReigister_OnExperienceLoaded(FOnExperienceLoaded::FDelegate&& Delegate);
	
protected:
	/*客户端执行LoadExperienceTPtrVariable*/
	UFUNCTION()
	void OnRep_CurrentExperience();
	
protected:
	UPROPERTY(ReplicatedUsing=OnRep_CurrentExperience)
	TObjectPtr<const UExperienceDefination> CurrentExperience;
	
	bool bExperienceLoadedCompoleted=false;

	/**在Experience加载完全后Call */
	FOnExperienceLoaded OnExperienceLoadedDelegate;
	FOnExperienceLoaded OnExperienceLoadedDelegate_HighPriority;
};
