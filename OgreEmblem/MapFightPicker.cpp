#include "MapFightPicker.h"
#include "BrowserBucket.h"
#include "BattleManager.h"
#include "SetAttackTargetEvent.h"
#include "ConfirmationMenuEvent.h"
#include "BattleStage.h"
#include "BattleEvent.h"
#include "UnitKilledEvent.h"
#include "LevelUpHandler.h"

MapFightPicker::MapFightPicker(int id, If_BattleManager* man, CursorPos startingPos, MapCoord sqdPos, Squad sqd, BrowserBucket* bBucket) : MapManager(id, man, startingPos)
{
	passedBucket = bBucket;
	fightingSquad = sqd;
	squadPos = sqdPos;
	targetList = man->getBattleField().allLivingEnemiesInRange(sqdPos.getX(), sqdPos.getY(), sqd.getAtkRange(), sqd.getFlagTag());
	if (targetList.empty())
	{
		throw new std::exception();
	}
	setTarget(0);

	closable = true;
}

MapFightPicker::MapFightPicker(int id, If_BattleManager* man, CursorPos startingPos, MapCoord squadNewPos, Squad sqd, MoveData moveToPerform, BrowserBucket* bBucket) : MapFightPicker(id, man, startingPos, squadNewPos, sqd, bBucket)
{
	moveToBePerformed = moveToPerform;
	alsoMoveUnit = true;
}

void MapFightPicker::setTarget(int index)
{
	currentIndex = index;
	SetAttackTargetEvent evnt = SetAttackTargetEvent(level, targetList.at(index).getID());
	eventQueue.addEvent(&evnt);
}

void MapFightPicker::rollUp()
{
	int newIndex = currentIndex - 1;
	if (newIndex < 0)
	{
		newIndex = targetList.size() - 1;
	}
	setTarget(newIndex);
}

void MapFightPicker::rollDown()
{
	int newIndex = currentIndex + 1;
	if (newIndex >= targetList.size())
	{
		newIndex = 0;
	}
	setTarget(newIndex);
}


StructuredEvent* MapFightPicker::getOpeningEvent()
{
	return new OpenBattleMapEvent(level - 1, true);
}

void MapFightPicker::controlMap(sf::Event keyPress)
{
	switch (keyPress.key.code)
	{
	case sf::Keyboard::Up:
	case sf::Keyboard::Left:
		rollUp();
		break;
	case sf::Keyboard::Down:
	case sf::Keyboard::Right:
		rollDown();
		break;
	case sf::Keyboard::X:
		openConfirmationWindow("Fight?");
		break;
	}
}

void MapFightPicker::selectionAction()
{
	ConfirmationMenuEvent temp = ConfirmationMenuEvent(menu.getVisuals(), MenuEventType::changedSelected, level);
	eventQueue.addEvent(&temp);
}

void MapFightPicker::performMenuAction(int action)
{
	switch (action)
	{
	case ConfirmationItems::yes:
		closeConfirmationWindow();
		confirmBattleAction();
		break;

	case ConfirmationItems::no:
		closeConfirmationWindow();
		break;
	}
}

void MapFightPicker::confirmBattleAction()
{
	if (alsoMoveUnit)
	{
		bManager->moveSquad(moveToBePerformed);
	}
	doBattle();
	fightingDone = true;
}

void MapFightPicker::preSubLevelClosing()
{
	if (fightingDone)
	{
		passedBucket->actionPerformed = true;
		passedBucket->cursor = cursor;
		closeMe = true;
	}
}

void MapFightPicker::doBattle()
{
	std::pair<BattleVisualData , std::vector<LevelUpData>> fightData = bManager->doBattle(fightingSquad.getID(), targetList.at(currentIndex).getID());
	BattleVisualData battleVisuals = fightData.first;
	BattleEvent evnt = BattleEvent(level, battleVisuals);
	addSignalAnticipation(SignalSubType::Battle);
	eventQueue.addEvent(&evnt);

	unsigned int i;
	std::list<ActionResults> resultsList = battleVisuals.getResults();
	while (resultsList.size() > 0)
	{
		ActionResults results = resultsList.front();
		std::vector<std::pair<int, bool>> deathIDTeam = results.getDeathInfo();
		for (i = 0; i < deathIDTeam.size(); i++)
		{
			int squadID;
			if (deathIDTeam.at(i).second)
			{
				squadID = battleVisuals.getAtkID();
			}
			else
			{
				squadID = battleVisuals.getDefID();
			}
			UnitKilledEvent ev = UnitKilledEvent(level, squadID, deathIDTeam.at(i).first);
			eventQueue.addEvent(&ev);
			addSignalAnticipation(SignalSubType::Death);
		}
		resultsList.pop_front();
	}

	if (fightData.second.size() > 0)
	{
		openLink(new LevelUpHandler(level + 1, fightData.second, bManager->getBattleFieldPtr()));
	}
	else
	{
		passedBucket->actionPerformed = true;
		passedBucket->cursor = cursor;
		closeMe = true;
	}

	bManager->putToRest(fightingSquad.getID());
}