#pragma once

#include "CoreMinimal.h"
#include "DarkAnimationState.h"
#include "DarkCharacterChase.h"
#include "Core/Character/DarkCharacter.h"
#include "UObject/Object.h"
#include "DarkCharacterAnimator.generated.h"

/**
 * 
*/

UCLASS(Blueprintable)
class SWEEPINGDARK_API UDarkCharacterAnimator : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, DisplayName = "Character", VisibleAnywhere)
	TObjectPtr<ADarkCharacter> Character;
	
private:
	UPROPERTY(Transient)
	int CurrentCharacterChase;
	
public:

	UPROPERTY(Transient)
	FString CurrentAnimationState;

	void SetCurrentCharacterChase(EDarkCharacterChase CharacterChase);

	int GetCurrentCharacterChase();
	
	UFUNCTION(BlueprintCallable)
	void SetCharacter(ADarkCharacter* NewCharacter);

	UFUNCTION(BlueprintCallable)
	void SetSprite(UPaperFlipbookComponent* PaperFlipbookComponent, UDarkAnimationState* AnimationState);
	
	UFUNCTION(BlueprintCallable)
	ADarkCharacter* GetCharacter() const;

	UFUNCTION(BlueprintCallable)
	void SetAnimationState(UDarkAnimationState* NewAnimationState, EDarkCharacterChase NewCharacterChase);

	UFUNCTION(BlueprintCallable)
	virtual void WhenAnimationStateChange(UDarkAnimationState* OldAnimationState, UDarkAnimationState* NewAnimationState);
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UDarkAnimationState>> AnimationStates;

	UFUNCTION(BlueprintCallable, DisplayName = "Get Animation State")
	UDarkAnimationState* GetAnimationState(const FString& Name);

	UFUNCTION(BlueprintCallable, DisplayName = "Tick Animation")
	void Tick(float DeltaSeconds);

	void MultipleActorVectorsChange(EDarkCharacterChase CharacterChase);
	
	void ActorDirectionalityChange(FVector2D AxisValue);
};
 