// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/CommonEquipmentManagerComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "ExperienceAbilitySet.h"
#include "Equipment/CommonEquipmentDefinition.h"
#include "Equipment/CommonEquipmentInstance.h"
#include "Net/UnrealNetwork.h"


void FCommonEquipmentList::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
}

void FCommonEquipmentList::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
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
			AbilitySet->GiveToAbilitySystem(ASC, Result);
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
		//TODO:Remove Ability through  Entry.GrantedHandles
		FCommonAppliedEquipmentEntry& Entry = *EntryIt;
		if (Entry.Instance == Instance)
		// {
		// 	if (ULyraAbilitySystemComponent* ASC = GetAbilitySystemComponent())
		// 	{
		// 		Entry.GrantedHandles.TakeFromAbilitySystem(ASC);
		// 	}

			Instance->DestroyEquipmentActors();
		
			EntryIt.RemoveCurrent();
			MarkArrayDirty();
		}
}

//////////////////////////////////////////////////////

UCommonEquipmentManagerComponent::UCommonEquipmentManagerComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), EquipmentList(this)
{
	SetIsReplicatedByDefault(true);
	bWantsInitializeComponent = true;
}

void UCommonEquipmentManagerComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass,EquipmentList);
}

UCommonEquipmentInstance* UCommonEquipmentManagerComponent::EquipItem(TSubclassOf<UCommonEquipmentDefinition> EquipmentDefinition)
{
	UCommonEquipmentInstance* Result = nullptr;
	if (EquipmentDefinition != nullptr)
	{
		Result = EquipmentList.AddEntry(EquipmentDefinition);
		if (Result != nullptr)
		{
			if (IsUsingRegisteredSubObjectList() && IsReadyForReplication())
			{
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
		EquipmentList.RemoveEntry(ItemInstance);
	}
}
