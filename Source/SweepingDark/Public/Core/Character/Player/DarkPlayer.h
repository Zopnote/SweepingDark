
#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Camera/DarkCamera.h"
#include "Core/Character/DarkCharacter.h"

#include "DarkPlayer.generated.h"

class ADarkPlayerController;

UCLASS()
class SWEEPINGDARK_API ADarkPlayer : public ADarkCharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Category = Controller)
	ADarkPlayerController* PlayerController;

public:
	
	ADarkPlayer();

	virtual void Landed(const FHitResult& Hit) override;
	
	bool Falling;

	UPROPERTY(VisibleAnywhere, DisplayName = "Camera Settings", Category = "Menria|Character|Player")
	UDarkCamera* CameraSettings;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	UFUNCTION(BlueprintCallable, DisplayName = "Get Controller", Category = "Menria|Character|Player")
	ADarkPlayerController* GetDarkController() const;
	
	UFUNCTION(BlueprintNativeEvent, Category = "Menria|Character|Player", DisplayName = "When Falling")
	void WhenFalling();
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, DisplayName = "Attack Able", Category = "Menria|Character")
	bool AttackAble;


};
