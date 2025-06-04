// Taimoor Rehman Siddiqui All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Interfaces/PawnUIInterface.h"
#include "HOPBaseCharacter.generated.h"

class UHOPAbilitySystemComponent;
class UHOPAttributeSet;
class UHOPDataAsset_StartUpDataBase;
class UMotionWarpingComponent;

UCLASS()
class HOPRPGFRAMEWORK_API AHOPBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHOPBaseCharacter();

	//~ Begin IAbilitySystemInterface Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface.

	//~ Begin IPawnCombatInterface Interface.
	virtual UHopPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End IPawnCombatInterface Interface.

	//~ Begin IPawnUIInterface Interface.
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	//~ End IPawnUIInterface Interface.

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HOPAbilitySystem")
	UHOPAbilitySystemComponent* HOPAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HOPAbilitySystem")
	UHOPAttributeSet* HOPAttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MotionWarping")
	UMotionWarpingComponent* MotionWarpingComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HOPCharacterData")
	TSoftObjectPtr<UHOPDataAsset_StartUpDataBase> CharacterStartUpData;


public:
	FORCEINLINE UHOPAbilitySystemComponent* GetHOPAbilitySystemComponent() const { return HOPAbilitySystemComponent; }

	FORCEINLINE UHOPAttributeSet* GetHOPAttributeSet() const { return HOPAttributeSet; }
};
