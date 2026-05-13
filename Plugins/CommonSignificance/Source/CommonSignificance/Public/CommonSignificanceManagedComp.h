// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonSigManagedObjectInterface.h"
#include "SignificanceManager.h"
#include "Components/ActorComponent.h"
#include "CommonSignificanceManagedComp.generated.h"


struct FSignificanceTickIntervalPolicy;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMMONSIGNIFICANCE_API UCommonSignificanceManagedComp : public UActorComponent,public ICommonSigManagedObjectInterface
{
	GENERATED_BODY()

public:	
	UCommonSignificanceManagedComp() {};

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = Significance)
	FName SignificanceTag = TEXT("DefaultComponent");

	UPROPERTY(EditDefaultsOnly, Category = Significance)
	ESignificanceByType SignificanceByType = ESignificanceByType::Distance;

	UPROPERTY(EditDefaultsOnly, Category = Significance)
	EPostSignificanceType PostSignificanceType = EPostSignificanceType::Sequential;

public:
	virtual float SignificanceFunction(
		USignificanceManager::FManagedObjectInfo* ObjectInfo, const FTransform& Viewpoint) override;
	virtual void PostSignificanceFunction(
		USignificanceManager::FManagedObjectInfo* ObjectInfo,
		float OldSignificance, float Significance, bool bFinal) override;

	UFUNCTION(BlueprintNativeEvent, Category = Significance)
	void OnSignificanceChanged(float OldSignificance, float Significance);

protected:
	virtual float GetOwnerDistance(const FTransform& Viewpoint);
	virtual float GetOwnerDistance2D(const FTransform& Viewpoint);
	virtual float GetOwnerScreenSize(const FTransform& Viewpoint);
	
	const FSignificanceTickIntervalPolicy* SignificancePolicy = nullptr;
};
