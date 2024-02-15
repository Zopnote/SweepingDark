// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "UObject/Object.h"
#include "DarkAnimationState.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SWEEPINGDARK_API UDarkAnimationState : public UObject
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dark|Animation", DisplayName = "Name")
	FString Name;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dark|Animation", DisplayName = "Back Animation")
	TObjectPtr<UPaperFlipbook> Back;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dark|Animation", DisplayName = "Front Animation")
	TObjectPtr<UPaperFlipbook> Front;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dark|Animation", DisplayName = "Right Animation")
	TObjectPtr<UPaperFlipbook> Right;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dark|Animation", DisplayName = "Left Animation")
	TObjectPtr<UPaperFlipbook> Left;
	
};
