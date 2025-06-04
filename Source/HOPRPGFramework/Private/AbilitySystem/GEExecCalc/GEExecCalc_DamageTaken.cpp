// Taimoor Rehman Siddiqui All Right Reserved


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/HOPAttributeSet.h"
#include "HopGameplayTags.h"

#include "HOPDebugHelper.h"

struct FHopDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FHopDamageCapture()
	{
		// Capture the AttackPower attribute from the source of the effect
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHOPAttributeSet, AttackPower, Source, false);
		// Capture the DefensePower attribute from the target of the effect
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHOPAttributeSet, DefensePower, Target, false);
		// Capture the DamageTaken attribute from the target of the effect
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHOPAttributeSet, DamageTaken, Target, false);
		
	}
};

static const FHopDamageCapture& GetHopDamageCapture()
{
	static FHopDamageCapture HopDamageCapture;
	return HopDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	/*Slow Way to Doing Capture*/
	//FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
	//	UHOPAttributeSet::StaticClass(),
	//	GET_MEMBER_NAME_CHECKED(UHOPAttributeSet, AttackPower)
	//);

	//FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(
	//	AttackPowerProperty,
	//	EGameplayEffectAttributeCaptureSource::Source,
	//	false // This is a source attribute, not a target attribute

	//);
	//RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition);

	RelevantAttributesToCapture.Add(GetHopDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetHopDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetHopDamageCapture().DamageTakenDef);

}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	//EffectSpec.GetContext().GetSourceObject();
	//EffectSpec.GetContext().GetAbility();
	//EffectSpec.GetContext().GetInstigator();
	//EffectSpec.GetContext().GetEffectCauser();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetHopDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);
	
	/*Debug::Print(TEXT("SourceAttackPower"), SourceAttackPower);*/

	float BaseDamage = 0.f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;


	// Check if the effect spec has any SetByCaller tag magnitudes
	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(HopGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;	
			/*Debug::Print(TEXT("BaseDamage"), BaseDamage);*/
		}
		if (TagMagnitude.Key.MatchesTagExact(HopGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
			/*Debug::Print(TEXT("UsedLightAttackComboCount"), UsedLightAttackComboCount);*/
		}
		if (TagMagnitude.Key.MatchesTagExact(HopGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
			/*Debug::Print(TEXT("UsedHeavyAttackComboCount"), UsedHeavyAttackComboCount);*/
		}
	}

	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetHopDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);
	/*Debug::Print(TEXT("TargetDefensePower"), TargetDefensePower);*/

	if (UsedLightAttackComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.05f + 1.f ;

		BaseDamage *= DamageIncreasePercentLight;
		/*Debug::Print(TEXT("ScaledBaseDamageLight"), BaseDamage);*/
	}

	if (UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = UsedHeavyAttackComboCount * 0.15f + 1.f;
		BaseDamage *= DamageIncreasePercentHeavy;
		/*Debug::Print(TEXT("ScaledBaseDamageHeavy"), BaseDamage);*/
	}

	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;
	//Debug::Print(TEXT("FinalDamageDone"), FinalDamageDone);

	if (FinalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
			GetHopDamageCapture().DamageTakenProperty,
			EGameplayModOp::Override,
			FinalDamageDone
		));
	}

}
