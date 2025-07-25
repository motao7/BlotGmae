// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayTagStack.h"

#include "NativeGameplayTags.h"

/////////////////////////////////////////////////////////////////////
// FGameplayTagStack

FString FGameplayTagStack::GetDebugString() const
{
	return FString::Printf(TEXT("%sx%d"), *Tag.ToString(), StackCount);
}

//////////////////////////////////////////////////////////////////////
// FGameplayTagStackContainer

void FGameplayTagStackContainer::AddStack(FGameplayTag Tag, int32 StackCount)
{
	if (!Tag.IsValid())
	{
		FFrame::KismetExecutionMessage(TEXT("An invalid tag was passed to AddStack"), ELogVerbosity::Warning);
		return;
	}

	for (FGameplayTagStack& Stack : Stacks)
	{
		if (Stack.Tag == Tag)
		{
			const int32 NewCount = Stack.StackCount + StackCount;
			Stack.StackCount = NewCount;
			TagToCountMap[Tag] = NewCount;
			MarkItemDirty(Stack);
			return;
		}
	}

	FGameplayTagStack& NewStack = Stacks.Emplace_GetRef(Tag, StackCount);
	MarkItemDirty(NewStack);
	TagToCountMap.Add(Tag, StackCount);
}

void FGameplayTagStackContainer::RemoveStack(FGameplayTag Tag, int32 StackCount)
{
	if (!Tag.IsValid())
	{
		FFrame::KismetExecutionMessage(TEXT("An invalid tag was passed to RemoveStack"), ELogVerbosity::Warning);
		return;
	}

	//@TODO: Should we error if you try to remove a stack that doesn't exist or has a smaller count?
	for (auto It = Stacks.CreateIterator(); It; ++It)
	{
		FGameplayTagStack& Stack = *It;
		if (Stack.Tag == Tag)
		{
			if (Stack.StackCount <= StackCount)
			{
				It.RemoveCurrent();
				TagToCountMap.Remove(Tag);
				MarkArrayDirty();
			}
			else
			{
				const int32 NewCount = Stack.StackCount - StackCount;
				Stack.StackCount = NewCount;
				TagToCountMap[Tag] = NewCount;
				MarkItemDirty(Stack);
			}
			return;
		}
	}
}

bool FGameplayTagStackContainer::IsEqual(const FGameplayTagStackContainer& Other) const
{
	if (TagToCountMap.Num() != Other.TagToCountMap.Num())
	{
		return false;
	}

	for (const auto& Pair : TagToCountMap)
	{
		const int32* OtherCount = Other.TagToCountMap.Find(Pair.Key);
		if (!OtherCount || *OtherCount != Pair.Value)
		{
			return false;
		}
	}

	return true;
}

void FGameplayTagStackContainer::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
	for (int32 Index : RemovedIndices)
	{
		const FGameplayTag Tag = Stacks[Index].Tag;
		TagToCountMap.Remove(Tag);
	}
}

void FGameplayTagStackContainer::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	for (int32 Index : AddedIndices)
	{
		const FGameplayTagStack& Stack = Stacks[Index];
		TagToCountMap.Add(Stack.Tag, Stack.StackCount);
	}
}

void FGameplayTagStackContainer::PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize)
{
	for (int32 Index : ChangedIndices)
	{
		const FGameplayTagStack& Stack = Stacks[Index];
		TagToCountMap[Stack.Tag] = Stack.StackCount;
	}
}

