// Taimoor Rehman Siddiqui All Right Reserved


#include "AbilitySystem/Abilities/HOPGameplayAbility.h"
#include "AbilitySystem/HOPAbilitySystemComponent.h"
#include "Components/Combat/HopPawnCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

void UHOPGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == EHOPAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive()) 
		{
			// Activate the ability immediately
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
		

	}
}

void UHOPGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	if (AbilityActivationPolicy == EHOPAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UHopPawnCombatComponent* UHOPGameplayAbility::GetHOPPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UHopPawnCombatComponent>();
	
}

UHOPAbilitySystemComponent* UHOPGameplayAbility::GetHOPAbilitySystemComponentFromActorInfo() const
{
	return Cast<UHOPAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
	
}

FActiveGameplayEffectHandle UHOPGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	check(TargetASC && InSpecHandle.IsValid());

	return GetHOPAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*InSpecHandle.Data,
		TargetASC

	);

	
}

FActiveGameplayEffectHandle UHOPGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EHopSuccessType& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);

	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? EHopSuccessType::Successful : EHopSuccessType::Failed;

	return ActiveGameplayEffectHandle;
}
