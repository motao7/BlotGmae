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

void UCommonBackPackManageComponent::ExchangeItems(int32 Index1, int32 Index2)
{
	// 先调用父类的交换逻辑
	Super::ExchangeItems(Index1, Index2);

	// 获取快捷栏组件
	if (UCommonQuickBarComponent* QuickBar = UCommonKitStatics::GetQuickBarManagerFromController(GetOwnerAsController()))
	{
		// 计算快捷栏的大小（背包大小的1/4）
		const int32 QuickBarSize = QuickBar->GetNumSlots();
		
		// 检查交换的索引是否在快捷栏范围内
		const bool bIndex1InQuickBar = (Index1 >= 0 && Index1 < QuickBarSize);
		const bool bIndex2InQuickBar = (Index2 >= 0 && Index2 < QuickBarSize);
		
		// 获取交换后的物品实例
		UCommonInventoryItemInstance* Item1 = GetItem(Index1);
		UCommonInventoryItemInstance* Item2 = GetItem(Index2);
		
		// 如果Index1在快捷栏范围内
		if (bIndex1InQuickBar)
		{
			// 如果Index1位置现在有物品，则更新快捷栏
			if (Item1)
			{
				QuickBar->RemoveItemFromSlot(Index1);
				QuickBar->AddItemToSlot(Index1, Item1);
			}
			// 如果Index1位置现在没有物品，则从快捷栏移除
			else
			{
				QuickBar->RemoveItemFromSlot(Index1);
			}
		}
		
		// 如果Index2在快捷栏范围内
		if (bIndex2InQuickBar)
		{
			// 如果Index2位置现在有物品，则更新快捷栏
			if (Item2)
			{
				QuickBar->RemoveItemFromSlot(Index2);
				QuickBar->AddItemToSlot(Index2, Item2);
			}
			// 如果Index2位置现在没有物品，则从快捷栏移除
			else
			{
				QuickBar->RemoveItemFromSlot(Index2);
			}
		}
	}
}
