// Taimoor Rehman Siddiqui All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Character/HOPBaseCharacter.h"
#include "GameplayTagContainer.h"
#include "HopHeroCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UHOPDataAsset_InputConfig;
struct FInputActionValue;
class UHopHeroCombatComponent;
class UHeroUIComponent;
/**
 * 
 */
UCLASS()
class HOPRPGFRAMEWORK_API AHopHeroCharacter : public AHOPBaseCharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AHopHeroCharacter();

	//~ Begin IPawnCombatInterface Interface.
	virtual UHopPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End IPawnCombatInterface Interface.

	//~ Begin IPawnUIInterface Interface.
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	//~ End IPawnUIInterface Interface.

	virtual UHeroUIComponent* GetHeroUIComponent() const override;

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Add private members here
#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HOPCombat", meta = (AllowPrivateAccess = "true"))
	UHopHeroCombatComponent* HopHeroCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UHeroUIComponent* HeroUIComponent;

#pragma endregion


#pragma region Inputs

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HOPCharacterData", meta = (AllowPrivateAccess = "true"))
	UHOPDataAsset_InputConfig* InputConfigDataAsset;

	UPROPERTY()
	FVector2D SwitchDirection = FVector2D::ZeroVector;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue);
	void Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);

#pragma endregion

public:
	FORCEINLINE UHopHeroCombatComponent* GetHopHeroCombatComponent() const { return HopHeroCombatComponent; }
};
