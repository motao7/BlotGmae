// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonExtensionSubsystem.h"
#include "Components/DynamicEntryBoxBase.h"
#include "CommonExtensionPointWidget.generated.h"

class UCommonLocalPlayer;
enum class EUIExtensionPointMatch : uint8;
struct FUIExtensionPointHandle;
struct FUIExtensionHandle;

/**
 *		A slot that defines a location in a layout, where content can be added later
 */
UCLASS()
class COMMONGAME_API UCommonExtensionPointWidget : public UDynamicEntryBoxBase
{
	GENERATED_BODY()

public:
	//~UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	//~End of UWidget interface

private:
	void RegisterExtensionPoint();
	void RegisterExtensionPointForPlayerState(UCommonLocalPlayer* LocalPlayer, APlayerState* PlayerState);
	/**
	 *		CallBack function,call when ExtesnionSystem finish extension registetation.Actually Create/Remove Widget.
	 *		This function will work only(work mean success to insert widget to this slot)
	 *		ExtensionSystem exist registed Extension that match to this ExtensionPoint.
	 *		FUIExtensionPointRequest& Request contain Widget that want to insert 
	 */
	void OnAddOrRemoveExtension(EUIExtensionAction Action, const FUIExtensionPointRequest& Request);

protected:
	/** The tag that defines this extension point */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Extension")
	FGameplayTag ExtensionPointTag;

	/** How exactly does the extension need to match the extension point tag. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Extension")
	EUIExtensionPointMatch ExtensionPointTagMatch = EUIExtensionPointMatch::ExactMatch;

	//TODO:将AllowDataClasses移除，感觉不是很有必要存在
	/**Decide what class Widget can insert in this ExtensionPointWidget*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Extension")
	TArray<TObjectPtr<UClass>> AllowDataClasses;
	
	TArray<FUIExtensionPointHandle> ExtensionPointHandles;

	UPROPERTY(Transient)
	TMap<FUIExtensionHandle, TObjectPtr<UUserWidget>> ExtensionMapping;	
	
	
};
