

#include "Core/Character/DarkCharacter.h"

#include "PaperFlipbookComponent.h"
#include "VectorTypes.h"
#include "Chaos/Utilities.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameSession.h"


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
	HitSuperflatPoint->SetupAttachment(RootComponent);
	HitSuperflatPoint->InitSphereRadius(140.0f);
	HitSuperflatPoint->SetCollisionProfileName("OverlapAllDynamic");
	
	HitHotPointLeft = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hot Point Left Collision"));
	HitHotPointLeft->SetupAttachment(RootComponent);
	HitHotPointLeft->SetCapsuleHalfHeight(35.0f);
	HitHotPointLeft->SetCapsuleRadius(22.0f);
	HitHotPointLeft->SetRelativeLocation(FVector(-75, 0, -6));
	HitHotPointLeft->SetRelativeRotation(FRotator(90, 0, 0));
	
	HitHotPointRight = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hot Point Right Collision"));
	HitHotPointRight->SetupAttachment(RootComponent);
	HitHotPointRight->SetCapsuleHalfHeight(35.0f);
	HitHotPointRight->SetCapsuleRadius(22.0f);
	HitHotPointRight->SetRelativeLocation(FVector(75, 0, -6));
	HitHotPointRight->SetRelativeRotation(FRotator(90, 0, 0));

	HitHotPointFront = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hot Point Front Collision"));
	HitHotPointFront->SetupAttachment(RootComponent);
	HitHotPointFront->SetCapsuleHalfHeight(35.0f);
	HitHotPointFront->SetCapsuleRadius(22.0f);
	HitHotPointFront->SetRelativeLocation(FVector(0, -60, -6));
	HitHotPointFront->SetRelativeRotation(FRotator(90, 0, 90));
	
	HitHotPointBack = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hot Point Back Collision"));
	HitHotPointBack->SetupAttachment(RootComponent);
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

FVector2D ADarkCharacter::GetDrectionality()
{
	return Directionality;
}

void ADarkCharacter::WhenDirectionalityChanged(FVector2D OldDirection, FVector2D NewDirection) {}

// Called when the game starts or when spawned
void ADarkCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADarkCharacter::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
		const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			const FVector OtherActor = PlayerController->GetPawn()->GetActorLocation();
			const FVector FirstVector = GetActorForwardVector();
			FVector SecondVector = FVector(OtherActor.X-GetActorLocation().X, OtherActor.Y-GetActorLocation().Y, OtherActor.Z-GetActorLocation().Z);
			SecondVector.Normalize(0.0001);
			const float ScalarProduct = FirstVector.X * SecondVector.X + FirstVector.Y * SecondVector.Y + FirstVector.Z * SecondVector.Z;
			const float ArcCosineInRadians = FMath::Acos(ScalarProduct);
			float ArcCosineInDegrees = ArcCosineInRadians * (180 / 3.14159265358979323846);
			FString String = FString::SanitizeFloat(ArcCosineInDegrees);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT(""+String));
			const float RightScalarProduct = GetActorRightVector().X * SecondVector.X + GetActorRightVector().Y * SecondVector.Y + GetActorRightVector().Z * SecondVector.Z;
			bool SideSwitch = RightScalarProduct<0;
			
			if (ArcCosineInDegrees<45 && 0<ArcCosineInDegrees)
			{
				Sprite->SetRelativeRotation(FRotator(0.0f, -90, 0.0f));
				InversedSprite->SetRelativeRotation(FRotator(0.0f, -270, 0.0f));
				return;
			}
			
			if (ArcCosineInDegrees<135 && 45<ArcCosineInDegrees)
			{
				if (SideSwitch)
				{
					Sprite->SetRelativeRotation(FRotator(0.0f, -180, 0.0f));
					InversedSprite->SetRelativeRotation(FRotator(0.0f, 0, 0.0f));
					return;
				}
				Sprite->SetRelativeRotation(FRotator(0.0f, 0, 0.0f));
				InversedSprite->SetRelativeRotation(FRotator(0.0f, -180, 0.0f));
				return;
			}
			
			if (ArcCosineInDegrees<180 && 135<ArcCosineInDegrees)
			{
				Sprite->SetRelativeRotation(FRotator(0.0f, -270, 0.0f));
				InversedSprite->SetRelativeRotation(FRotator(0.0f, -90, 0.0f));
				return;
			}
			
		}
}

