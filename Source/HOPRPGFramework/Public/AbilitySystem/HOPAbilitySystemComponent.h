// Taimoor Rehman Siddiqui All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "HopTypes/HopStructTypes.h"
#include "HOPAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class HOPRPGFRAMEWORK_API UHOPAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	UFUNCTION(BlueprintCallable, Category = "HOP|Ability", meta = (ApplyLevel = "1"))
	void GrantHeroWeaponAbilities(const TArray<FHopHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedSpecHandles);

	UFUNCTION(BlueprintCallable, Category = "HOP|Ability")
	void RemoveGrantedHeroWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);

	UFUNCTION(BlueprintCallable, Category = "HOP|Ability")

	// This function will activate the ability with the given tag if it is not already active
	bool TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate);

	
};
