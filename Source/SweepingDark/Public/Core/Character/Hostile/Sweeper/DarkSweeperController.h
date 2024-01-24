// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Core/Character/Controller/DarkAIController.h"
#include "DarkSweeperController.generated.h"

UCLASS()
class SWEEPINGDARK_API ADarkSweeperController : public ADarkAIController
{
	GENERATED_BODY()

public:
	ADarkSweeperController();

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
};
