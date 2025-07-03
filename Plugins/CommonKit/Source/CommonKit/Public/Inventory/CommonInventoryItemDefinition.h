// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CommonInventoryItemDefinition.generated.h"

class UCommonInventoryItemFragment;

UCLASS(Blueprintable, Const, Abstract)
class COMMONKIT_API UCommonInventoryItemDefinition : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="Inventory",meta=(DeterminesOutputType=FragmentClass))
	UCommonInventoryItemFragment* FindFragmentByClass(TSubclassOf<UCommonInventoryItemFragment> FragmentClass) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Display)
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Display, Instanced)
	TArray<TObjectPtr<UCommonInventoryItemFragment>> Fragments;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Display)
	bool IsDefaultItem=false;
};
