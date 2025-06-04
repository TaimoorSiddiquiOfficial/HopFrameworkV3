// Taimoor Rehman Siddiqui All Right Reserved


#include "AnimInstances/HopBaseAnimInstance.h"
#include "HopFunctionLibrary.h"

bool UHopBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
    if (APawn* OwningPawn = TryGetPawnOwner())
    {
        return UHopFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
    }
	return false;
}
