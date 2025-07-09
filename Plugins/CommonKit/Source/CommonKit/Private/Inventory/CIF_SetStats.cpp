// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/CIF_SetStats.h"
#include "Inventory/CommonInventoryItemInstance.h"


void UCIF_SetStats::OnInstanceCreated(UCommonInventoryItemInstance* Instance) const
{
	for (auto& KVP : InitialItemStats)
	{
		Instance->AddStatTagStack(KVP.Key, KVP.Value);
	}
}

int32 UCIF_SetStats::GetItemStatByTag(FGameplayTag Tag) const
{
	if (const int32* StatPtr = InitialItemStats.Find(Tag))
	{
		return *StatPtr;
	}

	return 0;
}
