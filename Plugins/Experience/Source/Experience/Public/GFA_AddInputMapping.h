// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GFA_WorldActionBase.h"
#include "GFA_AddInputMapping.generated.h"

struct FComponentRequestHandle;
class UInputMappingContext;
/**
 *		AddInput Mappinng to every local player
 *		RegisterInputMapping is for registerInputMapping to GameUserSetting
 *		While AddToWorld is actully add InputMapping to LocalPlayer
 */
UCLASS(meta = (DisplayName = "Add Input Mapping"))
class EXPERIENCE_API UGFA_AddInputMapping final : public UGFA_WorldActionBase
{
	GENERATED_BODY()

public:
	//~UGameFeatureAction interface
	virtual void OnGameFeatureRegistering() override;
	virtual void OnGameFeatureActivating(FGameFeatureActivatingContext& Context) override;
	virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;
	virtual void OnGameFeatureUnregistering() override;
	//~End of UGameFeatureAction interface

private:
	/** Delegate for when the game instance is changed to register IMC's */
	FDelegateHandle RegisterInputContextMappingsForGameInstanceHandle;

	/** Registers owned Input Mapping Contexts to the Input Registry Subsystem. Also binds onto the start of GameInstances and the adding/removal of Local Players. */
	void RegisterInputMappingContexts();
	
	/** Registers owned Input Mapping Contexts to the Input Registry Subsystem for a specified GameInstance. This also gets called by a GameInstance Start. */
	void RegisterInputContextMappingsForGameInstance(UGameInstance* GameInstance);

	/** Registers owned Input Mapping Contexts to the Input Registry Subsystem for a specified Local Player. This also gets called when a Local Player is added. */
	void RegisterInputMappingContextsForLocalPlayer(ULocalPlayer* LocalPlayer);

	/** Unregisters owned Input Mapping Contexts from the Input Registry Subsystem. Also unbinds from the start of GameInstances and the adding/removal of Local Players. */
	void UnregisterInputMappingContexts();

	/** Unregisters owned Input Mapping Contexts from the Input Registry Subsystem for a specified GameInstance. */
	void UnregisterInputContextMappingsForGameInstance(UGameInstance* GameInstance);

	/** Unregisters owned Input Mapping Contexts from the Input Registry Subsystem for a specified Local Player. This also gets called when a Local Player is removed. */
	void UnregisterInputMappingContextsForLocalPlayer(ULocalPlayer* LocalPlayer);

	//~UGameFeatureAction_WorldActionBase interface
	virtual void AddToWorld(const FWorldContext& WorldContext, const FGameFeatureStateChangeContext& ChangeContext) override;
	//~End of UGameFeatureAction_WorldActionBase interface

	void HandleControllerExtension(AActor* Actor, FName EventName);
	void AddInputMappingForPlayer(UPlayer* Player);
	void RemoveInputMapping(APlayerController* PlayerController);
	
	UPROPERTY(EditAnywhere, Category="Input", meta=(AssetBundles="Client,Server"))
	TSoftObjectPtr<UInputMappingContext> InputMapping;

};
