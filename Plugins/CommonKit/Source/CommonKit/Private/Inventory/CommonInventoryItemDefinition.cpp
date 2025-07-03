// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/CommonInventoryItemDefinition.h"

#include "Inventory/CommonInventoryItemFragment.h"


UCommonInventoryItemFragment* UCommonInventoryItemDefinition::FindFragmentByClass(TSubclassOf<UCommonInventoryItemFragment> FragmentClass) const
{
	if (FragmentClass != nullptr)
	{
		for (UCommonInventoryItemFragment* Fragment : Fragments)
		{
			if (Fragment && Fragment->IsA(FragmentClass))
			{
				return Fragment;
			}
		}
	}

	return nullptr;
}
