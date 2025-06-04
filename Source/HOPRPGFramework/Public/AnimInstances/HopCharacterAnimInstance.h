// Taimoor Rehman Siddiqui All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/HopBaseAnimInstance.h"
#include "HopCharacterAnimInstance.generated.h"

class AHOPBaseCharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class HOPRPGFRAMEWORK_API UHopCharacterAnimInstance : public UHopBaseAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UPROPERTY()
	AHOPBaseCharacter* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "HOPAnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "HOPAnimData|LocomotionData")
	bool bHasAcceleration;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "HOPAnimData|LocomotionData")
	float LocomotionDirection;
};
