// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/CommonEquipmentManagerComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "ExperienceAbilitySet.h"
#include "Engine/ActorChannel.h"
#include "Equipment/CommonEquipmentDefinition.h"
#include "Equipment/CommonEquipmentInstance.h"
#include "Net/UnrealNetwork.h"


void FCommonEquipmentList::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
	for (int32 Index : RemovedIndices)
	{
		const FCommonAppliedEquipmentEntry& Entry = Entries[Index];
		if (Entry.Instance != nullptr)
		{
			Entry.Instance->OnUnequipped();
		}
	}
}

void FCommonEquipmentList::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	for (int32 Index : AddedIndices)
	{
		const FCommonAppliedEquipmentEntry& Entry = Entries[Index];
		if (Entry.Instance != nullptr)
		{
			Entry.Instance->OnEquipped();
		}
	}
}

void FCommonEquipmentList::PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize)
{
}

UAbilitySystemComponent* FCommonEquipmentList::GetAbilitySystemComponent() const
{
	check(OwnerComponent);
	AActor* OwningActor = OwnerComponent->GetOwner();
	return Cast<UAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor));
}

UCommonEquipmentInstance* FCommonEquipmentList::AddEntry(TSubclassOf<UCommonEquipmentDefinition> EquipmentDefinition)
{
	UCommonEquipmentInstance* Result = nullptr;

	check(EquipmentDefinition != nullptr);
	check(OwnerComponent);
	check(OwnerComponent->GetOwner()->HasAuthority());
	
	const UCommonEquipmentDefinition* EquipmentCDO = GetDefault<UCommonEquipmentDefinition>(EquipmentDefinition);

	TSubclassOf<UCommonEquipmentInstance> InstanceType = EquipmentCDO->InstanceType;
	if (InstanceType == nullptr)
	{
		InstanceType = UCommonEquipmentInstance::StaticClass();
	}
	
	FCommonAppliedEquipmentEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.EquipmentDefinition = EquipmentDefinition;
	NewEntry.Instance = NewObject<UCommonEquipmentInstance>(OwnerComponent->GetOwner(), InstanceType);
	Result = NewEntry.Instance;

	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
	{
		for (const TObjectPtr<const UExperienceAbilitySet>& AbilitySet : EquipmentCDO->AbilitySetsToGrant)
		{
			//Add EquipmentInstance as SourceObject for Ability
			AbilitySet->GiveToAbilitySystem(ASC,/*inout*/ &NewEntry.GrantedHandles,Result);
		}
	}
	else
	{
		//@TODO: Warning logging?
	}

	Result->SpawnEquipmentActors(EquipmentCDO->ActorsToSpawn);
	
	MarkItemDirty(NewEntry);

	return Result;
}

void FCommonEquipmentList::RemoveEntry(UCommonEquipmentInstance* Instance)
{
	for (auto EntryIt = Entries.CreateIterator(); EntryIt; ++EntryIt)
	{
		FCommonAppliedEquipmentEntry& Entry = *EntryIt;
		if (Entry.Instance == Instance)
		{
			if (UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
			{
				Entry.GrantedHandles.TakeFromAbilitySystem(ASC);
			}
		}
		Instance->DestroyEquipmentActors();
		
		EntryIt.RemoveCurrent();
		MarkArrayDirty();
	}
}


//////////////////////////////////////////////////////////////////////

UCommonEquipmentManagerComponent::UCommonEquipmentManagerComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), EquipmentList(this)
{
	SetIsReplicatedByDefault(true);
	bWantsInitializeComponent = true;
	bReplicateUsingRegisteredSubObjectList=true;
}

void UCommonEquipmentManagerComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass,EquipmentList);
}

bool UCommonEquipmentManagerComponent::ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	// bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
	//
	// for (FCommonAppliedEquipmentEntry& Entry : EquipmentList.Entries)
	// {
	// 	UCommonEquipmentInstance* Instance = Entry.Instance;
	//
	// 	if (IsValid(Instance))
	// 	{
	// 		// WroteSomething |= Channel->ReplicateSubobject(Instance, *Bunch, *RepFlags);
	// 	}
	// }
	//
	// return WroteSomething;
	return Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
}

UCommonEquipmentInstance* UCommonEquipmentManagerComponent::EquipItem(TSubclassOf<UCommonEquipmentDefinition> EquipmentDefinition)
{
	UCommonEquipmentInstance* Result = nullptr;
	if (EquipmentDefinition != nullptr)
	{
		Result = EquipmentList.AddEntry(EquipmentDefinition);
		if (Result != nullptr)
		{
			Result->OnEquipped();
			if (IsUsingRegisteredSubObjectList() && IsReadyForReplication())
			{
				//UObjectPtr not automatically Replicated like AActorPtr 
				AddReplicatedSubObject(Result);
			}
		}
	}
	return Result;
}

void UCommonEquipmentManagerComponent::UnequipItem(UCommonEquipmentInstance* ItemInstance)
{
	if (ItemInstance != nullptr)
	{
		if (IsUsingRegisteredSubObjectList())
		{
			RemoveReplicatedSubObject(ItemInstance);
		}

		ItemInstance->OnUnequipped();
		EquipmentList.RemoveEntry(ItemInstance);
	}
}

void UCommonEquipmentManagerComponent::ReadyForReplication()
{
	Super::ReadyForReplication();

	// Register existing CommonEquipmentInstances
	if (IsUsingRegisteredSubObjectList())
	{
		for (const FCommonAppliedEquipmentEntry& Entry : EquipmentList.Entries)
		{
			UCommonEquipmentInstance* Instance = Entry.Instance;

			if (IsValid(Instance))
			{
				AddReplicatedSubObject(Instance);
			}
		}
	}
}

TArray<UCommonEquipmentInstance*> UCommonEquipmentManagerComponent::GetEquipmentInstancesOfType(TSubclassOf<UCommonEquipmentInstance> InstanceType) const
{
	TArray<UCommonEquipmentInstance*> Results;
	for (const FCommonAppliedEquipmentEntry& Entry : EquipmentList.Entries)
	{
		if (UCommonEquipmentInstance* Instance = Entry.Instance)
		{
			if (Instance->IsA(InstanceType))
			{
				Results.Add(Instance);
			}
		}
	}
	return Results;
}

UCommonEquipmentInstance* UCommonEquipmentManagerComponent::GetFirstInstanceOfType(TSubclassOf<UCommonEquipmentInstance> InstanceType)
{
	for (FCommonAppliedEquipmentEntry& Entry : EquipmentList.Entries)
	{
		if (UCommonEquipmentInstance* Instance = Entry.Instance)
		{
			if (Instance->IsA(InstanceType))
			{
				return Instance;
			}
		}
	}

	return nullptr;
}
