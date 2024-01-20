// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Player/DarkPlayer.h"

#include "Camera/CameraComponent.h"
#include "Core/Player/DarkPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


ADarkPlayer::ADarkPlayer()
{
	AttackAble = true;
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = WalkingSpeed;
	PlayerController = CreateDefaultSubobject<ADarkPlayerController>(TEXT("PlayerController"));
	Controller = PlayerController;
	PlayerController->SetDarkPlayer(this);
	if (CameraSettings == nullptr)
	{
		CameraSettings = CreateDefaultSubobject<UDarkCamera>(TEXT("Camera"));
		CameraSettings->CameraMode = EDarkCameraModes::Isometric;
		CameraSettings->DistanceToPlayer = 400.0f;
		CameraSettings->FieldOfView = 80.0f;
	}
	if (CameraSettings->CameraMode == EDarkCameraModes::Isometric)
	{
		CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
		CameraBoom->SetupAttachment(RootComponent);
		CameraBoom->TargetArmLength = CameraSettings->DistanceToPlayer; 
		CameraBoom->bUsePawnControlRotation = false;
		CameraBoom->SetRelativeLocation(FVector(60.0f, 30.0f, 60.0f));
		CameraBoom->SetRelativeRotation(FRotator(-20.0f, -90.0f, 0.0f));
	
		FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
		FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
		FollowCamera->FieldOfView = CameraSettings->FieldOfView;
		FollowCamera->bUsePawnControlRotation = false;
		PlayerController->ActiveLocomotion = false;
	}
	if (CameraSettings->CameraMode == EDarkCameraModes::ThirdPerson)
	{
		CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
		CameraBoom->SetupAttachment(RootComponent);
		CameraBoom->TargetArmLength = CameraSettings->DistanceToPlayer; 
		CameraBoom->bUsePawnControlRotation = false;
		CameraBoom->SetRelativeLocation(FVector(60.0f, 30.0f, 60.0f));
		CameraBoom->SetRelativeRotation(FRotator(-20.0f, -90.0f, 0.0f));
	
		FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
		FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
		FollowCamera->FieldOfView = CameraSettings->FieldOfView;
		FollowCamera->bUsePawnControlRotation = false;
		PlayerController->ActiveLocomotion = true;
	}
	if (CameraSettings->CameraMode == EDarkCameraModes::SideScroller)
	{
		
	}
	
}


ADarkPlayerController* ADarkPlayer::GetDarkController() const
{
		return PlayerController;
}

void ADarkPlayer::WhenFalling_Implementation()
{
}

void ADarkPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerController->SetupInput(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADarkPlayer::BeginPlay()
{
	Super::BeginPlay();
}

