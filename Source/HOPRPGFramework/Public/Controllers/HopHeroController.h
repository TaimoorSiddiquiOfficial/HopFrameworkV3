// Taimoor Rehman Siddiqui All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"

#include "HopHeroController.generated.h"

/**
 * 
 */
UCLASS()
class HOPRPGFRAMEWORK_API AHopHeroController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	AHopHeroController();

	virtual FGenericTeamId GetGenericTeamId() const override;

private:
	
	FGenericTeamId HeroTeamID;
};
