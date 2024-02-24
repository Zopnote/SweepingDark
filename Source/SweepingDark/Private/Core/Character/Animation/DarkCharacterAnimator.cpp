// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/Animation/DarkCharacterAnimator.h"

#include "Core/Character/DarkCharacter.h"
#include "Core/Character/Animation/DarkCharacterChase.h"

void UDarkCharacterAnimator::SetCurrentCharacterChase(const EDarkCharacterChase CharacterChase)
{
	CurrentCharacterChase = CharacterChase;
}

int UDarkCharacterAnimator::GetCurrentCharacterChase() const
{
	return CurrentCharacterChase;
}

void UDarkCharacterAnimator::SetCharacter(ADarkCharacter* NewCharacter)
{
	Character = NewCharacter;
}



ADarkCharacter* UDarkCharacterAnimator::GetCharacter() const
{
	return Character;
}

void UDarkCharacterAnimator::SetAnimationState(UDarkAnimationState* NewAnimationState)
{
	if (NewAnimationState == nullptr)
	{
		return;
	}
	CurrentAnimationState = NewAnimationState->Name;
	if (CurrentCharacterChase == Front)
	{
		GetCharacter()->Sprite->SetFlipbook(NewAnimationState->Front);
		return;
	}
	if (CurrentCharacterChase == Back)
	{
		GetCharacter()->Sprite->SetFlipbook(NewAnimationState->Back);
		return;
	}
	if (CurrentCharacterChase == Right)
	{
		GetCharacter()->Sprite->SetFlipbook(NewAnimationState->Right);
		return;
	}
	if (CurrentCharacterChase == Left)
	{
		GetCharacter()->Sprite->SetFlipbook(NewAnimationState->Left);
		return;
	}
}



UDarkAnimationState* UDarkCharacterAnimator::GetAnimationState(const FString& Name)
{
	for (TSubclassOf<UDarkAnimationState> DarkStateClass : AnimationStates)
	{
		if (UDarkAnimationState* DarkStateInstance = DarkStateClass.GetDefaultObject(); DarkStateInstance && DarkStateInstance->Name.Equals(Name))
		{
			return DarkStateInstance;
		}
	}
	return nullptr;
}

void UDarkCharacterAnimator::RefreshAnimationDirectionality()
{
	if (CurrentCharacterChase == Front)
	{
		GetCharacter()->Sprite->SetFlipbook(GetAnimationState(CurrentAnimationState)->Front);
		return;
	}
	if (CurrentCharacterChase == Back)
	{
		GetCharacter()->Sprite->SetFlipbook(GetAnimationState(CurrentAnimationState)->Back);
		return;
	}
	if (CurrentCharacterChase == Right)
	{
		GetCharacter()->Sprite->SetFlipbook(GetAnimationState(CurrentAnimationState)->Right);
		return;
	}
	if (CurrentCharacterChase == Left)
	{
		GetCharacter()->Sprite->SetFlipbook(GetAnimationState(CurrentAnimationState)->Left);
		return;
	}
}


void UDarkCharacterAnimator::DirectionalRelativeCameraChange(const EDarkCharacterChase CharacterChase)
{
	SetCurrentCharacterChase(CharacterChase);
	RefreshAnimationDirectionality();
}


void UDarkCharacterAnimator::ActorDirectionalityChange(FVector2D AxisValue)
{
	
}

void UDarkCharacterAnimator::Tick(const float Delta)
{
}

