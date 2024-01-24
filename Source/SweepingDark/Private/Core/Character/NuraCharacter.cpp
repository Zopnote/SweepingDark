// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/NuraCharacter.h"


// Sets default values
ANuraCharacter::ANuraCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANuraCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANuraCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ANuraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

