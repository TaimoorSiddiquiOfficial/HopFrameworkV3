// Taimoor Rehman Siddiqui All Right Reserved


#include "Components/Combat/HopEnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "HopGameplayTags.h"
#include "HopFunctionLibrary.h"

#include "HOPDebugHelper.h"

void UHopEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);

	//TODO:: Implement Block Check
	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = UHopFunctionLibrary::NativeDoesActorHaveTag(HitActor,HopGameplayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnblockable = UHopFunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), HopGameplayTags::Enemy_Status_Unblockable);

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		bIsValidBlock = UHopFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}
	
	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	if (bIsValidBlock)
	{
		//TODO:: Handle Successful Block
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(


			HitActor,
			HopGameplayTags::Player_Event_SuccessfulBlock,
			EventData
		);

	}

	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(

			GetOwningPawn(),
			HopGameplayTags::Shared_Event_MeleeHit,
			EventData
		);
	}

}
