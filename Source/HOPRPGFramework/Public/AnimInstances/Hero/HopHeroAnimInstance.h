// Taimoor Rehman Siddiqui All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/HopCharacterAnimInstance.h"
#include "HopHeroAnimInstance.generated.h"

class AHopHeroCharacter;
/**
 * 
 */
UCLASS()
class HOPRPGFRAMEWORK_API UHopHeroAnimInstance : public UHopCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "HOPAnimData|References")
	AHopHeroCharacter* OwningHeroCharacter;


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "HOPAnimData|LocomotionData")
	bool bShouldEnterRelaxState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HOPAnimData|LocomotionData")
	float EnterRelaxStateThreshold = 5.f;

	float IdleElapsedTime;
	
};
