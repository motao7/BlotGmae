// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "TagInputConfig.generated.h"

class UInputAction;
/**
 *		Struct used to map a input action to a gameplay input tag.
 */
USTRUCT(BlueprintType)
struct FTagInputAction
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UInputAction> InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

/**
 *		Non-mutable data asset that contains input configuration properties.
 *		InputConfig only connect IA and Tag,only when ASC has corresponding then can actully active
 */
UCLASS(BlueprintType, Const)
class TAGINPUT_API UTagInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	UTagInputConfig(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(Category = "TagInput")
	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

	UFUNCTION(Category = "TagInput")
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;
	
	// List of input actions used by the owner.  These input actions are mapped to a gameplay tag and must be manually bound.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FTagInputAction> NativeInputActions;

	// List of input actions used by the owner.  These input actions are mapped to a gameplay tag and are automatically bound to abilities with matching input tags.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FTagInputAction> AbilityInputActions;
};
