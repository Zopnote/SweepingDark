// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/DarkCharacter.h"


// Sets default values
ADarkCharacter::ADarkCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADarkCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADarkCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADarkCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

