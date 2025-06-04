// Taimoor Rehman Siddiqui All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/HOPDataAsset_StartUpDataBase.h"
#include "HopTypes/HopStructTypes.h"
#include "HOPDataAsset_HeroStartUpData.generated.h"




/**
 * 
 */
UCLASS()
class HOPRPGFRAMEWORK_API UHOPDataAsset_HeroStartUpData : public UHOPDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UHOPAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;
	
private:

	UPROPERTY(EditDefaultsOnly, Category = "HOPStartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FHopHeroAbilitySet> HeroStartUpAbilitiesSets;
};
