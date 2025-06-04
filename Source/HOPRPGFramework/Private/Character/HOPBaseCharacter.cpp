// Taimoor Rehman Siddiqui All Right Reserved


#include "Character/HOPBaseCharacter.h"
#include "AbilitySystem/HOPAbilitySystemComponent.h"
#include "AbilitySystem/HOPAttributeSet.h"
#include "MotionWarpingComponent.h"

// Sets default values
AHOPBaseCharacter::AHOPBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	HOPAbilitySystemComponent = CreateDefaultSubobject<UHOPAbilitySystemComponent>(TEXT("HOPAbilitySystemComponent"));

	HOPAttributeSet = CreateDefaultSubobject<UHOPAttributeSet>(TEXT("HOPAttributeSet"));

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));

}

UAbilitySystemComponent* AHOPBaseCharacter::GetAbilitySystemComponent() const
{
	return GetHOPAbilitySystemComponent();
}

UHopPawnCombatComponent* AHOPBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

UPawnUIComponent* AHOPBaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
}

void AHOPBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (HOPAbilitySystemComponent)
	{
		HOPAbilitySystemComponent->InitAbilityActorInfo(this, this);

		
		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("CharacterStartUpData is not set in the %s"), *GetName());
		

	
	}
	
}



