// Taimoor Rehman Siddiqui All Right Reserved


#include "Items/Weapons/HopHeroWeapon.h"

void AHopHeroWeapon::AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	GrantedAbilitySpecHandles = InSpecHandles;
	

}

TArray<FGameplayAbilitySpecHandle> AHopHeroWeapon::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}
