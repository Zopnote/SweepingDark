
#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"

#include "PaperZDCharacter.h"
#include "Components/SphereComponent.h"
#include "DarkCharacter.generated.h"

class UDarkCharacterAnimator;

UCLASS()
class SWEEPINGDARK_API ADarkCharacter : public ACharacter
{
private:
	GENERATED_BODY()
	
	UPROPERTY(Transient)
	FVector2D Directionality;
protected:
	float Health;
	bool Death;
	bool AbleDamage;
	bool AbleDamageByFire;
	bool AbleDamageByFalling;
	bool AbleDamageByDropping; // Damage by objects which falling on the Character
	bool AbleDamageByPlayer;
	bool AbleDamageByHostile;

	virtual void PostInitializeComponents() override;
	
	
	UPROPERTY(VisibleAnywhere, DisplayName = "Cold Point Collision")
	USphereComponent* HitColdPoint;
	
	UPROPERTY(VisibleAnywhere, DisplayName = "Area Point Collision")
	USphereComponent* HitAreaPoint;
	
	UPROPERTY(VisibleAnywhere, DisplayName = "Area Point Collision")
	USphereComponent* HitSuperflatPoint;
	
	UPROPERTY(VisibleAnywhere, DisplayName = "Hot Point Left Collision")
	UCapsuleComponent* HitHotPointLeft;
	
	UPROPERTY(VisibleAnywhere, DisplayName = "Hot Point Right Collision")
	UCapsuleComponent* HitHotPointRight;
	
	UPROPERTY(VisibleAnywhere, DisplayName = "Hot Point Left Collision")
	UCapsuleComponent* HitHotPointFront;
	
	UPROPERTY(VisibleAnywhere, DisplayName = "Hot Point Right Collision")
	UCapsuleComponent* HitHotPointBack;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dark|Character|Animation", DisplayName = "Animation Component")
	TSubclassOf<UDarkCharacterAnimator> CharacterAnimationComponent;
	
public:
	UPROPERTY(VisibleAnywhere, Category = "Dark|Character", DisplayName = "Sprite")
	TObjectPtr<UPaperFlipbookComponent> Sprite;
	
	UPROPERTY(VisibleAnywhere, Category = "Dark|Character", DisplayName = "Inversed Sprite")
	TObjectPtr<UPaperFlipbookComponent> InversedSprite;
	
	explicit ADarkCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	float WalkingSpeed;
	float RunningSpeed;

	UFUNCTION(BlueprintCallable, Category = "Dark|Character", DisplayName = "Set Directionality")
	bool SetDrectionality(FVector2D NewDirection);
	
	UFUNCTION(BlueprintCallable, Category = "Dark|Character", DisplayName = "Get Directionality")
	FVector2D GetDrectionality() const;
	
protected:
	virtual void BeginPlay() override;
	virtual void WhenDirectionalityChanged(FVector2D OldDirection, FVector2D NewDirection);
	virtual void WhenScalarDegreeChanged(float Degree, bool RightAxisValue);
	virtual void Tick(float DeltaSeconds) override;

};
