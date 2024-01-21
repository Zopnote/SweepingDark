// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "DarkCharacter.generated.h"

UCLASS()
class SWEEPINGDARK_API ADarkCharacter : public APaperZDCharacter
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
	bool Nura;
public:
	ADarkCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
