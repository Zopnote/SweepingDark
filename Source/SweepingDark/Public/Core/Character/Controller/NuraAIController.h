// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NuraAIController.generated.h"

UCLASS()
class SWEEPINGDARK_API ANuraAIController : public AAIController
{
	GENERATED_BODY()

public:
	ANuraAIController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
