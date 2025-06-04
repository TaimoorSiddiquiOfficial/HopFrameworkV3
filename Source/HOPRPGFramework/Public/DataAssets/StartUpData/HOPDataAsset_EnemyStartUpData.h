// Taimoor Rehman Siddiqui All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/HOPDataAsset_StartUpDataBase.h"
#include "HOPDataAsset_EnemyStartUpData.generated.h"


class UHOPEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class HOPRPGFRAMEWORK_API UHOPDataAsset_EnemyStartUpData : public UHOPDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UHOPAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "HOPStartUpData")
	TArray< TSubclassOf<UHOPEnemyGameplayAbility> > EnemyCombatAbilities;

	
};
