// Taimoor Rehman Siddiqui All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/HopPawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"
#include "HopPawnCombatComponent.generated.h"

class AHopWeaponBase;

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand
};

/**
 * 
 */
UCLASS()
class HOPRPGFRAMEWORK_API UHopPawnCombatComponent : public UHopPawnExtensionComponentBase
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable, Category = "HOPRPG|Combat")
	void RegiterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AHopWeaponBase* InWeaponToRegister,bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "HOPRPG|Combat")
	AHopWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UPROPERTY(BlueprintReadWrite, Category = "HOPRPG|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "HOPRPG|Combat")
	AHopWeaponBase* GetCharcterCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "HOPRPG|Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);

protected:

	virtual void ToggleCurrentEquippedWeaponCollision(bool bShouldEnable);
	virtual void ToggleBodyCollsionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType);

	TArray<AActor*> OverlappedActors;

private:
	TMap<FGameplayTag, AHopWeaponBase*> CharacterCarriedWeaponMap;
	
};
