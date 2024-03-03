#include "MapBrowser.h"
#include "BattleManager.h"
#include "MapSquadMover.h"
#include "InitBattleMapEvent.h"
#include "MapFightPicker.h"
#include "VictoryAchievedEvent.h"

void MapBrowser::handleXPress()
{
	if (bManager->getMap().doesHoveredExist(cursor))
	{
		if (bManager->getBattleField().isHoveredEmpty(cursor))
		{
			openMenu(createMapMenu());
		}
		else
		{
			Squad hovSqd = bManager->getBattleField().getHoveredSquad(cursor);

			if (hovSqd.getFlagTag() == tagID::player)
			{
				openMenu(createPlayerUnitMenu(hovSqd, isEnemyWithinRange(hovSqd)));
			}
			else
			{
				openMenu(createEnemyUnitMenu(hovSqd));
			}
		}
	}
	else
	{
		throw new std::exception();
	}
}

Menu MapBrowser::createMapMenu()
{
	std::vector<Menu> options;

	options.push_back(Menu("Klar", mbMenuActions::endTurn));
	options.push_back(Menu("Tillbaka", mbMenuActions::closeMenu));
	return Menu("Kartmeny", options);
}

Menu MapBrowser::createPlayerUnitMenu(Squad sqd, bool enemyInRange)
{
	std::vector<Menu> options;
	if (bManager->isSquadActive(sqd.getID()) && !sqd.isDefeated())
	{
		if (sqd.getMovesLeft() > 0)
		{
			options.push_back(Menu("Flytta", mbMenuActions::initiateMoveSquad));
		}

		if (enemyInRange)
		{
			options.push_back(Menu("Strid", mbMenuActions::initiateBattle));
		}
		options.push_back(Menu("Vänta", mbMenuActions::putToRest));
	}
	options.push_back(Menu("Info", mbMenuActions::openStatusScreen));
	options.push_back(Menu("Tillbaka", mbMenuActions::closeMenu));

	return Menu("Kompismeny", options);
}

Menu MapBrowser::createEnemyUnitMenu(Squad sqd)
{
	std::vector<Menu> options;

	options.push_back(Menu("Info", mbMenuActions::openStatusScreen));
	options.push_back(Menu("Tillbaka", mbMenuActions::closeMenu));
	return Menu("Dummingmeny", options);
}

void MapBrowser::performMenuAction(int action)
{
	Squad sqd;
	switch (action)
	{
	case mbMenuActions::initiateBattle:
		sqd = bManager->getBattleField().getHoveredSquad(cursor);
		openLink(new MapFightPicker(level + 1, bManager, cursor.getPos(), bManager->getBattleField().getMapCoord(cursor), sqd, &bucket));
		break;
	case mbMenuActions::putToRest:
		sqd = bManager->getBattleField().getHoveredSquad(cursor);
		bManager->putToRest(sqd.getID());
		closeMenu();
		break;
	case mbMenuActions::endTurn:
		closeMenu();
		sendEndTurn();
		break;
	case mbMenuActions::closeMenu:
		closeMenu();
		break;
	case mbMenuActions::initiateMoveSquad:
		sqd = bManager->getBattleField().getHoveredSquad(cursor);
		openLink(new MapSquadMover(level + 1, bManager, cursor.getPos(), sqd, &bucket));
		break;
	}
}

void MapBrowser::sendEndTurn()
{
	StructuredEventQueue generatedEvents = bManager->endTurn();
	while (!generatedEvents.isEmpty())
	{
		StructuredEvent* temp = generatedEvents.pop();
		temp->setLayer(level);
		eventQueue.addEvent(temp);
		delete(temp);
	}
}


void MapBrowser::preSubLevelClosing()
{
	if (bucket.actionPerformed)
	{
		cursor = bucket.cursor;
		InitBattleMapEvent evnt = InitBattleMapEvent(level, bManager->getMap().getVisuals(), bManager->getBattleField().getSquadData(), cursor.getPos());
		eventQueue.addEvent(&evnt);
		closeMenu();
		bucket.actionPerformed = false;

		if (bManager->checkForVictory())
		{
			VictoryAchievedEvent evnt2 = VictoryAchievedEvent(level);
			eventQueue.addEvent(&evnt2);
		}
	}
}