
#pragma once

#include "CoreMinimal.h"
#include "DarkPlayer.h"
#include "InputActionValue.h"
#include "GameFramework/Controller.h"
#include "DarkPlayerController.generated.h"


UCLASS()
class SWEEPINGDARK_API ADarkPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;

	
	UPROPERTY(Transient, meta = (AllowPrivateAccess = "true"))
	ADarkPlayer* DarkPlayer;
	
public:
	ADarkPlayerController();

	void SetDarkPlayer(ADarkPlayer* Player);

	void SetupInput(UInputComponent* PlayerInputComponent);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
	
protected:

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);
	
	void PressJump();
                                   
	void PressRun();
                                   	
	void UnpressRun();
	
};
