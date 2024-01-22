// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/SphereComponent.h"
#include "Core/Actor/DarkActor.h"
#include "Core/Character/DarkCharacter.h"
#include "DarkAIController.generated.h"

UCLASS()
class SWEEPINGDARK_API ADarkAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADarkAIController();

protected:
	
	UPROPERTY(EditAnywhere, DisplayName = "Perception Radius", Category = "Menria|Character|Controller")
	float PerceptionRadius; // Radius where other actors will be recognized.
	
	UPROPERTY(EditAnywhere, DisplayName = "Recognize Dark Character", Category = "Menria|Character|Controller")
	bool RecognizeCharacter; // Should the character recognize characters in the perception radius.
	
	UPROPERTY(EditAnywhere, DisplayName = "Recognize Dark Actor", Category = "Menria|Character|Controller")
	bool RecognizeActor; // Should the character recognize actors in the perception radius.
	
	UPROPERTY(EditAnywhere, DisplayName = "Enemy Dark Characters", Category = "Menria|Character|Controller")
	TArray<ADarkCharacter*> EnemyDarkCharacters;
	
	UPROPERTY(EditAnywhere, DisplayName = "Recognize Dark Actors", Category = "Menria|Character|Controller")
	TArray<ADarkActor*> RecognizeDarkActors;
	
	UPROPERTY(EditAnywhere, DisplayName = "Sedentary", Category = "Menria|Character|Controller")
	bool Sedentary; // Should the character move around its Settlement. If false the character will walk randomly through the world.
	
	UPROPERTY(EditAnywhere, DisplayName = "Settlement", Category = "Menria|Character|Controller")
	FVector Settlement; // Location in map where the character should be.
	
	UPROPERTY(EditAnywhere, DisplayName = "Sedentary Movement Radius", Category = "Menria|Character|Controller")
	float SedentaryMovementRadius; // The radius around the Settlement where the character walk when Sedentary on is.

	UPROPERTY(Transient, DisplayName = "Controlled Character Instance")
	ADarkCharacter* ControlledCharacter;
	
	UPROPERTY(VisibleAnywhere, DisplayName = "Recognition Sphere", Category = "Menria|Character|Controller")
	USphereComponent* RecognitionSphere;

	UFUNCTION(DisplayName = "Is Wall Between", Blueprintable)
	bool IsWallBetween(AController* Controller, AActor* OtherActor) const;

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Actor Recognition", Category = "Menria|Character|Controller")
	void OnActorRecognition(ADarkActor* RecognizedActor);
	
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Character Recognition", Category = "Menria|Character|Controller")
	void OnCharacterRecognition(ADarkCharacter* RecognizedCharacter);
	
	virtual void Tick(float DeltaTime) override;
	
private:
	UFUNCTION(NotBlueprintable)
	void OnComponentOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					   int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

};
