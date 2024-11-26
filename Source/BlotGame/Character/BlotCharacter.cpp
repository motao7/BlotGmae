// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BlotCharacter.h"

#include "BlotPawnExtensionComponent.h"


ABlotCharacter::ABlotCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	// Character不执行tick事件(网络开销，运算开销的问题)
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	PawnExtensionComponent=CreateDefaultSubobject<UBlotPawnExtensionComponent>(TEXT("PawnExtensionComponent"));
}
