#include "BattleManager.h"
#include "StartPlayerTurnEvent.h"
#include "StringHandler.h"
#include "StartEnemyTurnEvent.h"
#include "allActions.h"


BattleManager::BattleManager(IdCreator* idCr, StringHandler* strHandl)
{
    idCreator = idCr;
	//stringToTerrainMap = terrainMap;
	stringHandler = strHandl;
}

void BattleManager::initiateBattlefield(Flag* plr, Battle nextBattle)
{
	victoryConditions = nextBattle.getVictoryConditions();
	enemy = Flag(tagID::redEnemy, idCreator);
	enemy.addSquads(nextBattle.getEnemySquads());

    player = plr;
	std::vector<Squad> playerSquads = player->getSquads();

	bField = BattleField(nextBattle, playerSquads);

	std::vector<Flag*> teams;
	teams.push_back(player);
	teams.push_back(&enemy);

	squadAI = SquadAI(&bField);

	turnKeeper = TurnKeeper(teams, &bField);
	battleIsActive = true;
	battleIsWon = false;
}

/* BattleManager::initiateFlags(std::vector<Flag*> flags)
{
	unsigned int i;
	for (i = 0; i < flags.size(); i++)
	{
		flagMap.insert({ flags.at(i)->getTag(), flags.at(i) });
		participatingTags.push_back(flags.at(i)->getTag());
	}
	turnKeeper = TurnKeeper(flags, &bField);
}*/

bool BattleManager::checkForVictory()
{
	unsigned int i;
	for (i = 0; i < victoryConditions.size(); i++)
	{
		switch (victoryConditions.at(i))
		{
		case VictoryCondition::route:
			return checkForRouteVictory();
			break;
		default:
			throw new std::exception();
			return false;
		}
	}
	return false;
}

bool BattleManager::checkForRouteVictory()
{
	return !bField.anyFlagSquadsLeft(enemy.getTag());
}

StructuredEventQueue BattleManager::AIAction()
{
	StructuredEventQueue generatedEvents;
	if (turnKeeper.isPlayerActive())
	{
		throw new std::exception();
	}

	while (turnKeeper.getActiveSquads().size() > 0)
	{
		Squad currSquad = bField.getSquadByID(turnKeeper.getActiveSquads().at(0));
		if (!currSquad.isDefeated())
		{
			generatedEvents.concatenateQueues(squadAI.controlSquad(currSquad.getID()));
		}
		turnKeeper.putToRest(currSquad.getID());
	}
	turnKeeper.endTurn();
	return generatedEvents;
}

/*void BattleManager::addSquadsToMap(std::vector<Squad> squadList, tagID tag)
{
	std::vector<MapCoord> startingTiles = bField.getStartingPos(tag);
	unsigned int i = 0;

	while (i < startingTiles.size() && i < squadList.size())
	{
		//bMap.placeSquad(squadList.at(i), startingTiles.at(i));
		bField.addSquadToMap(squadList.at(i), startingTiles.at(i));
		i = i + 1;
	}
}*/

StructuredEventQueue BattleManager::endTurn()
{
	StructuredEventQueue generatedEvents;
	turnKeeper.endTurn();
	if (!turnKeeper.isPlayerActive())
	{
		StartEnemyTurnEvent evnt = StartEnemyTurnEvent();
		generatedEvents.addEvent(&evnt);
		
		generatedEvents = runAI(); //här ska det in en return-variabel ut till mapBrowser som kan skapa events till AI:n och skicka iväg.
	}
	if (turnKeeper.isPlayerActive())
	{
		StartPlayerTurnEvent evnt = StartPlayerTurnEvent();
		generatedEvents.addEvent(&evnt);
	}

	return generatedEvents;
}

bool BattleManager::isSquadActive(int squadID)
{
	return turnKeeper.isSquadActive(squadID);
}

void BattleManager::putToRest(int squadID)
{
	turnKeeper.putToRest(squadID);
}

MoveData BattleManager::moveSquad(MoveData moveData)
{
	return bField.moveSquad(moveData);
}

MoveData BattleManager::peekMoveSquad(MoveData moveData)
{
	return moveData;
}

std::pair<BattleVisualData, std::vector<LevelUpData>> BattleManager::doBattle(int attackerID, int defenderID)
{
	return bField.doBattle(attackerID, defenderID);
}

void BattleManager::winBattle()
{ 
	endBattle();
	battleIsWon = true; 
}

void BattleManager::endBattle()
{
	unsigned int i;
	std::vector<Squad> undefeatedSquads = bField.getAllLivingFlagSquads(player->getTag());
	for (i = 0; i < undefeatedSquads.size(); i++)
	{
		undefeatedSquads.at(i).cleanDeadUnits();
	}
	player->addSquadsOverwrite(undefeatedSquads);

	std::vector<Squad> defeatedSquads = bField.getAllDeadFlagSquads(player->getTag());
	for (i = 0; i < defeatedSquads.size(); i++)
	{
		defeatedSquads.at(i).cleanDeadUnits();
	}
	player->addSquadsOverwrite(defeatedSquads);
}