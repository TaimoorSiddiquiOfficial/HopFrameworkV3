// Taimoor Rehman Siddiqui All Right Reserved


#include "DataAssets/StartUpData/HOPDataAsset_StartUpDataBase.h"
#include "AbilitySystem/HOPAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/HOPGameplayAbility.h"

void UHOPDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UHOPAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);

	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);

	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);

	if (!StartUpGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf < UGameplayEffect >& EffectClass : StartUpGameplayEffects)
		{
			if (!EffectClass) continue;

			UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>();

			InASCToGive->ApplyGameplayEffectToSelf(
				EffectCDO,
				ApplyLevel,
				InASCToGive->MakeEffectContext()
			);
		}
	}
}

void UHOPDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UHOPGameplayAbility>>& InAbilitiesToGive, UHOPAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}
	for (const TSubclassOf<UHOPGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;
		
		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		InASCToGive->GiveAbility(AbilitySpec);
		
	}
}
