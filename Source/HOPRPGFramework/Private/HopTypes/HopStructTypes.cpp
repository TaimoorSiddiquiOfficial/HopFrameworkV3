// Taimoor Rehman Siddiqui All Right Reserved


#include "HopTypes/HopStructTypes.h"
#include "AbilitySystem/Abilities/HOPHeroGameplayAbility.h"

bool FHopHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
