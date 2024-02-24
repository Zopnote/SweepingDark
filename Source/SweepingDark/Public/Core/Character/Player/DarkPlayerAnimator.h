
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
	
public:
	UPROPERTY(Transient)
	ADarkPlayer* DarkPlayer;
	void InitializePlayerAnimationComponent(ADarkPlayer* InitDarkPlayer);
	virtual void Tick(const float Delta) override;
};
