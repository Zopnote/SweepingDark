

#include "Core/Character/Player/DarkPlayerAnimator.h"

#include "Core/Character/Player/DarkPlayer.h"
#include "Core/Character/Player/DarkPlayerController.h"


void UDarkPlayerAnimator::InitializePlayerAnimationComponent(ADarkPlayer* InitDarkPlayer) 
{
	DarkPlayer = InitDarkPlayer;
}

void UDarkPlayerAnimator::Tick(const float Delta)
{
	Super::Tick(Delta);
}
