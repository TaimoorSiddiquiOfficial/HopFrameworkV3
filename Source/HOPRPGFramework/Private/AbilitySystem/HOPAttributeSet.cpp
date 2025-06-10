// Taimoor Rehman Siddiqui All Right Reserved


#include "AbilitySystem/HOPAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "HopFunctionLibrary.h"
#include "HopGameplayTags.h"
#include "Interfaces/PawnUIInterface.h"
#include "Components/UI/PawnUIComponent.h"
#include "Components/UI/HeroUIComponent.h"

#include "HOPDebugHelper.h"

UHOPAttributeSet::UHOPAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}

void UHOPAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());

		
	}
	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPawnUIInterface "), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent(); 

	checkf(PawnUIComponent, TEXT("Couldn't Extract a PawnUIComponent from %s "),*Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(),0.f,GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth()/ GetMaxHealth());
	}
	
	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());
		SetCurrentRage(NewCurrentRage);

		if (GetCurrentRage() == GetMaxRage())
		{
			UHopFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), HopGameplayTags::Player_Status_Rage_Full);
		}
		else if (GetCurrentRage() == 0.f)
		{
			UHopFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), HopGameplayTags::Player_Status_Rage_None);
		}
		else
		{
			UHopFunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), HopGameplayTags::Player_Status_Rage_Full);
			UHopFunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), HopGameplayTags::Player_Status_Rage_None);
		}

		if (UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
		{
			HeroUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());
		}
	

		if (UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
		{
			HeroUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());
		}
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();
		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		//const FString DebugString = FString::Printf(
		//	TEXT("Old Health: %f, DamageDone: %f NewCurrentHealth: %f"),
		//	OldHealth,
		//	DamageDone,
		//	NewCurrentHealth

		//);

		//Debug::Print(DebugString, FColor::Green);



		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());


		
		if (GetCurrentHealth() == 0.f)
		{
			UHopFunctionLibrary::AddGameplayTagToActorIfNone(
				Data.Target.GetAvatarActor(),
				HopGameplayTags::Shared_Status_Dead
			);
			
		}
	}
}
