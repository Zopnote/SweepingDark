// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Character/DarkCharacter.h"
#include "DarkBlacksmith.generated.h"

UCLASS()
class SWEEPINGDARK_API ADarkBlacksmith : public ADarkCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADarkBlacksmith();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
