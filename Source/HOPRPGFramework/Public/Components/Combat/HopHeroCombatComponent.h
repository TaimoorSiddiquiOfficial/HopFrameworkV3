// Taimoor Rehman Siddiqui All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/HopPawnCombatComponent.h"
#include "HopHeroCombatComponent.generated.h"

class AHopHeroWeapon;

/**
 * 
 */
UCLASS()
class HOPRPGFRAMEWORK_API UHopHeroCombatComponent : public UHopPawnCombatComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "HOPRPG|Combat")
	AHopHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "HOPRPG|Combat")
	AHopHeroWeapon* GetHeroCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "HOPRPG|Combat")
	float GetHeroCurrentEquippWeaponDamageAtLevel(float InLevel) const;

	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;
	
};
