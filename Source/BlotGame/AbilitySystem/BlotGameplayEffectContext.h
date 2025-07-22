// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Templates/SharedPointer.h"
#include "BlotGameplayEffectContext.generated.h"

/**
 * 
 */
USTRUCT()
struct BLOTGAME_API FBlotGameplayEffectContext:public FGameplayEffectContext
{
	GENERATED_BODY()
	
	FBlotGameplayEffectContext()
		: FGameplayEffectContext()
	{
	}

	FBlotGameplayEffectContext(AActor* InInstigator, AActor* InEffectCauser)
		: FGameplayEffectContext(InInstigator, InEffectCauser)
	{
	}

	/** Returns the wrapped FBlotGameplayEffectContext from the handle, or nullptr if it doesn't exist or is the wrong type */
	static  FBlotGameplayEffectContext* ExtractEffectContext(struct FGameplayEffectContextHandle Handle);

	/** Overridden to serialize new fields */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FBlotGameplayEffectContext::StaticStruct();
	}
	
	void AddHitResults(const FHitResult& Hit) { HitResults.Add(MakeShared<FHitResult>(Hit)); }
	const TArray<TSharedPtr<FHitResult>>& GetHitResults() const { return HitResults; }

	void SetCartridgeID(int32 InCartridgeID){CartridgeID=InCartridgeID;}
	
protected:
	UPROPERTY()
	int32 CartridgeID = -1;
	
	TArray<TSharedPtr<FHitResult>> HitResults;
};

template<>
struct TStructOpsTypeTraits<FBlotGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FBlotGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};
