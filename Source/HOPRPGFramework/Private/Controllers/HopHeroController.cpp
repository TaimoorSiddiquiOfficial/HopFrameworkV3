// Taimoor Rehman Siddiqui All Right Reserved


#include "Controllers/HopHeroController.h"

AHopHeroController::AHopHeroController()
{
	//Began IGenericTeamAgentInterface.
	// Set the default team ID for the hero
	HeroTeamID = FGenericTeamId(0); // Default team ID
	//End IGenericTeamAgentInterface.
	
}

FGenericTeamId AHopHeroController::GetGenericTeamId() const
{
	return HeroTeamID;
}
