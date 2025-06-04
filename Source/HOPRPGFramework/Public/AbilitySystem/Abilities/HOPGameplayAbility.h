// Taimoor Rehman Siddiqui All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "HopTypes/HopEnumTypes.h"
#include "HOPGameplayAbility.generated.h"

class UHopPawnCombatComponent;
class UHOPAbilitySystemComponent;

UENUM(BlueprintType)
enum class EHOPAbilityActivationPolicy : uint8 {

	OnTriggered,
	OnGiven
};
/**
 * 
 */
UCLASS()
class HOPRPGFRAMEWORK_API UHOPGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	//~ Begin UGameplayAbility Interface.
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface.

	/** The activation policy for this ability. */
	UPROPERTY(EditDefaultsOnly, Category = "HOP|Ability")
	EHOPAbilityActivationPolicy AbilityActivationPolicy = EHOPAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "HOP|Ability")
	UHopPawnCombatComponent* GetHOPPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "HOP|Ability")
	UHOPAbilitySystemComponent* GetHOPAbilitySystemComponentFromActorInfo() const;

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "HOP|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EHopSuccessType& OutSuccessType);
	
};
