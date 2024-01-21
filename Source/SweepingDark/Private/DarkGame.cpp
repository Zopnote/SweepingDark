#include "SweepingDark/Public/DarkGame.h"

#include "SweepingDark/Public/Core/Character/Player/DarkPlayer.h"
#include "UObject/ConstructorHelpers.h"

ADarkGame::ADarkGame()
{
	static ConstructorHelpers::FClassFinder<ADarkPlayer> DarkPlayerBlueprintClass(TEXT("/Game/Blueprints/Character/Player/DarkPlayer_BP.DarkPlayer_BP_C"));
	if (DarkPlayerBlueprintClass.Class)
	{
		DefaultPawnClass = DarkPlayerBlueprintClass.Class;
	}
	else
	{
		DefaultPawnClass = CreateDefaultSubobject<ADarkPlayer>(TEXT("DarkPlayer"))->GetClass();
		UE_LOG(LogTemp, Error, TEXT("Fehler beim Finden der DarkPlayerBlueprintC-Klasse"));
	}
}

void ADarkGame::BeginPlay()
{
	/*Open Menu*/
	Super::BeginPlay();
}
