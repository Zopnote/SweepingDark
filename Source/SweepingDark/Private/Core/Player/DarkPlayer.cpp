
#include "Core/Player/DarkPlayer.h"

#include "Camera/CameraComponent.h"
#include "Core/Player/DarkPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


ADarkPlayer::ADarkPlayer()
{
	Falling = false;
	AttackAble = true;
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = WalkingSpeed;
	PlayerController = CreateDefaultSubobject<ADarkPlayerController>(TEXT("PlayerController"));
	Controller = PlayerController;
	PlayerController->SetDarkPlayer(this);
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; 
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->SetRelativeLocation(FVector(60.0f, 30.0f, 60.0f));
	CameraBoom->SetRelativeRotation(FRotator(-20.0f, -90.0f, 0.0f));
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	PlayerController->ActiveLocomotion = true;
	
}

void ADarkPlayer::Landed(const FHitResult& Hit)
{
	Falling = false;
	Super::Landed(Hit);
}


ADarkPlayerController* ADarkPlayer::GetDarkController() const { return PlayerController; }

void ADarkPlayer::WhenFalling_Implementation() {}

void ADarkPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerController->SetupInput(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADarkPlayer::Tick(const float DeltaSeconds)
{
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

