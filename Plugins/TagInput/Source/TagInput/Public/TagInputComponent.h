// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "TagInputConfig.h"
#include "TagInputComponent.generated.h"

struct FTagInputAction;
class UTagInputConfig;
struct FGameplayTag;

/**
 *		Connect Action to acutually Event/Ability
 */
UCLASS()
class TAGINPUT_API UTagInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	void RemapJumpToKey(const UTagInputConfig* InputConfig, const FGameplayTag& InputTag,const FKey& NewKey);

	template<class UserClass, typename FuncType>
	void BindNativeAction(const UTagInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func);

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions(const UTagInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc);
};

template<class UserClass, typename FuncType>
void UTagInputComponent::BindNativeAction(const UTagInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
{
	check(InputConfig);
	if (const UInputAction* IA = InputConfig->FindNativeInputActionForTag(InputTag))
	{
		BindAction(IA, TriggerEvent, Object, Func);
	}
}

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void UTagInputComponent::BindAbilityActions(const UTagInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc)
{
	check(InputConfig);

	for (const FTagInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, PressedFunc, Action.InputTag);
			}

			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}
		}
	}
}

