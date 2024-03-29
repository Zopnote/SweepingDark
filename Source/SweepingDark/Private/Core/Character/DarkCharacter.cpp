﻿

// ReSharper disable CppMemberFunctionMayBeStatic
#include "Core/Character/DarkCharacter.h"

#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Core/Character/Animation/DarkCharacterAnimator.h"
#include "Core/Character/Animation/DarkCharacterChase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


void ADarkCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (IsValid(this))
	{
		if (Sprite)
		{
			// force animation tick after movement component updates
			if (Sprite->PrimaryComponentTick.bCanEverTick && GetCharacterMovement())
			{
				Sprite->PrimaryComponentTick.AddPrerequisite(GetCharacterMovement(), GetCharacterMovement()->PrimaryComponentTick);
			}
		}
	}
}

// Sets default values
ADarkCharacter::ADarkCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.DoNotCreateDefaultSubobject(MeshComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
	
	InversedSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Inversed Sprite"));
	InversedSprite->SetupAttachment(RootComponent);
	InversedSprite->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	InversedSprite->SetRelativeScale3D(FVector(3.9f, 1.0f, 3.8f));
	InversedSprite->SetRelativeLocation(FVector(0.0f, 0.0f, -15.5f));
	
	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	Sprite->SetupAttachment(RootComponent);
	Sprite->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	Sprite->SetRelativeScale3D(FVector(3.9f, 1.0f, 3.8f));
	Sprite->SetRelativeLocation(FVector(0.0f, 0.0f, -15.5f));

	GetCapsuleComponent()->SetCapsuleRadius(34.0f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(60.0f);
	
	HitColdPoint = CreateDefaultSubobject<USphereComponent>(TEXT("Cold Point Collision"));
	HitColdPoint->SetupAttachment(RootComponent);
	HitColdPoint->InitSphereRadius(66.0f);
	HitColdPoint->SetCollisionProfileName("OverlapAllDynamic");

	
	HitAreaPoint = CreateDefaultSubobject<USphereComponent>(TEXT("Area Point Collision"));
	HitAreaPoint->SetupAttachment(RootComponent);
	HitAreaPoint->InitSphereRadius(95.0f);
	HitAreaPoint->SetCollisionProfileName("OverlapAllDynamic");
	
	HitSuperflatPoint = CreateDefaultSubobject<USphereComponent>(TEXT("Superflat Point Collision"));
	HitSuperflatPoint->SetupAttachment(HitAreaPoint);
	HitSuperflatPoint->InitSphereRadius(140.0f);
	HitSuperflatPoint->SetCollisionProfileName("OverlapAllDynamic");
	
	HitHotPointLeft = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hot Point Left Collision"));
	HitHotPointLeft->SetupAttachment(HitColdPoint);
	HitHotPointLeft->SetCapsuleHalfHeight(35.0f);
	HitHotPointLeft->SetCapsuleRadius(22.0f);
	HitHotPointLeft->SetRelativeLocation(FVector(-75, 0, -6));
	HitHotPointLeft->SetRelativeRotation(FRotator(90, 0, 0));
	
	HitHotPointRight = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hot Point Right Collision"));
	HitHotPointRight->SetupAttachment(HitColdPoint);
	HitHotPointRight->SetCapsuleHalfHeight(35.0f);
	HitHotPointRight->SetCapsuleRadius(22.0f);
	HitHotPointRight->SetRelativeLocation(FVector(75, 0, -6));
	HitHotPointRight->SetRelativeRotation(FRotator(90, 0, 0));

	HitHotPointFront = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hot Point Front Collision"));
	HitHotPointFront->SetupAttachment(HitColdPoint);
	HitHotPointFront->SetCapsuleHalfHeight(35.0f);
	HitHotPointFront->SetCapsuleRadius(22.0f);
	HitHotPointFront->SetRelativeLocation(FVector(0, -60, -6));
	HitHotPointFront->SetRelativeRotation(FRotator(90, 0, 90));
	
	HitHotPointBack = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hot Point Back Collision"));
	HitHotPointBack->SetupAttachment(HitColdPoint);
	HitHotPointBack->SetCapsuleHalfHeight(35.0f);
	HitHotPointBack->SetCapsuleRadius(22.0f);
	HitHotPointBack->SetRelativeLocation(FVector(0, 60, -6));
	HitHotPointBack->SetRelativeRotation(FRotator(90, 0, 90));
	
}

bool ADarkCharacter::SetDrectionality(const FVector2D NewDirection)
{
	WhenDirectionalityChanged(Directionality, NewDirection);
	Directionality = NewDirection;
	return true;
}

FVector2D ADarkCharacter::GetDrectionality() const
{
	return Directionality;
}

void ADarkCharacter::BeginPlay()
{
	Super::BeginPlay();
	bool Valid = false;
	const UClass* CharacterAnimationComponentClass = CharacterAnimationComponent.Get();
	UDarkCharacterAnimator* AnimationComponent = nullptr;
	if (CharacterAnimationComponentClass)
	{
		AnimationComponent = Cast<UDarkCharacterAnimator>(CharacterAnimationComponentClass->GetDefaultObject());
		if (AnimationComponent) { Valid = true; }
		
	}
	if (!Valid) { return; }
	AnimationComponent->SetCharacter(this);
}

void ADarkCharacter::WhenDirectionalityChanged(FVector2D OldDirection, const FVector2D NewDirection)
{
	bool Valid = false;
	const UClass* CharacterAnimationComponentClass = CharacterAnimationComponent.Get();
	UDarkCharacterAnimator* AnimationComponent = nullptr;
	if (CharacterAnimationComponentClass)
	{
		AnimationComponent = Cast<UDarkCharacterAnimator>(CharacterAnimationComponentClass->GetDefaultObject());
		if (AnimationComponent) { Valid = true; }
		
	}
	if (!Valid) { return; }
	AnimationComponent->ActorDirectionalityChange(NewDirection);
}

void ADarkCharacter::WhenScalarDegreeChanged(const float Degree, const bool RightAxisValue)
{
	FSpectrum FrontSpec;
	FSpectrum RightLeftSpec;
	FSpectrum BackSpec;
	bool Set = false;
	if (UseSpecificSpectrum && !Set)
	{
		FrontSpec.Start = SpecificSpectrumFront.Start;
		FrontSpec.End = SpecificSpectrumFront.End;
		RightLeftSpec.Start = SpecificSpectrumRightLeft.Start;
		RightLeftSpec.End = SpecificSpectrumRightLeft.End;
		BackSpec.Start = SpecificSpectrumBack.Start;
		BackSpec.End = SpecificSpectrumBack.End;
		Set = !Set;
	}
	if (RealtiveCameraHeight > 0.9)
	{
		return;
	}
	if (RealtiveCameraHeight > 0.7 && !Set)
	{
		FrontSpec.Start = 0;
		FrontSpec.End = 70;
		RightLeftSpec.Start = 70;
		RightLeftSpec.End = 120;
		BackSpec.Start = 120;
		BackSpec.End = 180;
		Set = !Set;
	}
	if (RealtiveCameraHeight > 0.5 && !Set)
	{
		FrontSpec.Start = 0;
		FrontSpec.End = 58;
		RightLeftSpec.Start = 58;
		RightLeftSpec.End = 120;
		BackSpec.Start = 120;
		BackSpec.End = 180;
		Set = !Set;
	}
	if (RealtiveCameraHeight > 0.45 && !Set)
	{
		FrontSpec.Start = 0;
		FrontSpec.End = 55;
		RightLeftSpec.Start = 55;
		RightLeftSpec.End = 120;
		BackSpec.Start = 120;
		BackSpec.End = 180;
		Set = !Set;
	}
	if (!Set)
	{
		FrontSpec.Start = 0;
		FrontSpec.End = 55;
		RightLeftSpec.Start = 55;
		RightLeftSpec.End = 128;
		BackSpec.Start = 128;
		BackSpec.End = 180;
		Set = !Set;
	}
	
	
	bool Valid = false;
	const UClass* CharacterAnimationComponentClass = CharacterAnimationComponent.Get();
	UDarkCharacterAnimator* AnimationComponent = nullptr;
	if (CharacterAnimationComponentClass)
	{
		AnimationComponent = Cast<UDarkCharacterAnimator>(CharacterAnimationComponentClass->GetDefaultObject());
		if (AnimationComponent) { Valid = true; }
		
	}
	if (!Valid) { return; }
	
	const FString String = FString::SanitizeFloat(Degree);

	
	if (FrontSpec.Start<Degree && Degree<FrontSpec.End)
	{
		AnimationComponent->DirectionalRelativeCameraChange(Front);
		Sprite->SetRelativeRotation(FRotator(0.0f, -90, 0.0f));
		InversedSprite->SetRelativeRotation(FRotator(0.0f, -270, 0.0f));
		return;
	}

	
	if ( RightLeftSpec.Start<Degree && Degree<RightLeftSpec.End)
	{
		if (RightAxisValue)
		{
		AnimationComponent->DirectionalRelativeCameraChange(Right);
			Sprite->SetRelativeRotation(FRotator(0.0f, -180, 0.0f));
			InversedSprite->SetRelativeRotation(FRotator(0.0f, 0, 0.0f));
			return;
		}
		AnimationComponent->DirectionalRelativeCameraChange(Left);
		Sprite->SetRelativeRotation(FRotator(0.0f, 0, 0.0f));
		InversedSprite->SetRelativeRotation(FRotator(0.0f, -180, 0.0f));
		return;
	}

	
	if (BackSpec.Start<Degree && Degree<BackSpec.End)
	{
		AnimationComponent->DirectionalRelativeCameraChange(Back);
		Sprite->SetRelativeRotation(FRotator(0.0f, -270, 0.0f));
		InversedSprite->SetRelativeRotation(FRotator(0.0f, -90, 0.0f));
		return;
	}
}



void ADarkCharacter::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (CharacterAnimationComponent)
	{
		CharacterAnimationComponent->GetDefaultObject<UDarkCharacterAnimator>()->Tick(DeltaSeconds);
	}
	//TODO: Change later to make multiplayer works 
	if (const APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0))
		{
		// Setup and save vectors for calculations
			const FVector OtherActor = CameraManager->GetCameraLocation();
			const FVector FirstVector = GetActorForwardVector();
			FVector SecondVector = FVector(OtherActor.X-GetActorLocation().X, OtherActor.Y-GetActorLocation().Y, OtherActor.Z-GetActorLocation().Z);
			SecondVector.Normalize(0.0001);
		// Calculate scalarproduct of the two vectors
			const float ScalarProduct = FirstVector.X * SecondVector.X + FirstVector.Y * SecondVector.Y + FirstVector.Z * SecondVector.Z;
		// Calculate the angle of the vectores out of the scalarproduct
			const float ArcCosineInRadians = FMath::Acos(ScalarProduct);
		// Calculate the degrees out of radians
			const float ArcCosineInDegrees = ArcCosineInRadians * (180 / 3.14159265358979323846);
			const float RightScalarProduct = GetActorRightVector().X * SecondVector.X + GetActorRightVector().Y * SecondVector.Y + GetActorRightVector().Z * SecondVector.Z;
			const bool SideSwitch = RightScalarProduct<0;
			WhenScalarDegreeChanged(ArcCosineInDegrees, SideSwitch);
		}
	if (const APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0))
	{
		const FVector OtherActor = CameraManager->GetCameraLocation();
		FVector SecondVector = OtherActor - GetActorLocation();
		SecondVector = GetTransform().InverseTransformVectorNoScale(SecondVector);
		SecondVector.Normalize(0.0001);
		RealtiveCameraHeight = SecondVector.Z;
		
	}
}

