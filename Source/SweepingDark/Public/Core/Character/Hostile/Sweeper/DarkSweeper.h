// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Core/Character/DarkCharacter.h"
#include "DarkSweeper.generated.h"

UCLASS()
class SWEEPINGDARK_API ADarkSweeper : public ADarkCharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, DisplayName = "Cold Point Collision")
	USphereComponent* ColdPoint;
	UPROPERTY(VisibleAnywhere, DisplayName = "Hot Point Left Collision")
	UCapsuleComponent* HotPointLeft;
	UPROPERTY(VisibleAnywhere, DisplayName = "Hot Point Right Collision")
	UCapsuleComponent* HotPointRight;

	
	
public:
	// Sets default values for this character's properties
	ADarkSweeper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
