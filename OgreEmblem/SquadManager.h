#pragma once
#include "Flag.h"
#include "Browser.h"
#include "Menu.h"
#include "CampVisualData.h"
#include "Manager.h"
#include "SquadManagerCommands.h"
#include "SquadManagerInitVisuals.h"
#include "SquadManagerState.h"
#include "GraphicsInterface.h"
#include "IdCreator.h"

enum SquadManagerMenuActions { addSquad, editSquad, removeSquad };
/*
class SquadManagerState : public ManagerState
{
private:
	Browser browserCopy;
	bool browserIsActive;
public:
};*/

class SquadManager
{
private:
	Flag* managedFlag = nullptr;
	IdCreator* idCreator = nullptr;
	bool closeMe = false;

	//BrowseSquadsState squadBrowser;

public:
	SquadManager() {};
	SquadManager(Flag* flag, IdCreator* sqdCreator);

	//void handleInput(sf::Event keyPress);
	void disbandSquad(DisbandSquadCommand command);

	//void compileVisualStack(GraphicsInterface* gInt);
	Flag* getFlagPointer() { return managedFlag; };
	bool shouldBeClose() { return closeMe; };

	//void activate();
};