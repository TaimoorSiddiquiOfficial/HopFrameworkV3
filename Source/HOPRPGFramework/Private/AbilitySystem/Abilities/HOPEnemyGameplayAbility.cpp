// Taimoor Rehman Siddiqui All Right Reserved


#include "AbilitySystem/Abilities/HOPEnemyGameplayAbility.h"
#include "Character/HopEnemyCharacter.h"
#include "AbilitySystem/HOPAbilitySystemComponent.h"
#include "Components/Combat/HopEnemyCombatComponent.h"
#include "HopGameplayTags.h"

AHopEnemyCharacter* UHOPEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedHopEnemyCharacter.IsValid())
	{
		CachedHopEnemyCharacter = Cast<AHopEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}
    return CachedHopEnemyCharacter.IsValid()? CachedHopEnemyCharacter.Get() : nullptr;
}

UHopEnemyCombatComponent* UHOPEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetHopEnemyCombatComponent();
}

FGameplayEffectSpecHandle UHOPEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
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
		InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel())
	);

	return EffectSpecHandle;
}
