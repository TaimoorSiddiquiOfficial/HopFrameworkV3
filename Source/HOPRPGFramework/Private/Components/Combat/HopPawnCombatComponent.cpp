// Taimoor Rehman Siddiqui All Right Reserved


#include "Components/Combat/HopPawnCombatComponent.h"
#include "Items/Weapons/HopWeaponBase.h"
#include "Components/BoxComponent.h"
#include "HOPDebugHelper.h"

void UHopPawnCombatComponent::RegiterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AHopWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A Named Named %s has already been added as carried weapon"), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister);

	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromTargetActor);

	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}

	//Debug
	/*const FString WeaponString = FString::Printf(TEXT("Weapon %s has been registered as carried weapon"), *InWeaponToRegister->GetName(), *InWeaponTagToRegister.ToString());
	Debug::Print(WeaponString);*/
}

AHopWeaponBase* UHopPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if (AHopWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
		{
			return *FoundWeapon;
		}
	}
	return nullptr;
}



AHopWeaponBase* UHopPawnCombatComponent::GetCharcterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}
	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UHopPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		AHopWeaponBase* WeaponToToggle = GetCharcterCurrentEquippedWeapon();

		check(WeaponToToggle);

		if (bShouldEnable)
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			/*Debug::Print(WeaponToToggle->GetName() + TEXT("Collision Enabled"), FColor::Green);*/
		}
		else
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			/*Debug::Print(WeaponToToggle->GetName() + TEXT("Collision Disabled"), FColor::Red);*/

			OverlappedActors.Empty();
			
		}

		

	}

	//TODO: Handle Body Collison Boxes

}

void UHopPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
}

void UHopPawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
}
