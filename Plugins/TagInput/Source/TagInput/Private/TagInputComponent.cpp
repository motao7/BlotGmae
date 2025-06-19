// Fill out your copyright notice in the Description page of Project Settings.


#include "TagInputComponent.h"

#include "EnhancedInputSubsystems.h"
#include "UserSettings/EnhancedInputUserSettings.h"

void UTagInputComponent::RemapJumpToKey(const UTagInputConfig* InputConfig, const FGameplayTag& InputTag, const FKey& NewKey)
{
	// check(InputConfig);
	// if (const UInputAction* IA = InputConfig->FindNativeInputActionForTag(InputTag))
	// {
	// 	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	// 	{
	// 		UEnhancedInputUserSettings* Settings = Subsystem->GetUserSettings();
	// 		
	// 		// Settings->MapPlayerKey()
	// 		Settings->ApplySettings();
	// 		Settings->SaveSettings();
	// 	}
	// }
}
