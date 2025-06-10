// Taimoor Rehman Siddiqui All Right Reserved


#include "AbilitySystem/HOPAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/HOPHeroGameplayAbility.h"
#include "HopGameplayTags.h"

void UHOPAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag)) continue;

		if (InInputTag.MatchesTag(HopGameplayTags::InputTag_Toggleable) && AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
		else
		{
			TryActivateAbility(AbilitySpec.Handle);
		}

	}
	
}

void UHOPAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid() || !InInputTag.MatchesTag(HopGameplayTags::InputTag_MustBeHeld))
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (
			AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag) &&
			AbilitySpec.IsActive()
		)
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
	} 
}

void UHOPAbilitySystemComponent::GrantHeroWeaponAbilities(const TArray<FHopHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedSpecHandles)
{
	if (InDefaultWeaponAbilities.IsEmpty())
	{
		return;
	}
	for (const FHopHeroAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		if (!AbilitySet.IsValid()) continue;
		
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant, ApplyLevel);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);

		

		OutGrantedSpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void UHOPAbilitySystemComponent::RemoveGrantedHeroWeaponAbilities(UPARAM(ref)TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	if (InSpecHandlesToRemove.IsEmpty())
	{
		return;
	}
	for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToRemove)
	{
		if (SpecHandle.IsValid())
		{
			ClearAbility(SpecHandle);
		}
		
	}
	
	InSpecHandlesToRemove.Empty();
}

bool UHOPAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
{
	check(AbilityTagToActivate.IsValid());

	TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagToActivate.GetSingleTagContainer(), FoundAbilitySpecs);

	if (!FoundAbilitySpecs.IsEmpty())
	{
		const int32 RandomAbilityIndex = FMath::RandRange(0, FoundAbilitySpecs.Num() - 1);
		FGameplayAbilitySpec* SpecToActivate = FoundAbilitySpecs[RandomAbilityIndex];

		check(SpecToActivate);

		if (!SpecToActivate->IsActive())
		{
			return TryActivateAbility(SpecToActivate->Handle);
		}
	}
	return false;
}
