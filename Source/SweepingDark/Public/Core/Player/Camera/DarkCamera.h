#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DarkCamera.generated.h"

class ADarkPlayer;

UENUM(BlueprintType)
enum class EDarkCameraModes : uint8
{
	ThirdPerson,
	Isometric,
	SideScroller
};

UCLASS()
class SWEEPINGDARK_API UDarkCamera : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, DisplayName = "Camera Mode", Category = "Menria|Character|Player|Camera")
	EDarkCameraModes CameraMode;

	UPROPERTY(VisibleAnywhere, DisplayName = "Field Of View", Category = "Menria|Character|Player|Camera")
	float FieldOfView;

	UPROPERTY(VisibleAnywhere, DisplayName = "Distance To Player", Category = "Menria|Character|Player|Camera")
	float DistanceToPlayer;

};
