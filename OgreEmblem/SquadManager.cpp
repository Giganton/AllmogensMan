#include "SquadManager.h"
#include<vector>
#include <SFML/Graphics.hpp>

SquadManager::SquadManager(Flag* flag, IdCreator* sqdCreator)
{
	managedFlag = flag;
	idCreator = sqdCreator;

	//activate();
}

/*void SquadManager::activate()
{
	closeMe = false; 
	squadBrowser = BrowseSquadsState(this, 1); 
}*/

/*void SquadManager::handleInput(sf::Event keyPress)
{
	squadBrowser.receiveInput(keyPress);
	if (squadBrowser.shouldBeClosed())
	{

	}
}*/

void SquadManager::disbandSquad(DisbandSquadCommand command)
{
	managedFlag->disbandSquad(command.squadID);
}

/*void SquadManager::compileVisualStack(GraphicsInterface* gInt)
{
	squadBrowser.compileVisualStack(gInt);
}*/