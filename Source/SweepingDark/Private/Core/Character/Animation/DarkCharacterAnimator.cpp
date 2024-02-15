// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/Animation/DarkCharacterAnimator.h"

UDarkAnimationState* UDarkCharacterAnimator::GetAnimationState(const FString& Name)
{
	for (UDarkAnimationState* DarkState : AnimationStates)
	{
		if (DarkState->Name.Equals(Name))
		{
			return DarkState;
		}
	}
	return nullptr;
}

void UDarkCharacterAnimator::Tick(float DelthaSeconds) {}
