
// ReSharper disable CppMemberFunctionMayBeConst
#include "SweepingDark/Public/Core/Character/Player/DarkPlayerController.h"

#include <chrono>
#include <thread>

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Core/Character/Player/DarkPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"



ADarkPlayerController::ADarkPlayerController(): DarkPlayer(nullptr), IsPlayerCameraFocused(false), ActiveLocomotion(false), HoldingRun(false), IsLerping(false), GoalYaw(0), HoldingW(false), HoldingA(false), HoldingS(false), HoldingD(false) { }

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
void ADarkPlayerController::PressW()
{
	HoldingW = true;
}
void ADarkPlayerController::ReleaseW()
{
	HoldingW = false;
	IsPlayerCameraFocused = false;
	IsLerping = false;
}
void ADarkPlayerController::PressA() { HoldingA = true; }
void ADarkPlayerController::ReleaseA() { HoldingA = false; }
void ADarkPlayerController::PressS() { HoldingS = true; }
void ADarkPlayerController::ReleaseS()
{
	HoldingS = false;
	IsPlayerCameraFocused = false;
	IsLerping = false;
}
void ADarkPlayerController::PressD() { HoldingD = true; }
void ADarkPlayerController::ReleaseD() { HoldingD = false; }



FVector2D ADarkPlayerController::GetDirectionality() const
{
	
	return DarkPlayer->GetDrectionality();
}

FVector2D ADarkPlayerController::SetDirectionality() const { return DarkPlayer->GetDrectionality(); }

	/*Check if the player moving against a wall etc.*/
bool ADarkPlayerController::GetIsStuck() const { return DarkPlayer->GetVelocity().SizeSquared() < FMath::Square(10.0f) && GetIsHoldingMove() && !GetIsGhostHold(); }

	/*Check if the player hold one button that let him move*/
bool ADarkPlayerController::GetIsHoldingMove() const { return (HoldingA || HoldingD || HoldingS || HoldingW); }

	/*Check if the player hold button to run*/
bool ADarkPlayerController::GetIsHoldingRun() const { return HoldingRun; }

bool ADarkPlayerController::GetIsGhostHold() const { return (HoldingA && HoldingD || HoldingW && HoldingS); }


void ADarkPlayerController::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (IsLerping)
	{
		if (FMath::IsNearlyEqual(DarkPlayer->GetActorRotation().Yaw, GoalYaw, 2.0))
		{
			if (HoldingW || HoldingS)
			{
				IsPlayerCameraFocused = true;
				IsLerping = !IsLerping;
			}
		}
	}
}

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
	if (HoldingS)
	{
		return;
	}
	if (HoldingA || HoldingD)
	{
		UCharacterMovementComponent* Movement = DarkPlayer->GetCharacterMovement();
		Movement->MaxWalkSpeed = DarkPlayer->RightRunningSpeed;
		HoldingRun = true;
		return;
	}
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

void ADarkPlayerController::Right(const float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		if (HoldingW && IsPlayerCameraFocused)
		{
			const FRotator NewRotation = FRotationMatrix::MakeFromX(DarkPlayer->FollowCamera->GetForwardVector()).Rotator();
			const FRotator Rotation = NewRotation;
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			DarkPlayer->SetDrectionality(FVector2D(0, AxisValue*-1));
			DarkPlayer->AddMovementInput(Direction, AxisValue);
			return;
		}
		const FRotator NewRotation = FRotationMatrix::MakeFromX(DarkPlayer->FollowCamera->GetForwardVector()).Rotator();
		const float DeltaTime = GetWorld()->GetDeltaSeconds();
		float LerpAlpha = FMath::Clamp(10 * DeltaTime, 0.0f, 1.0f);
		FRotator LerpedRotation = FMath::Lerp(DarkPlayer->GetActorRotation(), NewRotation, LerpAlpha);
		DarkPlayer->SetActorRotation(FRotator(0.0f, LerpedRotation.Yaw, 0.0f));
		
		const FRotator Rotation = NewRotation;
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		DarkPlayer->SetDrectionality(FVector2D(0, AxisValue*-1));
		DarkPlayer->AddMovementInput(Direction, AxisValue);
	}
}


void ADarkPlayerController::Forward(const float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		if ((HoldingW || HoldingS) && IsPlayerCameraFocused)
		{
			const FRotator NewRotation = FRotationMatrix::MakeFromX(DarkPlayer->FollowCamera->GetForwardVector()).Rotator();
			DarkPlayer->SetActorRotation(FRotator(0.0f, NewRotation.Yaw, 0.0f));
			
			const FRotator YawRotation(0, NewRotation.Yaw, 0);
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			DarkPlayer->SetDrectionality(FVector2D(AxisValue, 0));
			DarkPlayer->AddMovementInput(Direction, -1*AxisValue);
			return;
		}
		
		const FRotator NewRotation = FRotationMatrix::MakeFromX(DarkPlayer->FollowCamera->GetForwardVector()).Rotator();
		const float DeltaTime = GetWorld()->GetDeltaSeconds();
		float LerpAlpha = FMath::Clamp(14 * DeltaTime, 0.0f, 1.0f);
		FRotator LerpedRotation = FMath::Lerp(DarkPlayer->GetActorRotation(), NewRotation, LerpAlpha);
		DarkPlayer->SetActorRotation(FRotator(0.0f, LerpedRotation.Yaw, 0.0f));
		
		GoalYaw = NewRotation.Yaw;
		IsLerping = true;
		
		const FRotator YawRotation(0, NewRotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		
		DarkPlayer->SetDrectionality(FVector2D(AxisValue, 0));
		DarkPlayer->AddMovementInput(Direction, -1*AxisValue);
	}
}



void ADarkPlayerController::Pitch(const float AxisValue)
{
	if (DarkPlayer->RealtiveCameraHeight > 0.75 && AxisValue > 0)
	{
		return;
	}
	DarkPlayer->AddControllerPitchInput(AxisValue);
}

void ADarkPlayerController::Yaw(const float AxisValue)
{
	if (!ActiveLocomotion) { return; }
	DarkPlayer->AddControllerYawInput(AxisValue);
}

