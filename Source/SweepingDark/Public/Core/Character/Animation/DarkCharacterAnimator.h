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

	UPROPERTY(Transient)
	FString CurrentAnimationState;
	
public:

	void SetCurrentCharacterChase(EDarkCharacterChase CharacterChase);

	int GetCurrentCharacterChase() const;
	
	UFUNCTION(BlueprintCallable)
	void SetCharacter(ADarkCharacter* NewCharacter);
	
	UFUNCTION(BlueprintCallable)
	ADarkCharacter* GetCharacter() const;

	UFUNCTION(BlueprintCallable)
	void SetAnimationState(UDarkAnimationState* NewAnimationState);
	
	UFUNCTION(BlueprintCallable, DisplayName = "Get Animation State")
	UDarkAnimationState* GetAnimationState(const FString& Name);
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UDarkAnimationState>> AnimationStates;

	void RefreshAnimationDirectionality();
	
	virtual void DirectionalRelativeCameraChange(EDarkCharacterChase CharacterChase);
	
	virtual void ActorDirectionalityChange(FVector2D AxisValue);

	
	virtual void Tick(const float Delta);
};
 