// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/Hostile/Sweeper/DarkSweeper.h"

#include "Components/CapsuleComponent.h"
#include "Core/Character/Hostile/Sweeper/DarkSweeperController.h"



// Sets default values
ADarkSweeper::ADarkSweeper()
{
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = ADarkSweeperController::StaticClass();
	ColdPoint = CreateDefaultSubobject<USphereComponent>(TEXT("Cold Point Collision"));
	ColdPoint->SetupAttachment(RootComponent);
	ColdPoint->InitSphereRadius(86.0f);
	ColdPoint->SetCollisionProfileName("OverlapAllDynamic");

	HotPointLeft = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hot Point Left Collision"));
	HotPointLeft->SetupAttachment(RootComponent);
	HotPointLeft->SetCapsuleHalfHeight(44.0f);
	HotPointLeft->SetCapsuleRadius(22.0f);
	HotPointLeft->SetRelativeLocation(FVector(-80, 18, -25));
	HotPointLeft->SetRelativeRotation(FRotator(90, 0, 0));
	
	HotPointRight = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hot Point Right Collision"));
	HotPointRight->SetupAttachment(RootComponent);
	HotPointRight->SetCapsuleHalfHeight(44.0f);
	HotPointRight->SetCapsuleRadius(22.0f);
	HotPointRight->SetRelativeLocation(FVector(80, 18, -25));
	HotPointRight->SetRelativeRotation(FRotator(90, 0, 0));
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

