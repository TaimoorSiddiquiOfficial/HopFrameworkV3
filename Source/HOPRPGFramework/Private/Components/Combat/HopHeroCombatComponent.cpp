// Taimoor Rehman Siddiqui All Right Reserved


#include "Components/Combat/HopHeroCombatComponent.h"
#include "Items/Weapons/HopHeroWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "HopGameplayTags.h"

#include "HOPDebugHelper.h"

AHopHeroWeapon* UHopHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AHopHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));

}

AHopHeroWeapon* UHopHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return Cast<AHopHeroWeapon>(GetCharcterCurrentEquippedWeapon());
}

float UHopHeroCombatComponent::GetHeroCurrentEquippWeaponDamageAtLevel(float InLevel) const
{
	return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UHopHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}
	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(

		GetOwningPawn(),
		HopGameplayTags::Shared_Event_MeleeHit,
		Data
		);
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		HopGameplayTags::Player_Event_HitPause,
		FGameplayEventData()
	);
}

void UHopHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		HopGameplayTags::Player_Event_HitPause,
		FGameplayEventData()
	);
	
}
