// Taimoor Rehman Siddiqui All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HOPDataAsset_StartUpDataBase.generated.h"

class UHOPGameplayAbility;
class UHOPAbilitySystemComponent;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class HOPRPGFRAMEWORK_API UHOPDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UHOPAbilitySystemComponent* InASCToGive,int32 ApplyLevel = 1);
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "HOPStartUpData")
	TArray< TSubclassOf < UHOPGameplayAbility > > ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "HOPStartUpData")
	TArray< TSubclassOf < UHOPGameplayAbility > > ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray< TSubclassOf < UGameplayEffect > > StartUpGameplayEffects;

	void GrantAbilities(const TArray< TSubclassOf < UHOPGameplayAbility > >& InAbilitiesToGive, UHOPAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
