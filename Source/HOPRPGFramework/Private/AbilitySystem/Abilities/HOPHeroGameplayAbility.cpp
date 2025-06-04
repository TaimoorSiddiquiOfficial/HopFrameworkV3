// Taimoor Rehman Siddiqui All Right Reserved


#include "AbilitySystem/Abilities/HOPHeroGameplayAbility.h"
#include "Character/HopHeroCharacter.h"
#include "Controllers/HopHeroController.h"
#include "AbilitySystem/HOPAbilitySystemComponent.h"
#include "HopGameplayTags.h"

AHopHeroCharacter* UHOPHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{

	if (!CachedHopHeroCharacter.IsValid())
	{
		CachedHopHeroCharacter = Cast<AHopHeroCharacter>(GetCurrentActorInfo()->AvatarActor);
	}
	
    return CachedHopHeroCharacter.IsValid()? CachedHopHeroCharacter.Get() : nullptr;
}

AHopHeroController* UHOPHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if (!CachedHopHeroController.IsValid())
	{
		CachedHopHeroController = Cast<AHopHeroController>(GetCurrentActorInfo()->PlayerController);
	}

	return CachedHopHeroController.IsValid() ? CachedHopHeroController.Get() : nullptr;
	
}

UHopHeroCombatComponent* UHOPHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHopHeroCombatComponent();
}

FGameplayEffectSpecHandle UHOPHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetHOPAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetHOPAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass, 
		GetAbilityLevel(), 
		ContextHandle
		
	);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		
		HopGameplayTags::Shared_SetByCaller_BaseDamage,
		InWeaponBaseDamage
	
	);

	if (InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
	}

	return EffectSpecHandle;
}
