// Taimoor Rehman Siddiqui All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/HOPGameplayAbility.h"
#include "HOPHeroGameplayAbility.generated.h"

class AHopHeroCharacter;
class AHopHeroController;
/**
 * 
 */
UCLASS()
class HOPRPGFRAMEWORK_API UHOPHeroGameplayAbility : public UHOPGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "HOP|Ability")
	AHopHeroCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "HOP|Ability")
	AHopHeroController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "HOP|Ability")
	UHopHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "HOP|Ability")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);

private:
	// Add private members here
	
	TWeakObjectPtr<AHopHeroCharacter> CachedHopHeroCharacter;
	TWeakObjectPtr<AHopHeroController> CachedHopHeroController;
};
