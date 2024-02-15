#pragma once

#include "CoreMinimal.h"
#include "DarkAnimationState.h"
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
	
public:
	UPROPERTY(BlueprintReadWrite, DisplayName = "Character")
	TObjectPtr<ADarkCharacter> Character;
	
	UPROPERTY(EditAnywhere)
	TArray<class UDarkAnimationState*> AnimationStates;

	UFUNCTION(BlueprintCallable, DisplayName = "Get Animation State")
	UDarkAnimationState* GetAnimationState(const FString& Name);

	UFUNCTION(BlueprintCallable, DisplayName = "Tick Animation")
	void Tick(float DeltaSeconds);
};
