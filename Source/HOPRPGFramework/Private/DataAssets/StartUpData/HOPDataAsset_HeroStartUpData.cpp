// Taimoor Rehman Siddiqui All Right Reserved


#include "DataAssets/StartUpData/HOPDataAsset_HeroStartUpData.h"
#include "AbilitySystem/Abilities/HOPHeroGameplayAbility.h"
#include "AbilitySystem/HOPAbilitySystemComponent.h"




void UHOPDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UHOPAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
    Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	for (const FHopHeroAbilitySet& AbilitySet : HeroStartUpAbilitiesSets)
	{
		if (!AbilitySet.IsValid()) continue;
		
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);


		InASCToGive->GiveAbility(AbilitySpec);
		
	}
}
