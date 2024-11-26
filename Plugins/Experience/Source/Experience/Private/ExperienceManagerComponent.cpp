// Fill out your copyright notice in the Description page of Project Settings.


#include "ExperienceManagerComponent.h"

#include "ExperienceActionSet.h"
#include "ExperienceDefination.h"
#include "GameFeaturesSubsystem.h"
#include "GameFeaturesSubsystemSettings.h"
#include "Engine/AssetManager.h"
#include "Net/UnrealNetwork.h"


UExperienceManagerComponent::UExperienceManagerComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SetIsReplicatedByDefault(true);
}

void UExperienceManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, CurrentExperience);
}

void UExperienceManagerComponent::StartLoadExperience(const TSoftClassPtr<UExperienceDefination>& SPExperience)
{
	FPrimaryAssetId ExperienceId=UAssetManager::Get().GetPrimaryAssetIdForPath(SPExperience.ToSoftObjectPath());
	ensureMsgf(ExperienceId.IsValid(),TEXT("Function:StartLoadExperience fail to Get GetPrimaryAssetIdForPath"));
	
	FSoftObjectPath AssetPath = UAssetManager::Get().GetPrimaryAssetPath(ExperienceId);
	//FSoftObjectPath中TryLoad，加载元数据(元数据类似于.h文件，而真正的运行之城类的.cpp没有加载，即成员变量都没有真正加载，
	//需要后续在加载成员变量)
	TSubclassOf<UExperienceDefination> AssetClass = Cast<UClass>(AssetPath.TryLoad());
	//正常来说GetDefault就是获得一个类的CDO，即默认实例
	//但是TSoftObjectPtr、TObjectPtr、TWeakObjectPtr 等指针类型）：这些成员变量通常不会在 CDO 加载时自动加载。它们只是指向其他资源的引用
	//所以还是要再次加载成员变量
	const UExperienceDefination* Experience = GetDefault<UExperienceDefination>(AssetClass);
	check(Experience != nullptr);
	check(CurrentExperience == nullptr);
	CurrentExperience = Experience;
	check(AssetClass);
	
	LoadExperienceTPtrVariable();
}

void UExperienceManagerComponent::LoadExperienceTPtrVariable()
{
	check(CurrentExperience != nullptr);

	//获得要加载的AssetId
	TSet<FPrimaryAssetId> AssetList;
	AssetList.Add(CurrentExperience->GetPrimaryAssetId());
	for(auto& ActionSet:CurrentExperience->ActionSets)
	{
		if(ActionSet!=nullptr)
		{
			AssetList.Add(ActionSet->GetPrimaryAssetId());
		}
	}

	//添加客户端还是服务器加载的捆绑包到绑定AssetList中(我也不知道具体有啥用，性能更高吧，绑定捆绑包后，有些资产客户端不用加载有些服务器不用加载)
	TArray<FName> BundlesToLoad;
	const ENetMode OwnerNetMode = GetOwner()->GetNetMode();
	const bool bLoadClient = GIsEditor || (OwnerNetMode != NM_DedicatedServer);
	const bool bLoadServer = GIsEditor || (OwnerNetMode != NM_Client);
	if (bLoadClient)
	{
		BundlesToLoad.Add(UGameFeaturesSubsystemSettings::LoadStateClient);
	}
	if (bLoadServer)
	{
		BundlesToLoad.Add(UGameFeaturesSubsystemSettings::LoadStateServer);
	}
	TSharedPtr<FStreamableHandle> AssetListHandle = nullptr;
	if (AssetList.Num() > 0)
	{
		//ChangeBundleStateForPrimaryAssets，添加了捆绑包并异步的加载资产
		AssetListHandle = UAssetManager::Get().ChangeBundleStateForPrimaryAssets(AssetList.Array(), BundlesToLoad, {}, false, FStreamableDelegate(), FStreamableManager::AsyncLoadHighPriority);
	}

	//绑定Asset加载完后的回调函数
	FStreamableDelegate OnAssetsLoadedDelegate = FStreamableDelegate::CreateUObject(this, &ThisClass::OnExperienceLoadComplete);
	if (!AssetListHandle.IsValid() || AssetListHandle->HasLoadCompleted())
	{
		// Assets were already loaded, call the delegate now
		FStreamableHandle::ExecuteDelegate(OnAssetsLoadedDelegate);
	}
	else
	{
		AssetListHandle->BindCompleteDelegate(OnAssetsLoadedDelegate);

		AssetListHandle->BindCancelDelegate(FStreamableDelegate::CreateLambda([OnAssetsLoadedDelegate]()
			{
				OnAssetsLoadedDelegate.ExecuteIfBound();
			}));
	}
}

void UExperienceManagerComponent::OnExperienceLoadComplete()
{
	int ReaminLoadingGameFeatureNum=CurrentExperience->GameFeatureToEnable.Num();
	for(auto& GameFeatureName:CurrentExperience->GameFeatureToEnable)
	{
		--ReaminLoadingGameFeatureNum;
		FString PluginURL;
		UGameFeaturesSubsystem::Get().GetPluginURLByName(GameFeatureName,PluginURL);
		UGameFeaturesSubsystem::Get().LoadAndActivateGameFeaturePlugin(PluginURL,FGameFeaturePluginLoadComplete::CreateUObject(this, &ThisClass::OnExperienceFullLoadCompleted,ReaminLoadingGameFeatureNum));
	}
	
}

void UExperienceManagerComponent::OnExperienceFullLoadCompleted(const UE::GameFeatures::FResult& Result,int ReaminLoadingGameFeatureNum)
{
	if(ReaminLoadingGameFeatureNum!=0) return;

	//Action没有设置对应的世界Context使用lamada表达式中的【】来让Action作用于正确的世界
	FGameFeatureActivatingContext Context;
	if (const FWorldContext* ExistingWorldContext = GEngine->GetWorldContextFromWorld(GetWorld()))
	{
		Context.SetRequiredWorldContextHandle(ExistingWorldContext->ContextHandle);
	}

	auto ActivateListOfActions = [&Context](const TArray<UGameFeatureAction*>& ActionList)
	{
		for (UGameFeatureAction* Action : ActionList)
		{
			if (Action != nullptr)
			{
				//Action没有设置对应的世界Context使用lamada表达式中的【】来让Action作用于正确的世界
				Action->OnGameFeatureRegistering();
				Action->OnGameFeatureLoading();
				Action->OnGameFeatureActivating(Context);
			}
		}
	};

	ActivateListOfActions(CurrentExperience->Actions);
	for (const TObjectPtr<UExperienceActionSet>& ActionSet : CurrentExperience->ActionSets)
	{
		if (ActionSet != nullptr)
		{
			ActivateListOfActions(ActionSet->Actions);
		}
	}

	bExperienceLoadedCompoleted=true;
	
	OnExperienceLoadedDelegate.Broadcast(CurrentExperience);
	OnExperienceLoadedDelegate.Clear();
}

void UExperienceManagerComponent::CallOrReigister_OnExperienceLoaded(FOnExperienceLoaded::FDelegate&& Delegate)
{
	if(GetIsExperienceLoadedCompoleted())
	{
		Delegate.Execute(CurrentExperience);
	}
	else
	{
		//MoveTemp类似于Std::move:移动右值 or 将左值变为右值
		OnExperienceLoadedDelegate.Add(MoveTemp(Delegate));
	}
}

void UExperienceManagerComponent::OnRep_CurrentExperience()
{
	LoadExperienceTPtrVariable();
}

