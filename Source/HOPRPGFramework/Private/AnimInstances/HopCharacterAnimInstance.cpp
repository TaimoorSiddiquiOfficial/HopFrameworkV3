// Taimoor Rehman Siddiqui All Right Reserved


#include "AnimInstances/HopCharacterAnimInstance.h"
#include "Character/HOPBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"



	

	void UHopCharacterAnimInstance::NativeInitializeAnimation()
	{
		// Initialize the owning character and movement component
		OwningCharacter = Cast<AHOPBaseCharacter>(TryGetPawnOwner());
		if (OwningCharacter)
		{
			OwningMovementComponent = OwningCharacter->GetCharacterMovement();

		}
	}

	void UHopCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
		// Update animation properties based on the character's state
	}

	// Update the ground speed based on the character's velocity
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	// Check if the character is accelerating
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared()> 0.f;

	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
}
