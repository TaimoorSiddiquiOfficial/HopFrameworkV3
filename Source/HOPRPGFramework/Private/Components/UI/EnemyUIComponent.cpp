// Taimoor Rehman Siddiqui All Right Reserved


#include "Components/UI/EnemyUIComponent.h"
#include "Widgets/HopWidgetBase.h"

void UEnemyUIComponent::RegisterEnemyDrawnWidget(UHopWidgetBase* InWidgetToRegister)
{
	EnemyDrawnWidgets.Add(InWidgetToRegister);
}

void UEnemyUIComponent::RemoveEnemyDrawnWidgetsIfAny()
{
	if (EnemyDrawnWidgets.IsEmpty())
	{
		return;
	}

	for (UHopWidgetBase* DrawnWidget : EnemyDrawnWidgets)
	{
		if (DrawnWidget)
		{
			DrawnWidget->RemoveFromParent();
		}
	}

	EnemyDrawnWidgets.Empty();
}
