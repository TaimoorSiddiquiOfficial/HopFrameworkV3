// Taimoor Rehman Siddiqui All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/HopBaseAnimInstance.h"
#include "HopHeroLinkedAnimLayer.generated.h"

class UHopHeroAnimInstance;
/**
 * 
 */
UCLASS()
class HOPRPGFRAMEWORK_API UHopHeroLinkedAnimLayer : public UHopBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UHopHeroAnimInstance* GetHeroAnimInstance() const;
};
