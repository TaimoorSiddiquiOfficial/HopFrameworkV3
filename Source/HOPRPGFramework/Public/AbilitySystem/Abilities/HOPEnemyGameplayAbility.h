// Taimoor Rehman Siddiqui All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/HOPGameplayAbility.h"
#include "HOPEnemyGameplayAbility.generated.h"

class AHopEnemyCharacter;
class UHopEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class HOPRPGFRAMEWORK_API UHOPEnemyGameplayAbility : public UHOPGameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "HOP|Ability")
	AHopEnemyCharacter* GetEnemyCharacterFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "HOP|Ability")
	UHopEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "HOP|Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat);

private:
	// Cached reference to the enemy character

	TWeakObjectPtr<AHopEnemyCharacter> CachedHopEnemyCharacter;
};

