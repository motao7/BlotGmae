// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attribute/BlotCombatAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"


UBlotCombatAttributeSet::UBlotCombatAttributeSet()
	:MaxWalkSpeed(600.f)
{
}

void UBlotCombatAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//COND_OwnerOnly mean that o只复制给这个 Actor 的网络拥有者（NetOwner）对应的客户端
	//This set's owner is PlayerState,while PlayerState's NetOwner is PlayerController
	//REPNOTIFY_Always mean no matter if the value of MaxWalk Speed change,always call OnRep_MaxWalkSpeed
	DOREPLIFETIME_CONDITION(UBlotCombatAttributeSet, MaxWalkSpeed, COND_OwnerOnly);
}

void UBlotCombatAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute==GetMaxWalkSpeedAttribute())
	{
		if (APlayerState* PS=Cast<APlayerState>(GetOwningActor()))
		{
			if (ACharacter* Character=Cast<ACharacter>(PS->GetPawn()))
			{
				if (UCharacterMovementComponent* MoveCom=Character->GetCharacterMovement())
				{
					MoveCom->MaxWalkSpeed=GetMaxWalkSpeed();
				}
			}
		}
	}
}

void UBlotCombatAttributeSet::OnRep_BaseDamage(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBlotCombatAttributeSet, BaseDamage, OldValue);
}

void UBlotCombatAttributeSet::OnRep_BaseHeal(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBlotCombatAttributeSet, BaseHeal, OldValue);
}

void UBlotCombatAttributeSet::OnRep_MaxWalkSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBlotCombatAttributeSet, MaxWalkSpeed, OldValue);
	/**
	*     // 只有 BaseHeal 的值真发生变化才触发
	if (BaseHeal != OldValue)
	{
		设置客户端的值为新值
		OnAttributeChanged.Broadcast(...); 
	}
	 */
	if (APlayerState* PS = Cast<APlayerState>(GetOwningActor()))
	{
		if (ACharacter* Character = Cast<ACharacter>(PS->GetPawn()))
		{
			if (UCharacterMovementComponent* MoveCom = Character->GetCharacterMovement())
			{
				MoveCom->MaxWalkSpeed = GetMaxWalkSpeed();
			}
		}
	}
}
