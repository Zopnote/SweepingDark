// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DarkActor.generated.h"

UCLASS()
class SWEEPINGDARK_API ADarkActor : public AActor
{
	GENERATED_BODY()

public:
	ADarkActor();
	bool GetIsStrategyObject();
	int GetObjectRelevance();
private:
	bool IsStrategyObject;
	int ObjectRelevance;
	
protected:
	virtual void BeginPlay() override;
};
