// Fill out your copyright notice in the Description page of Project Settings.


#include "ExperienceManagerComponent.h"

#include "ExperienceActionSet.h"
#include "ExperienceDefinition.h"
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

bool UExperienceManagerComponent::IsExperienceLoaded() const
{
	return bExperienceLoadedCompoleted;
}

void UExperienceManagerComponent::StartLoadExperience(const TSoftClassPtr<UExperienceDefinition>& ExperienceDef)
{
	// 获取主资产ID
	FPrimaryAssetId ExperienceId = UAssetManager::Get().GetPrimaryAssetIdForPath(ExperienceDef.ToSoftObjectPath());
	ensureMsgf(ExperienceId.IsValid(), TEXT("Function: StartLoadExperience failed to GetPrimaryAssetIdForPath"));

	// 获取主资产路径
	FSoftObjectPath AssetPath = UAssetManager::Get().GetPrimaryAssetPath(ExperienceId);
    
	// 尝试加载资产类
	TSubclassOf<UExperienceDefinition> AssetClass = Cast<UClass>(AssetPath.TryLoad());
	if (!AssetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load asset class from path: %s"), *AssetPath.ToString());
		return;
	}

	// 获取资产的默认实例（CDO）---这会加载类的基本信息，但不会加载类的成员变量,如果你有类似 TSoftObjectPtr 类型的成员变量，它们可能需要进一步加载
	const UExperienceDefinition* Experience = GetDefault<UExperienceDefinition>(AssetClass);
	if (!Experience)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get default experience definition from asset class."));
		return;
	}

	// 确保 CurrentExperience 是空的
	check(CurrentExperience == nullptr);
	CurrentExperience = Experience;

	// 加载Expeirnece的其他成员变量（例如软对象指针等）
	LoadExperienceTPtrVariable();
}

void UExperienceManagerComponent::LoadExperienceTPtrVariable()
{
	check(CurrentExperience != nullptr);

	//获得要加载的AssetId/这些PrimaryAsset要被AssetManager扫描
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
		//将所有软引用的资源（包括你配置在 Experience、ActionSet、GameFeatureAction 中的 WidgetClass、LayoutClass）加入加载列表
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

	OnExperienceLoadedDelegate_HighPriority.Broadcast(CurrentExperience);
	OnExperienceLoadedDelegate_HighPriority.Clear();
	
	OnExperienceLoadedDelegate.Broadcast(CurrentExperience);
	OnExperienceLoadedDelegate.Clear();

	OnExperienceLoadedDelegate_LowPriority.Broadcast(CurrentExperience);
	OnExperienceLoadedDelegate_LowPriority.Clear();
}

void UExperienceManagerComponent::CallOrReigister_OnExperienceLoaded_HighPriority(FOnExperienceLoaded::FDelegate&& Delegate)
{
	if(GetIsExperienceLoadedCompoleted())
	{
		Delegate.Execute(CurrentExperience);
	}
	else
	{
		//MoveTemp类似于Std::move:移动右值 or 将左值变为右值
		OnExperienceLoadedDelegate_HighPriority.Add(MoveTemp(Delegate));
	}
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

void UExperienceManagerComponent::CallOrRegister_OnExperienceLoaded_LowPriority(FOnExperienceLoaded::FDelegate&& Delegate)
{
	if(GetIsExperienceLoadedCompoleted())
	{
		Delegate.Execute(CurrentExperience);
	}
	else
	{
		//MoveTemp类似于Std::move:移动右值 or 将左值变为右值
		OnExperienceLoadedDelegate_LowPriority.Add(MoveTemp(Delegate));
	}
}

void UExperienceManagerComponent::OnRep_CurrentExperience()
{
	LoadExperienceTPtrVariable();
}

