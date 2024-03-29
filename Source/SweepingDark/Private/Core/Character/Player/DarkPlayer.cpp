﻿
#include "Core/Character/Player/DarkPlayer.h"

#include "Camera/CameraComponent.h"
#include "Core/Character/Player/DarkPlayerAnimator.h"
#include "Core/Character/Player/DarkPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


void ADarkPlayer::WhenScalarDegreeChanged(const float Degree, const bool RightAxisValue)
{
	Super::WhenScalarDegreeChanged(Degree, RightAxisValue);
}

ADarkPlayer::ADarkPlayer()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	PlayerAnimationComponent = CreateDefaultSubobject<UDarkPlayerAnimator>(TEXT("Player Animation Component"));
	PlayerAnimationComponent->InitializePlayerAnimationComponent(this);
	Falling = false;
	AttackAble = true;
	WalkingSpeed = 350.0f;
	RunningSpeed = 700.0f;
	RightRunningSpeed = 750.0f;
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = WalkingSpeed;
	PlayerController = CreateDefaultSubobject<ADarkPlayerController>(TEXT("PlayerController"));
	PlayerController->SetDarkPlayer(this);
	Controller = PlayerController;
	UseSpecificSpectrum = false;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; 
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetRelativeLocation(FVector(60.0f, 30.0f, 60.0f));
	CameraBoom->SetRelativeRotation(FRotator(-20.0f, -90.0f, 0.0f));
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	GetCharacterMovement()->bOrientRotationToMovement = false;
	FollowCamera->bUsePawnControlRotation = false;
	
	PlayerController->ActiveLocomotion = true;
	
	InversedHelmetSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Inversed Helmet Sprite"));
	InversedHelmetSprite->SetupAttachment(GetRootComponent());
	InversedHelmetSprite->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	InversedHelmetSprite->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	
	InversedChestSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Inversed Chest Sprite"));
	InversedChestSprite->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	InversedChestSprite->SetupAttachment(GetRootComponent());
	InversedChestSprite->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

	InversedBootsSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Inversed BootsSprite"));
	InversedBootsSprite->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	InversedBootsSprite->SetupAttachment(GetRootComponent());
	InversedBootsSprite->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	
	
	HelmetSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Helmet Sprite"));
	HelmetSprite->SetupAttachment(GetRootComponent());
	HelmetSprite->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	
	ChestSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Chest Sprite"));
	ChestSprite->SetupAttachment(GetRootComponent());
	ChestSprite->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	
	BootsSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Boots Sprite"));
	BootsSprite->SetupAttachment(GetRootComponent());
	BootsSprite->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	
}

void ADarkPlayer::Landed(const FHitResult& Hit)
{
	Falling = false;
	Super::Landed(Hit);
}


ADarkPlayerController* ADarkPlayer::GetDarkPlayerController() const
{
	return PlayerController;
}

void ADarkPlayer::WhenFalling_Implementation() {}

void ADarkPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerController->SetupInput(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADarkPlayer::Tick(const float DeltaSeconds)
{
	PlayerController->Tick(DeltaSeconds);
	if (!Falling)
	{
		if (GetVelocity().Z < 0)
		{
			WhenFalling();
			Falling = !Falling;
		}
	}
	Super::Tick(DeltaSeconds);
}

