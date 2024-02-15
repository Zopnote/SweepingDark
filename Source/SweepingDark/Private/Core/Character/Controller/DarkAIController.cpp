

// ReSharper disable CppMemberFunctionMayBeConst
#include "Core/Character/Controller/DarkAIController.h"


// Sets default values
ADarkAIController::ADarkAIController()
{
	RecognitionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Recognition Area"));
	RecognitionSphere->SetupAttachment(RootComponent);
	RecognitionSphere->InitSphereRadius(PerceptionRadius);
	RecognitionSphere->SetCollisionProfileName("OverlapAllDynamic");
	RecognitionSphere->OnComponentBeginOverlap.AddDynamic(this, &ADarkAIController::OnComponentOverlap);
	PrimaryActorTick.bCanEverTick = true;
}

void ADarkAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADarkAIController::BlueprintActorRecognition_Implementation(ADarkActor* RecognizedActor) {}
void ADarkAIController::BlueprintCharacterRecognition_Implementation(ADarkCharacter* RecognizedCharacter) {}
void ADarkAIController::OnActorRecognition(ADarkActor* RecognizedActor) {}
void ADarkAIController::OnCharacterRecognition(ADarkCharacter* RecognizedCharacter) {}

void ADarkAIController::Tick(const float DeltaTime)
{
	
	Super::Tick(DeltaTime);
}

void ADarkAIController::OnComponentOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!RecognizeCharacter && !RecognizeActor) { return; }
	if (RecognizeActor)
	{
		if (ADarkActor* OtherDarkActor = Cast<ADarkActor>(OtherActor))
		{
			if (!IsWallBetween(GetWorld()->GetFirstPlayerController(), OtherDarkActor))
			{
				OnActorRecognition(OtherDarkActor);
				BlueprintActorRecognition(OtherDarkActor);
			}
		}
	}
	if (RecognizeCharacter)
	{
		if (ADarkCharacter* OtherCharacter = Cast<ADarkCharacter>(OtherActor))
		{
			if (!IsWallBetween(GetWorld()->GetFirstPlayerController(), OtherCharacter))
			{
				OnCharacterRecognition(OtherCharacter);
				BlueprintCharacterRecognition(OtherCharacter);
			}
		}
	}
}

bool ADarkAIController::IsWallBetween(AController* Controller, AActor* OtherActor) const
{
	if (Controller && OtherActor)
	{
		FVector StartLocation = Controller->GetPawn()->GetActorLocation();
		FVector EndLocation = OtherActor->GetActorLocation();

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(Controller->GetPawn());
		if (FHitResult HitResult; GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams))
		{
			return true;
		}
		return false;
	}
	return false;
}
