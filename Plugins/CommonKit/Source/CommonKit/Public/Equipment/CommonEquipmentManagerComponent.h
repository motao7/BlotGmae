// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ExperienceAbilitySet.h"
#include "Components/PawnComponent.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "CommonEquipmentManagerComponent.generated.h"

struct FExperienceAbilitySet_GrantedHandles;
struct FCommonEquipmentList;
class UCommonEquipmentManagerComponent;
class UCommonEquipmentDefinition;
class UCommonEquipmentInstance;

/** A single piece of applied equipment */
USTRUCT(BlueprintType)
struct FCommonAppliedEquipmentEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()
	
public:
	FCommonAppliedEquipmentEntry(){}

private:
	friend FCommonEquipmentList;
	friend UCommonEquipmentManagerComponent;

	// The equipment class that got equipped
	UPROPERTY()
	TSubclassOf<UCommonEquipmentDefinition> EquipmentDefinition;

	UPROPERTY()
	TObjectPtr<UCommonEquipmentInstance> Instance = nullptr;

	// Authority-only list of granted handles
	UPROPERTY(NotReplicated)
	FExperienceAbilitySet_GrantedHandles GrantedHandles;
};

/** List of applied equipment */
USTRUCT(BlueprintType)
struct FCommonEquipmentList : public FFastArraySerializer
{
	GENERATED_BODY()

	FCommonEquipmentList()
		: OwnerComponent(nullptr)
	{
	}

	FCommonEquipmentList(UActorComponent* InOwnerComponent)
		: OwnerComponent(InOwnerComponent)
	{
	}

public:
	//~FFastArraySerializer contract
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);
	void PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize);
	UAbilitySystemComponent* GetAbilitySystemComponent() const;
	//~End of FFastArraySerializer contract

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FCommonAppliedEquipmentEntry, FCommonEquipmentList>(Entries, DeltaParms, *this);
	}

	/**Actually Create Equipment(Weapon,Ability)*/
	UCommonEquipmentInstance* AddEntry(TSubclassOf<UCommonEquipmentDefinition> EquipmentDefinition);
	/**Actually Remove Equipment(Weapon,Ability)*/
	void RemoveEntry(UCommonEquipmentInstance* Instance);

private:
	friend UCommonEquipmentManagerComponent;
	
	// Replicated list of equipment entries
	UPROPERTY()
	TArray<FCommonAppliedEquipmentEntry> Entries;

	UPROPERTY(NotReplicated)
	TObjectPtr<UActorComponent> OwnerComponent;
};

template<>
struct TStructOpsTypeTraits<FCommonEquipmentList> : public TStructOpsTypeTraitsBase2<FCommonEquipmentList>
{
	enum { WithNetDeltaSerializer = true };
};



/**
 *		Maintain EquipmentList.
 *		Manage EquipmemtInstance support Add/Remove Item.....
 */
UCLASS()
class COMMONKIT_API UCommonEquipmentManagerComponent : public UPawnComponent
{
	GENERATED_BODY()
public:
	UCommonEquipmentManagerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	//~UObject interface
	/**Not use this instead Using RegisteredSubObjectList*/
	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
	//~End of UObject interface

	//~AActorComponent interface
	virtual void ReadyForReplication() override;
	//~End of AActorComponent interface
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	UCommonEquipmentInstance* EquipItem(TSubclassOf<UCommonEquipmentDefinition> EquipmentDefinition);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void UnequipItem(UCommonEquipmentInstance* ItemInstance);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UCommonEquipmentInstance*> GetEquipmentInstancesOfType(TSubclassOf<UCommonEquipmentInstance> InstanceType) const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UCommonEquipmentInstance* GetFirstInstanceOfType(TSubclassOf<UCommonEquipmentInstance> InstanceType);

private:
	UPROPERTY(Replicated)
	FCommonEquipmentList EquipmentList;
};
