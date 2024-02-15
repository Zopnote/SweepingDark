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

void UDarkCharacterAnimator::SetSprite(UPaperFlipbookComponent* PaperFlipbookComponent,
	UDarkAnimationState* AnimationState)
{
	if (GetCurrentCharacterChase() == Front)
	{
		PaperFlipbookComponent->SetFlipbook(AnimationState->Front);
		return;
	}
	if (GetCurrentCharacterChase() == Back)
	{
		PaperFlipbookComponent->SetFlipbook(AnimationState->Back);
		return;
	}
	if (GetCurrentCharacterChase() == Left)
	{
		PaperFlipbookComponent->SetFlipbook(AnimationState->Left);
		return;
	}
	if (GetCurrentCharacterChase() == Right)
	{
		PaperFlipbookComponent->SetFlipbook(AnimationState->Right);
		return;
	}
}

ADarkCharacter* UDarkCharacterAnimator::GetCharacter() const
{
	return Character;
}

void UDarkCharacterAnimator::SetAnimationState(UDarkAnimationState* NewAnimationState, EDarkCharacterChase NewCharacterChase)
{
	if (CurrentAnimationState == NewAnimationState->Name && CurrentCharacterChase == NewCharacterChase)
	{
		return;
	}
	WhenAnimationStateChange(GetAnimationState(CurrentAnimationState), NewAnimationState);
	CurrentAnimationState = NewAnimationState->Name;
	SetSprite(Character->Sprite, NewAnimationState);
	//SetSprite(Character->InversedSprite, NewAnimationState);
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



void UDarkCharacterAnimator::Tick(float DelthaSeconds)
{
	
}

void UDarkCharacterAnimator::MultipleActorVectorsChange(const EDarkCharacterChase CharacterChase)
{
	SetAnimationState(GetAnimationState("Walk"), CharacterChase);
	SetCurrentCharacterChase(CharacterChase);
}


void UDarkCharacterAnimator::ActorDirectionalityChange(FVector2D AxisValue)
{
	
}

