
#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"

#include "DarkPlayer.generated.h"

class ADarkPlayerController;

UCLASS()
class SWEEPINGDARK_API ADarkPlayer : public APaperZDCharacter
{
	GENERATED_BODY()

	float WalkingSpeed = 350.0f;

	float RunningSpeed = 700.0f;
	
	UPROPERTY(VisibleAnywhere, Category = Controller)
	ADarkPlayerController* PlayerController;

	
public:
	
	ADarkPlayer();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Menria|Character|Player", DisplayName = "Directionality")
	FVector2D Directionality;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
protected:
	
	UPROPERTY(EditAnywhere, DisplayName = "Attack Able", Category = "Menria|Character")
	bool AttackAble;

	virtual void BeginPlay() override;

};
