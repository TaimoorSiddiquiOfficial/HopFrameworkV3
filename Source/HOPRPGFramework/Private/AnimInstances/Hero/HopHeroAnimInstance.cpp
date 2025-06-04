// Taimoor Rehman Siddiqui All Right Reserved


#include "AnimInstances/Hero/HopHeroAnimInstance.h"
#include "Character/HopHeroCharacter.h"

void UHopHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	// Initialize the owning hero character
	if (OwningCharacter)
	{
		OwningHeroCharacter = Cast<AHopHeroCharacter>(OwningCharacter);
	}
	
}

void UHopHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	// Add any additional logic specific to the hero character here
	// For example, you can update hero-specific animation properties or states
	if (bHasAcceleration)
	{
		IdleElapsedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElapsedTime += DeltaSeconds;
		bShouldEnterRelaxState = (IdleElapsedTime >= EnterRelaxStateThreshold);
	}
}