// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/Animation/DarkCharacterAnimator.h"

#include "Core/Character/DarkCharacter.h"
#include "Core/Character/Animation/DarkCharacterChase.h"

void UDarkCharacterAnimator::SetCurrentCharacterChase(EDarkCharacterChase CharacterChase)
{
	CurrentCharacterChase = CharacterChase;
}

int UDarkCharacterAnimator::GetCurrentCharacterChase()
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
	WhenAnimationStateChange(GetAnimationState(CurrentAnimationState), NewAnimationState);
	CurrentAnimationState = NewAnimationState->Name;
	if (CurrentCharacterChase == Front)
	{
		GetCharacter()->Sprite->SetFlipbook(GetAnimationState("Walk")->Front);
		return;
	}
	if (CurrentCharacterChase == Back)
	{
		GetCharacter()->Sprite->SetFlipbook(GetAnimationState("Walk")->Back);
		return;
	}
	if (CurrentCharacterChase == Right)
	{
		GetCharacter()->Sprite->SetFlipbook(GetAnimationState("Walk")->Right);
		return;
	}
	if (CurrentCharacterChase == Left)
	{
		GetCharacter()->Sprite->SetFlipbook(GetAnimationState("Walk")->Left);
		return;
	}
}

void UDarkCharacterAnimator::WhenAnimationStateChange(UDarkAnimationState* OldAnimationState,
	UDarkAnimationState* NewAnimationState)
{
	
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



void UDarkCharacterAnimator::MultipleActorVectorsChange(const EDarkCharacterChase CharacterChase)
{
	SetCurrentCharacterChase(CharacterChase);
	SetAnimationState(GetAnimationState("Walk"));
}


void UDarkCharacterAnimator::ActorDirectionalityChange(FVector2D AxisValue)
{
	SetAnimationState(GetAnimationState("Walk"));
}

