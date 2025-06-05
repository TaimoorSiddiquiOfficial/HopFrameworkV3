// Taimoor Rehman Siddiqui All Right Reserved


#include "Components/Combat/HopEnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "HopGameplayTags.h"
#include "HopFunctionLibrary.h"
#include "Character/HopEnemyCharacter.h"
#include "Components/BoxComponent.h"

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

void UHopEnemyCombatComponent::ToggleBodyCollsionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	AHopEnemyCharacter* OwningEnemyCharacter = GetOwningPawn<AHopEnemyCharacter>();

	check(OwningEnemyCharacter);

	UBoxComponent* LeftHandCollisionBox = OwningEnemyCharacter->GetLeftHandCollisionBox();
	UBoxComponent* RightHandCollisionBox = OwningEnemyCharacter->GetRightHandCollisionBox();

	check(LeftHandCollisionBox && RightHandCollisionBox);

	switch (ToggleDamageType)
	{
	case EToggleDamageType::LeftHand:
		LeftHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;

	case EToggleDamageType::RightHand:
		RightHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;

	default:
		break;
	}

	if (!bShouldEnable)
	{
		OverlappedActors.Empty();
	}
}