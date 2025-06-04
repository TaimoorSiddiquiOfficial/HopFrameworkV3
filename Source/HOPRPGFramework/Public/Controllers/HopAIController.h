// Taimoor Rehman Siddiqui All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HopAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;

/**
 * 
 */
UCLASS()
class HOPRPGFRAMEWORK_API AHopAIController : public AAIController
{
	GENERATED_BODY()
	

public:
	// Sets default values for this actor's properties
	AHopAIController(const FObjectInitializer& ObjectInitializer);

	//Began IGenericTeamAgentInterface.
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	//End IGenericTeamAgentInterface.

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UAIPerceptionComponent* EnemyPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAISenseConfig_Sight* AISenseConfig_Sight;

	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "HOP Detour Crown Avoidance Config")
	bool bEnableDetourCrownAvoidance = true;

	UPROPERTY(EditDefaultsOnly, Category = "HOP Detour Crown Avoidance Config", meta = (EditCondition = "bEnableDetourCrownAvoidance", UIMin ="1", UIMax = "4"))
	int32 DetourCrowdAvoidanceQuality = 4;

	UPROPERTY(EditDefaultsOnly, Category = "HOP Detour Crown Avoidance Config", meta = (EditCondition = "bEnableDetourCrownAvoidance"))
	float CollisionQueryRange = 600.f;



	};
