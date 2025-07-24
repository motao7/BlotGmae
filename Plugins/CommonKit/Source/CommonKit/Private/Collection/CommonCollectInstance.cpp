// Fill out your copyright notice in the Description page of Project Settings.


#include "Collection/CommonCollectInstance.h"

#include "Inventory/CommonInventoryItemInstance.h"


UCommonInventoryItemInstance* UCommonCollectInstance::GetAssociateInventoryInstance()
{
	return Cast<UCommonInventoryItemInstance>(GetInstigator()); 
}
