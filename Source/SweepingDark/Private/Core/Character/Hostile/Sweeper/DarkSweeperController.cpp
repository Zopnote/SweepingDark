
#include "Core/Character/Hostile/Sweeper/DarkSweeperController.h"


ADarkSweeperController::ADarkSweeperController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADarkSweeperController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADarkSweeperController::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

