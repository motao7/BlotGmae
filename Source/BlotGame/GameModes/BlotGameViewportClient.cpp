// Fill out your copyright notice in the Description page of Project Settings.


#include "SignificanceManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/BlotGameViewportClient.h"


void UBlotGameViewportClient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (UWorld* World = GetWorld())
	{
		if (!CachedPC.IsValid())
		{
			CachedPC = TWeakObjectPtr<APlayerController>(
				UGameplayStatics::GetPlayerController(World, 0));
		}

		if (CachedPC.IsValid())
		{
			if (USignificanceManager* SM = USignificanceManager::Get(World))
			{
				FVector ViewLoc;
				FRotator ViewRot;
				CachedPC.Get()->GetPlayerViewPoint(ViewLoc, ViewRot);

				TArray<FTransform> Viewpoints;
				Viewpoints.Emplace(ViewRot, ViewLoc, FVector::OneVector);

				SM->Update(Viewpoints);
			}
		}
	}
}
