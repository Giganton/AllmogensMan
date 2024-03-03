#include "MapSquadMover.h"
#include "BattleManager.h"
#include "MovementDotsEvent.h"
#include "MovementTargetCrossEvent.h"
#include "SquadMovedEvent.h"
#include "MapPostMove.h"


MapSquadMover::MapSquadMover(int id, If_BattleManager* man, CursorPos startingPos, Squad sqd, BrowserBucket* pBucket) : MapManager(id, man, startingPos)
{ 
	squadToMove = sqd; 
	stage = MovementStage(squadToMove, MapCoord(startingPos.x, startingPos.y));
	passedBucket = pBucket;

	closable = true;
	addInitEvent();
}
void MapSquadMover::handleXPress()
{
	if (bManager->getBattleField().doesHoveredExist(cursor))
	{
		if (bManager->getBattleField().isHoveredEmpty(cursor))
		{
			if (stage.isExecutable())
			{
				openMenu(createMapMenu());
				if (!stage.isDisconnected())
				{
					MovementTargetCrossEvent temp = MovementTargetCrossEvent(level, stage.getPath().at(stage.getPath().size() - 1));
					eventQueue.addEvent(&temp);
				}
			}
		}
		else
		{
			openMenu(createSquadMenu());
		}
	}
	else
	{
		throw new std::exception();
	}
}

Menu MapSquadMover::createMapMenu()
{
	std::vector<Menu> options;

	options.push_back(Menu("Move", msmMenuActions::msm_moveSquad));
	options.push_back(Menu("Tillbaka", msmMenuActions::msm_closeMenu));
	return Menu("Kartmeny", options);
}

Menu MapSquadMover::createSquadMenu()
{
	std::vector<Menu> options;

	options.push_back(Menu("Info", msmMenuActions::msm_openStatusScreen));
	options.push_back(Menu("Tillbaka", msmMenuActions::msm_closeMenu));
	return Menu("gruppmeny", options);
}

void MapSquadMover::performMenuAction(int action)
{
	MoveData mData;
	MovementTargetCrossEvent temp;
	switch (action)
	{
	case msmMenuActions::msm_moveSquad:
		mData = bManager->peekMoveSquad(stage.getMoveData());
		closeMenu();
		openLink(new MapPostMove(level + 1, bManager, CursorPos(mData.path.at(mData.path.size() - 1).getX(), mData.path.at(mData.path.size() - 1).getY()), squadToMove, mData, passedBucket));
		break;
	case msmMenuActions::msm_closeMenu:
		closeMenu();
		break;
	}

}

void MapSquadMover::uponCursorMove()
{
	MapCoord coord = MapCoord(cursor.getPos().x, cursor.getPos().y);
	int stepCost = bManager->getBattleField().getMovementCost(stage.getLastStep(), coord, squadToMove);
	stage.tryCoord(coord, bManager->getBattleField().canIPassHere(coord, squadToMove), bManager->getBattleField().canIStandHere(coord, squadToMove), stepCost);
}

void MapSquadMover::preSubLevelClosing()
{
	if (passedBucket->actionPerformed)
	{
		closeMe = true;
	}
}

void MapSquadMover::collectEvents()
{
	StructuredEventQueue stageQueue = stage.pullEvents();
	while (!stageQueue.isEmpty())
	{
		StructuredEvent* stageEvent = stageQueue.pop();
		stageEvent->setLayer(level);
		eventQueue.addEvent(stageEvent);
		delete stageEvent;
	}
}

void MapSquadMover::atMenuClosing()
{
	closable = true;
	if (!stage.isDisconnected())
	{
		MovementTargetCrossEvent temp = MovementTargetCrossEvent(level);
		eventQueue.addEvent(&temp);
	}
}