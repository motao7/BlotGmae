// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/WorldSubsystem.h"
#include "CommonExtensionSubsystem.generated.h"

struct FUIExtensionPointRequest;
class UCommonExtensionSubsystem;
// Match rule for extension points
UENUM(BlueprintType)
enum class EUIExtensionPointMatch : uint8
{
	ExactMatch,
	PartialMatch
};

// Match rule for extension points
UENUM(BlueprintType)
enum class EUIExtensionAction : uint8
{
	Added,
	Removed
};

DECLARE_DELEGATE_TwoParams(FExtendExtensionPointDelegate, EUIExtensionAction Action, const FUIExtensionPointRequest& Request);

/*
 *		A struct that is convienet to ExtensionSubsytem to maintain Widget(that want to insert in ExtensionPoint)
 */
struct FUIExtension : TSharedFromThis<FUIExtension>
{
public:
	FGameplayTag ExtensionPointTag;
	int32 Priority = INDEX_NONE;
	TWeakObjectPtr<UObject> ContextObject;
	//Actually Widget pointer
	TObjectPtr<UObject> Data = nullptr;
};

/**
 *		A struct that is convienet to ExtensionSubsytem to maintain ExtensionPointWidget
 */
struct FUIExtensionPoint : TSharedFromThis<FUIExtensionPoint>
{
public:
	FGameplayTag ExtensionPointTag;
	TWeakObjectPtr<UObject> ContextObject;
	EUIExtensionPointMatch ExtensionPointTagMatchType = EUIExtensionPointMatch::ExactMatch;
	/**Decide what class Extension can insert in*/
	TArray<TObjectPtr<UClass>> AllowedDataClasses;
	/**Bind function now only is UUIExtensionPointWidget::OnAddOrRemoveExtension*/
	FExtendExtensionPointDelegate Callback;

	bool DoesExtensionPassContract(const FUIExtension* Extension) const;
};

USTRUCT(BlueprintType)
struct COMMONGAME_API FUIExtensionPointHandle
{
	GENERATED_BODY()

public:
	FUIExtensionPointHandle() {}

	void Unregister();

	bool IsValid() const { return DataPtr.IsValid(); }

	bool operator==(const FUIExtensionPointHandle& Other) const { return DataPtr == Other.DataPtr; }
	bool operator!=(const FUIExtensionPointHandle& Other) const { return !operator==(Other); }

	friend uint32 GetTypeHash(const FUIExtensionPointHandle& Handle)
	{
		return PointerHash(Handle.DataPtr.Get());
	}

private:
	TWeakObjectPtr<UCommonExtensionSubsystem> ExtensionSource;

	TSharedPtr<FUIExtensionPoint> DataPtr;
	
	friend UCommonExtensionSubsystem;

	FUIExtensionPointHandle(UCommonExtensionSubsystem* InExtensionSource, const TSharedPtr<FUIExtensionPoint>& InDataPtr) : ExtensionSource(InExtensionSource), DataPtr(InDataPtr) {}
};


USTRUCT(BlueprintType)
struct COMMONGAME_API FUIExtensionHandle
{
	GENERATED_BODY()

public:
	FUIExtensionHandle() {}

	void Unregister();

	bool IsValid() const { return DataPtr.IsValid(); }

	bool operator==(const FUIExtensionHandle& Other) const { return DataPtr == Other.DataPtr; }
	bool operator!=(const FUIExtensionHandle& Other) const { return !operator==(Other); }

	friend FORCEINLINE uint32 GetTypeHash(FUIExtensionHandle Handle)
	{
		return PointerHash(Handle.DataPtr.Get());
	}

private:
	TWeakObjectPtr<UCommonExtensionSubsystem> ExtensionSource;
	
	TSharedPtr<FUIExtension> DataPtr;
	
	friend UCommonExtensionSubsystem;

	FUIExtensionHandle(UCommonExtensionSubsystem* InExtensionSource, const TSharedPtr<FUIExtension>& InDataPtr) : ExtensionSource(InExtensionSource), DataPtr(InDataPtr) {}
};

/**
 *		Use for CallBackFunction about ExtensionPoint
 *		Warpped information that want to broadcast
 */
USTRUCT(BlueprintType)
struct FUIExtensionPointRequest
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FUIExtensionHandle ExtensionHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag ExtensionPointTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Priority = INDEX_NONE;

	//Fill in Actually Widget pointer
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UObject> Data = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UObject> ContextObject = nullptr;
};

/**
 *		Register FUIExtension/FUIExtensionPoint then use
 *		ExtensionPointMap and ExtensionMap to perserve the mapping relationship between Tag and FUIExtension/FUIExtensionPoint
 */
UCLASS()
class COMMONGAME_API UCommonExtensionSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	FUIExtensionPointHandle RegisterExtensionPoint(const FGameplayTag& ExtensionPointTag, EUIExtensionPointMatch ExtensionPointTagMatchType, const TArray<UClass*>& AllowedDataClasses, FExtendExtensionPointDelegate ExtensionCallback);
	FUIExtensionPointHandle RegisterExtensionPointForContext(const FGameplayTag& ExtensionPointTag, UObject* ContextObject, EUIExtensionPointMatch ExtensionPointTagMatchType, const TArray<UClass*>& AllowedDataClasses, FExtendExtensionPointDelegate ExtensionCallback);

	FUIExtensionHandle RegisterExtensionAsWidget(const FGameplayTag& ExtensionPointTag, TSubclassOf<UUserWidget> WidgetClass, int32 Priority);
	FUIExtensionHandle RegisterExtensionAsWidgetForContext(const FGameplayTag& ExtensionPointTag, UObject* ContextObject, TSubclassOf<UUserWidget> WidgetClass, int32 Priority);
	FUIExtensionHandle RegisterExtensionAsData(const FGameplayTag& ExtensionPointTag, UObject* ContextObject, UObject* Data, int32 Priority);

protected:
	/**When a extension point is registered, the system will search for all the extensions(Registed) that match it, and notify extensions to join the extensionPoint through callbacks. */
	void NotifyExtensionPointOfExtensions(TSharedPtr<FUIExtensionPoint>& ExtensionPoint);
	/**When a extension is registered, the system will search for all the extension points(Registed) that match it, and notify extension to join the extensionPoints through callbacks. */
	void NotifyExtensionPointsOfExtension(EUIExtensionAction Action, TSharedPtr<FUIExtension>& Extension);

	FUIExtensionPointRequest CreateExtensionRequest(const TSharedPtr<FUIExtension>& Extension);
private:
	typedef TArray<TSharedPtr<FUIExtensionPoint>> FExtensionPointList;
	TMap<FGameplayTag, FExtensionPointList> ExtensionPointMap;

	typedef TArray<TSharedPtr<FUIExtension>> FExtensionList;
	TMap<FGameplayTag, FExtensionList> ExtensionMap;
	
};
