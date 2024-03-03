#pragma once
#include<vector>
#include "SquadManager.h"
#include "CampMenuState.h"
#include "GraphicsInterface.h"
#include "IdCreator.h"

class Flag;

enum class CampModes { none , mainMode, squadManager };

class Camp
{
private:
	Flag* campingFlag = nullptr;
	IdCreator* idCreator = nullptr;
	//SickBay sickBay;
	SquadManager squadManager;
	CampModes currentMode = CampModes::none;
	//bool* openMapBasket = nullptr;

	//CampMenuState campMenu;

public:
	Camp() {};
	Camp(Flag* flag, IdCreator* idCrt);

	Camp(const Camp& cpEQ);
	Camp& operator=(const Camp asEQ);

	//void handleInput(sf::Event keypress);
	//void compileVisualStack(GraphicsInterface* gInt) { campMenu.compileVisualStack(gInt); };

	SquadManager* getSquadManagerPtr() { return &squadManager; };

};