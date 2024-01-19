// Fill out your copyright notice in the Description page of Project Settings.


#include "SweepingDark/Public/Core/Actor/DarkActor.h"


// Sets default values
ADarkActor::ADarkActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

bool ADarkActor::GetIsStrategyObject()
{
	return false;
}

int ADarkActor::GetObjectRelevance()
{
	return 1;
}

void ADarkActor::BeginPlay()
{
	Super::BeginPlay();
	
}

