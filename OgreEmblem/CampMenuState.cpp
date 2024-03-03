#include "CampMenuState.h"
#include "SquadManagerEvent.h"
#include "SquadManagerState.h"
#include "Camp.h"
#include "MapBrowser.h"

CampMenuState::CampMenuState( int lvl, Camp* cmp, bool* mapBasket)
{
	level = lvl;
	camp = cmp;
	menu = createCampMenu();
	menu.activate();
	menu.setSelected(0);
	MenuVisualEvent temp = MenuVisualEvent(MenuVisualData(menu));
	CampMenuEvent event = CampMenuEvent(level, temp);
	eventQueue.addEvent(&event);

	openMapBasket = mapBasket;
	*openMapBasket = false;
	closable = false;
}

Menu CampMenuState::createCampMenu()
{
	std::vector<Menu> chList;
	chList.push_back(Menu("Leave camp", CampMenuActions::leaveCamp));
	chList.push_back(Menu("Edit squads", CampMenuActions::editSquads));

	return Menu("Main menu", chList, false);
}

void CampMenuState::handleKeyPress(sf::Event keypress)
{
	switch (keypress.key.code)
	{
	case sf::Keyboard::Z:
		closeMe = true;
		break;
	default:
		controlMenu(keypress);
	}
	MenuVisualEvent temp = MenuVisualEvent(MenuVisualData(menu));
	CampMenuEvent event = CampMenuEvent(level, temp);
	eventQueue.addEvent(&event);
}

void CampMenuState::performMenuAction(int action)
{
	OpenSquadManagerEvent temp;
	switch (action)
	{
	case CampMenuActions::editSquads:
		openSquadManager();
		//temp = OpenSquadManagerEvent(level);
		//eventQueue.addEvent(&temp);
		break;
	case CampMenuActions::leaveCamp:
		*openMapBasket = true;
		closeMe = true;
		break;
	default:
		throw new std::exception();
	}
}

void CampMenuState::openSquadManager()
{
	/*nextLevel = new BrowseSquadsState(camp->getSquadManagerPtr(), level + 1);
	middleMan = true;*/
	openLink(new BrowseSquadsState(camp->getSquadManagerPtr(), level + 1));
}

StructuredEvent* CampMenuState::getOpeningEvent()
{
	return new OpenCampMenuEvent(level - 1);
}

void CampMenuState::compileVisualStack(GraphicsInterface* gInt)
{
	//gInt->getVisualStackPointer()->addCampEvents(eventQueue);
	//gInt->getVisualStackPointer()->setCampVisibility(true);

	gInt->addEvents(eventQueue);
	eventQueue.emptyQueue();
	if (middleMan)
	{
		nextLevel->compileVisualStack(gInt);
	}
}