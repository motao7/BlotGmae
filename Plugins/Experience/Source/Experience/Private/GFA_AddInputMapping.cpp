// Fill out your copyright notice in the Description page of Project Settings.


#include "GFA_AddInputMapping.h"

#include "EnhancedInputSubsystems.h"
#include "Experience.h"
#include "GameFeaturesSubsystem.h"
#include "InputMappingContext.h"
#include "Components/GameFrameworkComponentManager.h"
#include "Engine/AssetManager.h"
#include "UserSettings/EnhancedInputUserSettings.h"

void UGFA_AddInputMapping::OnGameFeatureRegistering()
{
	Super::OnGameFeatureRegistering();

	// RegisterInputMappingContexts();
}

void UGFA_AddInputMapping::OnGameFeatureActivating(FGameFeatureActivatingContext& Context)
{
	Super::OnGameFeatureActivating(Context);
}

void UGFA_AddInputMapping::OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context)
{
	Super::OnGameFeatureDeactivating(Context);
}

void UGFA_AddInputMapping::OnGameFeatureUnregistering()
{
	Super::OnGameFeatureUnregistering();

	// UnregisterInputMappingContexts();
}

void UGFA_AddInputMapping::RegisterInputMappingContexts()
{
	//For first Join local player
	RegisterInputContextMappingsForGameInstanceHandle = FWorldDelegates::OnStartGameInstance.AddUObject(this, &UGFA_AddInputMapping::RegisterInputContextMappingsForGameInstance);

	//For those who join later
	const TIndirectArray<FWorldContext>& WorldContexts = GEngine->GetWorldContexts();
	for (TIndirectArray<FWorldContext>::TConstIterator WorldContextIterator = WorldContexts.CreateConstIterator(); WorldContextIterator; ++WorldContextIterator)
	{
		RegisterInputContextMappingsForGameInstance(WorldContextIterator->OwningGameInstance);
	}
}

void UGFA_AddInputMapping::RegisterInputContextMappingsForGameInstance(UGameInstance* GameInstance)
{
	if (GameInstance != nullptr && !GameInstance->OnLocalPlayerAddedEvent.IsBoundToObject(this))
	{
		GameInstance->OnLocalPlayerAddedEvent.AddUObject(this, &UGFA_AddInputMapping::RegisterInputMappingContextsForLocalPlayer);
		GameInstance->OnLocalPlayerRemovedEvent.AddUObject(this, &UGFA_AddInputMapping::UnregisterInputMappingContextsForLocalPlayer);
		
		for (TArray<ULocalPlayer*>::TConstIterator LocalPlayerIterator = GameInstance->GetLocalPlayerIterator(); LocalPlayerIterator; ++LocalPlayerIterator)
		{
			RegisterInputMappingContextsForLocalPlayer(*LocalPlayerIterator);
		}
	}
}

void UGFA_AddInputMapping::RegisterInputMappingContextsForLocalPlayer(ULocalPlayer* LocalPlayer)
{
	if (ensure(LocalPlayer))
	{
		UAssetManager& AssetManager = UAssetManager::Get();
		
		if (UEnhancedInputLocalPlayerSubsystem* EISubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			if (UEnhancedInputUserSettings* Settings = EISubsystem->GetUserSettings())
			{
				FStreamableManager& Streamable = UAssetManager::Get().GetStreamableManager();
				Streamable.RequestAsyncLoad(InputMapping.ToSoftObjectPath(),FStreamableDelegate::CreateLambda([this, Settings]()
					{
						// 加载完成后，获取资源并注册
						UInputMappingContext* IMC = InputMapping.Get();
						if (IMC)
						{
							Settings->RegisterInputMappingContext(IMC);
						}
					})
				);
			}
		}
	}
}

void UGFA_AddInputMapping::UnregisterInputMappingContexts()
{
	FWorldDelegates::OnStartGameInstance.Remove(RegisterInputContextMappingsForGameInstanceHandle);
	RegisterInputContextMappingsForGameInstanceHandle.Reset();

	const TIndirectArray<FWorldContext>& WorldContexts = GEngine->GetWorldContexts();
	for (TIndirectArray<FWorldContext>::TConstIterator WorldContextIterator = WorldContexts.CreateConstIterator(); WorldContextIterator; ++WorldContextIterator)
	{
		UnregisterInputContextMappingsForGameInstance(WorldContextIterator->OwningGameInstance);
	}
}

