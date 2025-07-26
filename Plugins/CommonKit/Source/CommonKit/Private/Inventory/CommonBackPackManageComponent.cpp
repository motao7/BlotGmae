// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/CommonBackPackManageComponent.h"

#include "CommonKitStatics.h"
#include "Equipment/CommonQuickBarComponent.h"


UCommonInventoryItemInstance* UCommonBackPackManageComponent::AddItemByDefinition(TSubclassOf<UCommonInventoryItemDefinition> ItemDef, int32 StackCount)
{
	UCommonInventoryItemInstance* Result=Super::AddItemByDefinition(ItemDef, StackCount);

	if (UCommonQuickBarComponent* QuickBar=UCommonKitStatics::GetQuickBarManagerFromController(GetOwnerAsController()))
	{
		if (!QuickBar->HasItemInSlots(Result))
		{
			int32 FreeIndex=QuickBar->GetNextFreeItemSlot();
			QuickBar->AddItemToSlot(FreeIndex,Result);
		}
	}
	return Result;
}
