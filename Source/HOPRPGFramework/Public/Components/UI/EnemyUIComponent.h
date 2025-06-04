// Taimoor Rehman Siddiqui All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "EnemyUIComponent.generated.h"

class UHopWidgetBase;
/**
 * 
 */
UCLASS()
class HOPRPGFRAMEWORK_API UEnemyUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RegisterEnemyDrawnWidget(UHopWidgetBase* InWidgetToRegister);
	
	UFUNCTION(BlueprintCallable)
	void RemoveEnemyDrawnWidgetsIfAny();

private:
	TArray<UHopWidgetBase*> EnemyDrawnWidgets;
};