void UGFA_AddInputMapping::UnregisterInputContextMappingsForGameInstance(UGameInstance* GameInstance)
{
	if (GameInstance != nullptr)
	{
		GameInstance->OnLocalPlayerAddedEvent.RemoveAll(this);
		GameInstance->OnLocalPlayerRemovedEvent.RemoveAll(this);

		for (TArray<ULocalPlayer*>::TConstIterator LocalPlayerIterator = GameInstance->GetLocalPlayerIterator(); LocalPlayerIterator; ++LocalPlayerIterator)
		{
			UnregisterInputMappingContextsForLocalPlayer(*LocalPlayerIterator);
		}
	}
}

void UGFA_AddInputMapping::UnregisterInputMappingContextsForLocalPlayer(ULocalPlayer* LocalPlayer)
{
	if (ensure(LocalPlayer))
	{
		if (UEnhancedInputLocalPlayerSubsystem* EISubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			if (UEnhancedInputUserSettings* Settings = EISubsystem->GetUserSettings())
			{
				// Register this IMC with the settings!
				if (UInputMappingContext* IMC = InputMapping.Get())
				{
					Settings->UnregisterInputMappingContext(IMC);
				}
			}
		}
	}
}

void UGFA_AddInputMapping::AddToWorld(const FWorldContext& WorldContext, const FGameFeatureStateChangeContext& ChangeContext)
{
	UWorld* World = WorldContext.World();
	UGameInstance* GameInstance = WorldContext.OwningGameInstance;

	if ((GameInstance != nullptr) && (World != nullptr) && World->IsGameWorld())
	{
		if (UGameFrameworkComponentManager* ComponentManager = UGameInstance::GetSubsystem<UGameFrameworkComponentManager>(GameInstance))
		{
			//创建一个委托（delegate），当某个 APlayerController 被扩展时，调用 HandleControllerExtension 方法
			UGameFrameworkComponentManager::FExtensionHandlerDelegate AddAbilitiesDelegate =
				UGameFrameworkComponentManager::FExtensionHandlerDelegate::CreateUObject(this, &ThisClass::HandleControllerExtension);
			//在 ComponentManager 中注册这个扩展处理器。关联的类型是 APlayerController，表示将来每次这个类的对象创建时，都会触发上面的委托。
			TSharedPtr<FComponentRequestHandle> ExtensionRequestHandle =
				ComponentManager->AddExtensionHandler(APlayerController::StaticClass(), AddAbilitiesDelegate);
		}
	}
}

void UGFA_AddInputMapping::HandleControllerExtension(AActor* Actor, FName EventName)
{
	APlayerController* AsController = CastChecked<APlayerController>(Actor);

	// TODO Why does this code mix and match controllers and local players? ControllersAddedTo is never modified
	if ((EventName == UGameFrameworkComponentManager::NAME_ExtensionRemoved) || (EventName == UGameFrameworkComponentManager::NAME_ReceiverRemoved))
	{
		RemoveInputMapping(AsController);
	}
	else if ((EventName == UGameFrameworkComponentManager::NAME_ExtensionAdded))
	{
		AddInputMappingForPlayer(AsController->GetLocalPlayer());
	}
}


void UGFA_AddInputMapping::AddInputMappingForPlayer(UPlayer* Player)
{
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (const UInputMappingContext* IMC = InputMapping.Get())
			{
				InputSystem->AddMappingContext(IMC, 0);
			}
		}
		else
		{
			UE_LOG(LogExperience, Error, TEXT("Failed to find `UEnhancedInputLocalPlayerSubsystem` for local player. Input mappings will not be added. Make sure you're set to use the EnhancedInput system via config file."));
		}
	}
}

void UGFA_AddInputMapping::RemoveInputMapping(APlayerController* PlayerController)
{
	if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (const UInputMappingContext* IMC = InputMapping.Get())
			{
				InputSystem->RemoveMappingContext(IMC);
			}
		}
	}
}
