

#include "Core/Character/DarkCharacter.h"

#include "PaperFlipbookComponent.h"


// Sets default values
ADarkCharacter::ADarkCharacter()
{
	
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADarkCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADarkCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADarkCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

