// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonSignificanceSettings.h"


float FSignificanceDistanceThresholdSettings::GetSignificanceByDistance(float Distance) const
{
	const int32 Num = Thresholds.Num();
	if (Num==0) return 0.f;
	if (Distance>=Thresholds[Num-1].MaxDistance) return Thresholds[Num-1].Significance;

	for (int32 Index = 0;Index<Num;Index++)
	{
		if (Distance<=Thresholds[Index].MaxDistance) return Thresholds[Index].Significance;
	}

	return 0.f;
}

float FSignificanceScreenSizeThresholdSettings::GetSignificanceByScreenSize(float ScreenSize) const
{
	const int32 Num = Thresholds.Num();
	if (Num==0) return 0.f;
	if (ScreenSize>=Thresholds[Num-1].ScreenSize) return Thresholds[Num-1].Significance;

	for (int32 Index = 0;Index<Num;Index++)
	{
		if (ScreenSize <= Thresholds[Index].ScreenSize)
		{
			return Thresholds[Index].Significance;
		}
	}

	return 0.f;
}

float FSignificanceTickIntervalSettings::GetTickIntervalBySignificance(float Significance) const
{
	const int32 Num = TickIntervalMap.Num();
	if (Num == 0) return 0.f;
	if (Significance <= TickIntervalMap[Num - 1].Significance)
	{
		return TickIntervalMap[Num - 1].TickInterval;
	}
	for (int32 Idx = 0; Idx < Num; Idx++)
	{
		if (Significance >= TickIntervalMap[Idx].Significance)
		{
			return TickIntervalMap[Idx].TickInterval;
		}
	}
	return 0.f;
}

const FSignificanceTickIntervalPolicy* USignificanceSettings::GetTickIntervalPolicy(FName InTag, ESignificanceByType InType)
{
	const USignificanceSettings* CDO = GetDefault<USignificanceSettings>();
	switch (InType)
	{
	case ESignificanceByType::Distance:
	case ESignificanceByType::Distance2D:
		for (const FSignificanceTickIntervalByDistancePolicy& Policy : CDO->DistancePolicies)
		{
			if (Policy.Tag == InTag) return &Policy;
		}
		break;
	case ESignificanceByType::ScreenSize:
		for (const FSignificanceTickIntervalByScreenSizePolicy& Policy : CDO->ScreenSizePolicies)
		{
			if (Policy.Tag == InTag) return &Policy;
		}
		break;
	default:
		break;
	}
	if (!InTag.IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT("SignificanceSettings: Tag(%s) Type(%d) not found!"), *InTag.ToString(), (int32)InType);
	}
	return nullptr;
}
