// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BlotGameState.h"

#include "ExperienceManagerComponent.h"

ABlotGameState::ABlotGameState(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	ExperienceManagerComponent=CreateDefaultSubobject<UExperienceManagerComponent>(TEXT("ExperienceManagerComponent"));
}
