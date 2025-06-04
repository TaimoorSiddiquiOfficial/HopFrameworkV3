// Taimoor Rehman Siddiqui All Right Reserved


#include "DataAssets/Input/HOPDataAsset_InputConfig.h"

UInputAction* UHOPDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FHopInputActionConfig& InputActionConfig : NativeInputActions)
	{
		if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}

	return nullptr;
}


