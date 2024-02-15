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
	TEnumAsByte<EDarkCharacterChase> CurrentCharacterChase;
	
public:

	UPROPERTY(Transient)
	FString CurrentAnimationState;

	void SetCurrentCharacterChase(EDarkCharacterChase CharacterChase);

	int GetCurrentCharacterChase();
	
	UFUNCTION(BlueprintCallable)
	void SetCharacter(ADarkCharacter* NewCharacter);

	
	UFUNCTION(BlueprintCallable)
	ADarkCharacter* GetCharacter() const;

	UFUNCTION(BlueprintCallable)
	void SetAnimationState(UDarkAnimationState* NewAnimationState);

	UFUNCTION(BlueprintCallable)
	virtual void WhenAnimationStateChange(UDarkAnimationState* OldAnimationState, UDarkAnimationState* NewAnimationState);
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UDarkAnimationState>> AnimationStates;

	UFUNCTION(BlueprintCallable, DisplayName = "Get Animation State")
	UDarkAnimationState* GetAnimationState(const FString& Name);


	void MultipleActorVectorsChange(EDarkCharacterChase CharacterChase);
	
	void ActorDirectionalityChange(FVector2D AxisValue);
};
 