#pragma once

#include "TeamDisplayAsset.generated.h"

UCLASS(BlueprintType)
class UTeamDisplayAsset:public UDataAsset
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable,Category="Team|TeamDisplayAsset")
	void ApplyToActor(AActor* Actor);
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="TeamColor")
	TMap<FName, FLinearColor> ColorParameters;

};
