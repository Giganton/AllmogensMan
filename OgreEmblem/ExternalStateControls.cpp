#include "ExternalStateControls.h"

ExternalStateControls compoundControls(ExternalStateControls c1, ExternalStateControls c2)
{
	ExternalStateControls retVal;
	retVal.startNextBattle = c1.startNextBattle || c2.startNextBattle;
	retVal.openCampScreen = c1.openCampScreen || c2.openCampScreen;

	return retVal;
}