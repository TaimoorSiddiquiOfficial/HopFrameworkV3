// Taimoor Rehman Siddiqui All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/HopPawnCombatComponent.h"
#include "HopEnemyCombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class HOPRPGFRAMEWORK_API UHopEnemyCombatComponent : public UHopPawnCombatComponent
{
	GENERATED_BODY()

public:
	virtual void OnHitTargetActor(AActor* HitActor) override;

protected:
	virtual void ToggleBodyCollsionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType) override;
	
};
