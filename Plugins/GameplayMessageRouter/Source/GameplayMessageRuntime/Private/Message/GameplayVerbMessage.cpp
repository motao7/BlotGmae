// Fill out your copyright notice in the Description page of Project Settings.


#include "Message/GameplayVerbMessage.h"

FString FGameplayVerbMessage::ToString() const
{
	FString HumanReadableMessage;
	FGameplayVerbMessage::StaticStruct()->ExportText(/*out*/ HumanReadableMessage, this, /*Defaults=*/ nullptr, /*OwnerObject=*/ nullptr, PPF_None, /*ExportRootScope=*/ nullptr);
	return HumanReadableMessage;
}
