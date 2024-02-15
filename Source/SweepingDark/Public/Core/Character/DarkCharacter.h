
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
	GENERATED_BODY()
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
	
	UPROPERTY(VisibleAnywhere, Category = "Dark|Character", DisplayName = "Sprite")
	TObjectPtr<UPaperFlipbookComponent> Sprite;
	
	UPROPERTY(VisibleAnywhere, Category = "Dark|Character", DisplayName = "Inversed Sprite")
	TObjectPtr<UPaperFlipbookComponent> InversedSprite;
	
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
	TObjectPtr<UDarkCharacterAnimator> CharacterAnimationComponent;
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dark|Character", DisplayName = "Directionality")
	FVector2D Directionality;
	explicit ADarkCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	float WalkingSpeed;
	float RunningSpeed;
	bool SetDrectionality(FVector2D NewDirection);
	FVector2D GetDrectionality();
	
protected:
	// Called when the game starts or when spawned
	void WhenDirectionalityChanged(FVector2D OldDirection, FVector2D NewDirection);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
public:

};
