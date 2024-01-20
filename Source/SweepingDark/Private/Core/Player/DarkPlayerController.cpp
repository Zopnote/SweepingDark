
// ReSharper disable CppMemberFunctionMayBeConst
#include "SweepingDark/Public/Core/Player/DarkPlayerController.h"
#include "Components/InputComponent.h"
#include "Core/Player/DarkPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"



ADarkPlayerController::ADarkPlayerController()
{
	
}

void ADarkPlayerController::SetDarkPlayer(ADarkPlayer* PlayerInstance)
{
	DarkPlayer = PlayerInstance;
}





void ADarkPlayerController::SetupInput(UInputComponent* PlayerInputComponent)
{
	try
	{
		
		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADarkPlayerController::PressJump);
		PlayerInputComponent->BindAction("Jump", IE_Released, this, &ADarkPlayerController::ReleaseJump);
		
		PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ADarkPlayerController::PressRun);
		PlayerInputComponent->BindAction("Run", IE_Released, this, &ADarkPlayerController::ReleaseRun);

		PlayerInputComponent->BindAxis("Forward", this, &ADarkPlayerController::Forward);
		PlayerInputComponent->BindAxis("Right", this, &ADarkPlayerController::Right);
		
		PlayerInputComponent->BindAxis("Pitch", this, &ADarkPlayerController::Pitch);
		PlayerInputComponent->BindAxis("Yaw", this, &ADarkPlayerController::Yaw);

		
		PlayerInputComponent->BindAction("W", IE_Pressed, this, &ADarkPlayerController::PressW);
		PlayerInputComponent->BindAction("W", IE_Released, this, &ADarkPlayerController::ReleaseW);
		PlayerInputComponent->BindAction("A", IE_Pressed, this, &ADarkPlayerController::PressA);
		PlayerInputComponent->BindAction("A", IE_Released, this, &ADarkPlayerController::ReleaseA);
		PlayerInputComponent->BindAction("S", IE_Pressed, this, &ADarkPlayerController::PressS);
		PlayerInputComponent->BindAction("S", IE_Released, this, &ADarkPlayerController::ReleaseS);
		PlayerInputComponent->BindAction("D", IE_Pressed, this, &ADarkPlayerController::PressD);
		PlayerInputComponent->BindAction("D", IE_Released, this, &ADarkPlayerController::ReleaseD);
		
		UE_LOG(LogTemp, Verbose, TEXT("Player character binding was executed with no errors."));
	}
	catch (...)
	{
		UE_LOG(LogTemp, Error, TEXT("Player character binding was executed with errors"));
	}
}
void ADarkPlayerController::PressW() { HoldingW = true; }
void ADarkPlayerController::ReleaseW() { HoldingW = false; }
void ADarkPlayerController::PressA() { HoldingA = true; }
void ADarkPlayerController::ReleaseA() { HoldingA = false; }
void ADarkPlayerController::PressS() { HoldingS = true; }
void ADarkPlayerController::ReleaseS() { HoldingS = false; }
void ADarkPlayerController::PressD() { HoldingD = true; }
void ADarkPlayerController::ReleaseD() { HoldingD = false; }



FVector2D ADarkPlayerController::GetDirectionality() const
{
	
	return Directionality;
}

FVector2D ADarkPlayerController::SetDirectionality() const { return Directionality; }

	/*Check if the player moving against a wall etc.*/
bool ADarkPlayerController::GetIsStuck() const { return DarkPlayer->GetVelocity().SizeSquared() < FMath::Square(10.0f) && GetIsHoldingMove() && !GetIsGhostHold(); }

	/*Check if the player hold one button that let him move*/
bool ADarkPlayerController::GetIsHoldingMove() const { return (HoldingA || HoldingD || HoldingS || HoldingW); }

	/*Check if the player hold button to run*/
bool ADarkPlayerController::GetIsHoldingRun() const { return HoldingRun; }

bool ADarkPlayerController::GetIsGhostHold() const { return (HoldingA && HoldingD || HoldingW && HoldingS); }



	
void ADarkPlayerController::PressJump()
{
	DarkPlayer->Jump();
}

void ADarkPlayerController::ReleaseJump()
{
	DarkPlayer->StopJumping();
}

void ADarkPlayerController::PressRun() 
{
	UCharacterMovementComponent* Movement = DarkPlayer->GetCharacterMovement();
	Movement->MaxWalkSpeed = DarkPlayer->RunningSpeed;
	HoldingRun = true;
}

void ADarkPlayerController::ReleaseRun() 
{
	UCharacterMovementComponent* Movement = DarkPlayer->GetCharacterMovement();
	Movement->MaxWalkSpeed = DarkPlayer->WalkingSpeed;
	HoldingRun = false;
}

void ADarkPlayerController::Forward(const float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		/*Find out which direction is right*/
		const FRotator Rotation = DarkPlayer->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		/*Get forward vector*/
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		Directionality = FVector2D(0, AxisValue*-1);
		/*Add movement in that direction*/
		DarkPlayer->AddMovementInput(Direction, AxisValue);
	}
}

void ADarkPlayerController::Right(const float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		/*Find out which direction is right*/
		const FRotator Rotation = DarkPlayer->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		/*Get right vector*/ 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		
		Directionality = FVector2D(AxisValue, 0);

		/*Add movement in that direction*/
		DarkPlayer->AddMovementInput(Direction, AxisValue);
	}
}

void ADarkPlayerController::Pitch(const float AxisValue)
{
	
	if (!ActiveLocomotion)
	{
		return;
	}
	const FRotator Old = DarkPlayer->CameraBoom->GetRelativeRotation();
	DarkPlayer->CameraBoom->SetRelativeRotation(FRotator(Old.Pitch+AxisValue, Old.Yaw, Old.Roll));
	
}

void ADarkPlayerController::Yaw(const float AxisValue)
{
	if (!ActiveLocomotion)
	{
		return;
	}
	DarkPlayer->AddControllerYawInput(AxisValue);
}

