
#pragma once

#include "CoreMinimal.h"
#include "Core/Character/Animation/DarkCharacterAnimator.h"
#include "DarkPlayerAnimator.generated.h"

class ADarkPlayer;
/**
 * 
 */
UCLASS(Blueprintable)
class SWEEPINGDARK_API UDarkPlayerAnimator : public UDarkCharacterAnimator
{
	GENERATED_BODY()
private:
	UPROPERTY(Transient)
	ADarkPlayer* DarkPlayer;
public:
	
	void InitializePlayerAnimationComponent(ADarkPlayer* DarkPlayer);
};
