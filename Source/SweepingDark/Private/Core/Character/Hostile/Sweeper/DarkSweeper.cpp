// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/Hostile/Sweeper/DarkSweeper.h"


// Sets default values
ADarkSweeper::ADarkSweeper()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADarkSweeper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADarkSweeper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADarkSweeper::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

