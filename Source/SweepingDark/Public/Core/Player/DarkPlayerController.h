
#pragma once

#include "CoreMinimal.h"
#include "DarkPlayer.h"
#include "InputActionValue.h"
#include "GameFramework/Controller.h"
#include "DarkPlayerController.generated.h"


UCLASS()
class SWEEPINGDARK_API ADarkPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void Landed(const FHitResult& Hit);
	
	UPROPERTY(Transient)
	ADarkPlayer* DarkPlayer;
	
public:
	ADarkPlayerController();

	void SetDarkPlayer(ADarkPlayer* Player);

	void SetupInput(UInputComponent* PlayerInputComponent);
	UFUNCTION(BlueprintCallable, Category = "Dark|Character|Player", DisplayName = "Get Is Stuck In Actor")
	bool GetIsStuck() const;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dark|Character|Player", DisplayName = "Directionality")
	FVector2D Directionality;
	
	UFUNCTION(BlueprintCallable, Category = "Dark|Character|Player", DisplayName = "Get Directionality")
	FVector2D GetDirectionality() const;

	UFUNCTION(BlueprintCallable, Category = "Dark|Character|Player", DisplayName = "Set Directionality")
	FVector2D SetDirectionality() const;
	
	UFUNCTION(BlueprintCallable, Category = "Dark|Character|Player|Controller", DisplayName = "Get Is Holding Move")
	bool GetIsHoldingMove() const;
	
	UFUNCTION(BlueprintCallable, Category = "Dark|Character|Player|Controller", DisplayName = "Get Is Holding Run")
	bool GetIsHoldingRun() const;
	
	/*A Ghost hold appear when the player presses two buttons which equalize themself.*/
	UFUNCTION(BlueprintCallable, Category = "Dark|Character|Player|Controller", DisplayName = "Get Is Ghost Hold")
	bool GetIsGhostHold() const;

	bool ActiveLocomotion;

private:
	void Pitch(const float AxisValue);
	void Yaw(const float AxisValue);

	void Forward(const float AxisValue);
	void Right(const float AxisValue);
		
	bool HoldingRun;

	bool Grounded;

	bool Jumped;
	
	bool GroundedInitializable;
protected:
	void PressJump();
	void ReleaseJump();
                                   
	void PressRun();
                                   	
	void ReleaseRun();
	
private:
	void PressW();
	void PressA();
	void PressS();
	void PressD();
	void ReleaseW();
	void ReleaseA();
	void ReleaseS();
	void ReleaseD();
	bool HoldingW;
	bool HoldingA;
	bool HoldingS;
	bool HoldingD;
};
