// Taimoor Rehman Siddiqui All Right Reserved


#include "DataAssets/StartUpData/HOPDataAsset_EnemyStartUpData.h"
#include "AbilitySystem/HOPAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/HOPEnemyGameplayAbility.h"

void UHOPDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UHOPAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	if (!EnemyCombatAbilities.IsEmpty())
	{
		for (const TSubclassOf<UHOPEnemyGameplayAbility>& AbilityClass : EnemyCombatAbilities)
		{
			if (!AbilityClass) continue;

			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;

			InASCToGive->GiveAbility(AbilitySpec);

		}
	}
}
