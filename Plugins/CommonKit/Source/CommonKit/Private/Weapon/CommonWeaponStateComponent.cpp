// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/CommonWeaponStateComponent.h"

#include "Kismet/GameplayStatics.h"

double UCommonWeaponStateComponent::GetTimeSinceLastHitNotification() const
{
	UWorld* World = GetWorld();
	return World->TimeSince(LastWeaponDamageInstigatedTime);
}

void UCommonWeaponStateComponent::AddLastWeaponDamageScreenLocations(const TArray<FHitResult>& FoundHits)
{
	if (APlayerController* OwnerPC = GetController<APlayerController>())
	{
		for (const FHitResult& Hit : FoundHits)
		{
			FVector2D HitScreenLocation;
			if (UGameplayStatics::ProjectWorldToScreen(OwnerPC, Hit.Location, /*out*/ HitScreenLocation, /*bPlayerViewportRelative=*/ false))
			{
				LastWeaponDamageScreenLocations.Add(HitScreenLocation);
			}
		}
	}
}

void UCommonWeaponStateComponent::UpdateDamageInstigatedTime()
{
	// If our LastWeaponDamageInstigatedTime was not very recent, clear our LastWeaponDamageScreenLocations array
	UWorld* World = GetWorld();
	if (World->GetTimeSeconds() - LastWeaponDamageInstigatedTime > 0.1)
	{
		LastWeaponDamageScreenLocations.Reset();
	}
	LastWeaponDamageInstigatedTime = World->GetTimeSeconds();
}
