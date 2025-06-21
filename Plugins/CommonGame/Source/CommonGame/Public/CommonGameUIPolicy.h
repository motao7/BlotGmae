// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CommonGameUIPolicy.generated.h"

class UCommonLocalPlayer;
class UCommonPrimaryGameLayout;

USTRUCT()
struct FRootViewportLayoutInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(Transient)
	TObjectPtr<ULocalPlayer> LocalPlayer = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UCommonPrimaryGameLayout> RootLayout = nullptr;

	UPROPERTY(Transient)
	bool bAddedToViewport = false;

	FRootViewportLayoutInfo() {}
	FRootViewportLayoutInfo(ULocalPlayer* InLocalPlayer, UCommonPrimaryGameLayout* InRootLayout, bool bIsInViewport)
		: LocalPlayer(InLocalPlayer)
		, RootLayout(InRootLayout)
		, bAddedToViewport(bIsInViewport)
	{}

	bool operator==(const ULocalPlayer* OtherLocalPlayer) const { return LocalPlayer == OtherLocalPlayer; }
};

/**
 *		Maintain PrimaryGameLayout by use Add/Remove/Create Layout
 */
UCLASS(Abstract, Blueprintable, Within = CommonGameUIManagerSubsystem)
class COMMONGAME_API UCommonGameUIPolicy : public UObject
{
	GENERATED_BODY()
public:
	UCommonPrimaryGameLayout* GetRootLayout(const UCommonLocalPlayer* LocalPlayer) const;

protected:
	void AddLayoutToViewport(UCommonLocalPlayer* LocalPlayer, UCommonPrimaryGameLayout* Layout);
	void CreateLayoutWidget(UCommonLocalPlayer* LocalPlayer);
	
private:
	friend class UCommonGameUIManagerSubsystem;

	void NotifyPlayerAdded(UCommonLocalPlayer* LocalPlayer);
	
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UCommonPrimaryGameLayout> DefaultLayoutClass;

	/** Maintain Layout that already added in policy*/
	UPROPERTY(Transient)
	TArray<FRootViewportLayoutInfo> RootViewportLayouts;

};
