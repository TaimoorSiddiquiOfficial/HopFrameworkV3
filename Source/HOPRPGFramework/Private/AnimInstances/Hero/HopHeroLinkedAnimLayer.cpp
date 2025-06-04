// Taimoor Rehman Siddiqui All Right Reserved


#include "AnimInstances/Hero/HopHeroLinkedAnimLayer.h"
#include "AnimInstances/Hero/HopHeroAnimInstance.h"

UHopHeroAnimInstance* UHopHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
   return Cast<UHopHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
    
}
