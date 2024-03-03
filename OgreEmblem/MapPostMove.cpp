#include "MapPostMove.h"
#include "SquadMovedEvent.h"
#include "MapCursorEvent.h"
#include "BattleManager.h"
#include "MapFightPicker.h"

MapPostMove::MapPostMove(int id, If_BattleManager* man, CursorPos startingPos, Squad sqd, MoveData moveData, BrowserBucket* bBucket) : MapManager(id, man, startingPos)
{
	addInitEvent();
	movedSquad = sqd;
	moveToBePerformed = moveData;
	SquadMovedEvent temp1 = SquadMovedEvent(level, moveData);
	eventQueue.addEvent(&temp1);
	openMenu(createPostMoveMenu());
	passedBucket = bBucket;

	closable = true;
}

Menu MapPostMove::createPostMoveMenu()
{
	std::vector<Menu> options;
	
	if (isEnemyWithinRange(movedSquad, moveToBePerformed.path.at(moveToBePerformed.path.size() - 1)))
	{
		options.push_back(Menu("Battle", mpmMenuActions::mpm_startFight));
	}
	options.push_back(Menu("Wait", mpmMenuActions::mpm_squadWait));
	options.push_back(Menu("Back", mpmMenuActions::mpm_back));
	return Menu("eftergångsmeny", options);
}

void MapPostMove::performMenuAction(int action)
{
	switch (action)
	{
	case mpmMenuActions::mpm_startFight:
		openLink(new MapFightPicker(level + 1, bManager, cursor.getPos(), moveToBePerformed.path.at(moveToBePerformed.path.size() - 1), movedSquad, moveToBePerformed, passedBucket));
		break;
	case mpmMenuActions::mpm_squadWait:
		moveSquad();
		bManager->putToRest(movedSquad.getID());
		passedBucket->actionPerformed = true;
		passedBucket->cursor = cursor;
		closeMe = true;
		break;
	case mpmMenuActions::mpm_back:
		closeMe = true;
	default:
		break;
	}
}

void MapPostMove::pauseForAnimation()
{
	MapManager::pauseForAnimation();
	MenuEvent temp = MenuEvent(menu.getVisuals(), MenuEventType::hidden, level);
	MapCursorEvent temp2 = MapCursorEvent(level, MapCursorEventType::hide);
	eventQueue.addEvent(&temp);
	eventQueue.addEvent(&temp2);
}

void MapPostMove::animationFinished()
{
	MapManager::animationFinished();
	MenuEvent temp = MenuEvent(menu.getVisuals(), MenuEventType::shown, level);
	MapCursorEvent temp2 = MapCursorEvent(level, MapCursorEventType::show);
	eventQueue.addEvent(&temp);
	eventQueue.addEvent(&temp2);
}

void MapPostMove::moveSquad()
{
	bManager->moveSquad(moveToBePerformed);
}

void MapPostMove::preSubLevelClosing()
{
	if (passedBucket->actionPerformed)
	{
		closeMe = true;
	}
}