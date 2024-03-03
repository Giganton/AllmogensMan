#include "Camp.h"

Camp::Camp(Flag* flag, IdCreator* idCrt)
{ 
	campingFlag = flag; 
	idCreator = idCrt; 
	squadManager = SquadManager(campingFlag, idCreator);
	currentMode = CampModes::mainMode; 
	//openMapBasket = mapBasket;
	//*openMapBasket = false;
	//campMenu = CampMenuState(1, this, openMapBasket);
}

Camp::Camp(const Camp& cpEQ)
{
	campingFlag = cpEQ.campingFlag;
	idCreator = cpEQ.idCreator;
	//SickBay sickBay;
	squadManager = cpEQ.squadManager;
	currentMode = cpEQ.currentMode;

	//campMenu = cpEQ.campMenu;
	//campMenu.setCampPtr(this);
}
Camp& Camp::operator=(const Camp asEQ)
{
	campingFlag = asEQ.campingFlag;
	idCreator = asEQ.idCreator;
	//SickBay sickBay;
	squadManager = asEQ.squadManager;
	currentMode = asEQ.currentMode;

	//campMenu = asEQ.campMenu;
	//campMenu.setCampPtr(this);

	return *this;
}

/*void Camp::handleInput(sf::Event keypress)
{
	switch (currentMode)
	{
	case CampModes::mainMode:
		campMenu.receiveInput(keypress);
		break;
	/*case CampModes::squadManager:
		squadManager.handleInput(keypress);
		break;*/
	/*default:
		throw new std::exception();
	}
}*/