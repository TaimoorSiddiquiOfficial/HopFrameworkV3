// Taimoor Rehman Siddiqui All Right Reserved


#include "Character/HopHeroCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/HOPDataAsset_InputConfig.h"
#include "Components/Input/HopInputComponent.h"
#include "HopGameplayTags.h"
#include "AbilitySystem/HOPAbilitySystemComponent.h"
#include "DataAssets/StartUpData/HOPDataAsset_HeroStartUpData.h"
#include "Components/Combat/HopHeroCombatComponent.h"
#include "Components/UI/HeroUIComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "HOPDebugHelper.h"

AHopHeroCharacter::AHopHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f; // The camera follows at this distance behind the character
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f); // Camera height offset FVector(0.f, 0.f, 50.f)
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f); // Character rotation speed FRotator(0.f, 540.f, 0.f)
	GetCharacterMovement()->MaxWalkSpeed = 400.f; // Character movement speed
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f; // Character braking speed

	HopHeroCombatComponent = CreateDefaultSubobject<UHopHeroCombatComponent>(TEXT("HopHeroCombatComponent"));

	HeroUIComponent = CreateDefaultSubobject<UHeroUIComponent>(TEXT("HeroUIComponent"));
}

UHopPawnCombatComponent* AHopHeroCharacter::GetPawnCombatComponent() const
{
	return HopHeroCombatComponent;
}

UPawnUIComponent* AHopHeroCharacter::GetPawnUIComponent() const
{
	return HeroUIComponent;
}
UHeroUIComponent* AHopHeroCharacter::GetHeroUIComponent() const
{
	return HeroUIComponent;
}


void AHopHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	/*if (HOPAbilitySystemComponent && HOPAttributeSet)
	{
		const FString ASCText = FString::Printf(TEXT("Owner Actor: %s, AvatarActor: %s"), *HOPAbilitySystemComponent->GetOwnerActor()->GetActorLabel(), *HOPAbilitySystemComponent->GetAvatarActor()->GetActorLabel());
		Debug::Print(TEXT("AbilitySystemComponent are valid")+ ASCText,FColor::Green);
		Debug::Print(TEXT("AttributeSet are valid") + ASCText, FColor::Green);
	}*/

	if (!CharacterStartUpData.IsNull())
	{
		if (UHOPDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(HOPAbilitySystemComponent);
		}
	}
	
}

void AHopHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Default Mapping Context is not set in the Input Config Data Asset!"));
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UHopInputComponent* HopInputComponent = CastChecked<UHopInputComponent>(PlayerInputComponent);

	HopInputComponent->BindNativeInputAction(InputConfigDataAsset, HopGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	HopInputComponent->BindNativeInputAction(InputConfigDataAsset, HopGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);

	HopInputComponent->BindNativeInputAction(InputConfigDataAsset, HopGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Triggered, this, &ThisClass::Input_SwitchTargetTriggered);
	HopInputComponent->BindNativeInputAction(InputConfigDataAsset, HopGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Completed, this, &ThisClass::Input_SwitchTargetCompleted);

	

	HopInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
}

void AHopHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

}
void AHopHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{ 
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f,Controller->GetControlRotation().Yaw,0.f);
	//Debug::Print(FString::Printf(TEXT("MovementVector: %s"), *MovementVector.ToString()));
    if (MovementVector.Y != 0.f )
	{
		{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		
		AddMovementInput(ForwardDirection, MovementVector.Y);

		}
	}
	//Debug::Print(FString::Printf(TEXT("MovementRotation: %s"), *MovementRotation.ToString()));
	if (MovementVector.X != 0.f)
	{
		
		
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
	
		AddMovementInput(RightDirection, MovementVector.X);

	}
	



}

void AHopHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
void AHopHeroCharacter::Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue)
{
	SwitchDirection = InputActionValue.Get<FVector2D>();
}
void AHopHeroCharacter::Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		SwitchDirection.X > 0.f ? HopGameplayTags::Player_Event_SwitchTarget_Right : HopGameplayTags::Player_Event_SwitchTarget_Left,
		Data
	);
	/*Debug::Print(FString::Printf(TEXT("SwitchDirection: %s"), *SwitchDirection.ToString()));*/
}
void AHopHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	HOPAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}
void AHopHeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	HOPAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}

