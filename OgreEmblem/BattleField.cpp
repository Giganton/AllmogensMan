#include "BattleField.h"
#include<queue>
#include<numeric>
#include "FightResults.h"
#include "BattleStage.h"

BattleField::BattleField(BattleMap map, std::vector<Squad> squadList)
{
	bMap = map;
	unsigned int i;
	Squad sqd;
	std::map<tagID, std::vector<MapCoord>> startingPosMap = map.getStartingPosMap(); //funkar som kö här, kanske borde vara det också...
	for (i = 0; i < squadList.size(); i++)
	{
		sqd = squadList.at(i);
		tagID tag = sqd.getFlagTag();
		if (startingPosMap.find(tag)->second.size() > 0)
		{
			addSquadToMap(sqd, startingPosMap.find(tag)->second.at(0));
			startingPosMap.find(tag)->second.erase(startingPosMap.find(tag)->second.begin()); //rörigt!
		}
	}
}

BattleField::BattleField(Battle battle, std::vector<Squad> playerSquads)
{
	bMap = battle.getMap();
	unsigned int i;
	std::vector < std::pair < Squad, MapCoord > > enemySpawns = battle.getEnemySpawns();
	for (i = 0; i < enemySpawns.size(); i++)
	{
		addSquadToMap(enemySpawns.at(i).first, enemySpawns.at(i).second);
	}

	std::map<tagID, std::vector<MapCoord>> startingPosMap = bMap.getStartingPosMap();
	for (i = 0; i < playerSquads.size(); i++)
	{
		Squad sqd = playerSquads.at(i);
		tagID tag = sqd.getFlagTag();
		if (startingPosMap.find(tag)->second.size() > 0)
		{
			addSquadToMap(sqd, startingPosMap.find(tag)->second.at(0));
			startingPosMap.find(tag)->second.erase(startingPosMap.find(tag)->second.begin()); //rörigt!
		}
	}
}

void BattleField::addSquadToMap(Squad sqd, MapCoord coord)
{
	if (isSquadOnField(sqd) || !canIStandHere(coord, sqd))
	{
		throw new std::exception();
	}
	squads.insert({ sqd.getID(), sqd });
	coordsBySquadID.insert({ sqd.getID(), coord });
	squadIDByCoords.insert({ coord, sqd.getID() });
}

void BattleField::removeSquadFromMap(Squad sqd)
{
	if (!isSquadOnField(sqd))
	{
		throw new std::exception();
	}
	squads.erase(sqd.getID());
	MapCoord coord = coordsBySquadID.find(sqd.getID())->second;
	coordsBySquadID.erase(sqd.getID());
	squadIDByCoords.erase(coord);
}

void BattleField::moveSquadToCoord(int sqdID, MapCoord coord)
{
	if (isCoordOccupied(coord))
	{
		throw new std::exception();
	}
	MapCoord oldCoord = coordsBySquadID.find(sqdID)->second;
	squadIDByCoords.erase(oldCoord);
	squadIDByCoords.insert({ coord, sqdID });
	coordsBySquadID.find(sqdID)->second = coord;
}

bool BattleField::isSquadOnField(Squad sqd)
{
	return isSquadOnField(sqd.getID());
}
bool BattleField::isSquadOnField(int sqdID)
{
	return (squads.find(sqdID) != squads.end());
}


bool BattleField::isCoordOccupied(MapCoord coord)
{
	return (squadIDByCoords.find(coord) != squadIDByCoords.end());
}

std::vector<SquadData> BattleField::getSquadData()
{
	std::map<int, Squad>::iterator it;
	std::vector<SquadData> retVal;
	SquadData sqdData;

	for (it = squads.begin(); it != squads.end(); it++)
	{
		sqdData = SquadData(it->second, coordsBySquadID.find(it->first)->second);
		retVal.push_back(sqdData);
	}

	return retVal;
}

std::vector<Squad> BattleField::getSquadsByProximity(MapCoord mapPos)
{
	std::vector<Squad> squadVector = {};
	std::vector<int> distVector = {};
	std::vector<int> indexVector = {};
	unsigned int i;
	if (squads.size() == 0)
	{
		throw new std::exception(); //om enheten är ensam på kartan
	}

	std::map<int, MapCoord>::iterator it;
	Squad* closestSquad = nullptr;

	for (it = coordsBySquadID.begin(); it != coordsBySquadID.end(); it++)
	{
		MapCoord temp = it->second;
		int dist = mapPos.distanceTo(temp);
		distVector.push_back(dist);
		squadVector.push_back(squads.find(it->first)->second);
	}
	indexVector = sortIndices(distVector);
	std::vector<Squad> retVal(squadVector.size());

	for (i = 0; i < indexVector.size(); i++)
	{
		retVal.at(i) = squadVector.at(indexVector.at(i));
	}

	return retVal;
}

std::vector<int> BattleField::sortIndices(std::vector<int> vector)
{
	std::vector<int> retVal(vector.size());
	std::iota(retVal.begin(), retVal.end(), 0); //initierar indexvektorn 0,1,2,...

	std::sort(retVal.begin(), retVal.end(), [&vector](int i1, int i2) {return vector[i1] < vector[i2]; });
	return retVal;
}

Squad BattleField::findClosestSquad(Squad squad)
{
	if (squads.size() <= 1)
	{
		throw new std::exception(); //om enheten är ensam på kartan
	}
	MapCoord squadPos = findSquadPos(squad);

	std::map<int, MapCoord>::iterator it;
	int minDistance = 999999;
	Squad closestSquad;

	for (it = coordsBySquadID.begin(); it != coordsBySquadID.end(); it++)
	{
		MapCoord temp = it->second;
		int dist = squadPos.distanceTo(temp);
		if (dist > 0 && dist < minDistance)
		{
			minDistance = dist;
			closestSquad = squads.find(it->first)->second;
		}
	}
	return closestSquad;
}

MapCoord BattleField::findSquadPos(Squad sqd)
{
	if (coordsBySquadID.find(sqd.getID()) == coordsBySquadID.end())
	{
		throw new std::exception();
	}
	return coordsBySquadID.find(sqd.getID())->second;
}

MapCoord BattleField::findSquadPos(int sqdID)
{
	return findSquadPos(squads.find(sqdID)->second);
}

Squad BattleField::findSquadAtPos(MapCoord coord)
{
	if (squadIDByCoords.find(coord) == squadIDByCoords.end())
	{
		throw new std::exception();
	}
	return squads.find(squadIDByCoords.find(coord)->second)->second;
}

std::vector<Squad> BattleField::allSquadsInRange(int x, int y, int range)
{
	int i, j;
	int widthRange = range;
	std::vector<Squad> retVec = {};

	for (i = -range; i <= range; i++)
	{
		if (i != 0 && bMap.withinBounds(x + i, y) && isCoordOccupied(MapCoord(x + i, y)))
		{
			retVec.push_back(findSquadAtPos(MapCoord(x + i, y)));
		}
		for (j = 1; j <= range - abs(i); j++)
		{
			if (bMap.withinBounds(x + i, y + j) && isCoordOccupied(MapCoord(x + i, y + j)))
			{
				retVec.push_back(findSquadAtPos(MapCoord(x + i, y + j)));
			}
			if (bMap.withinBounds(x + i, y - j) && isCoordOccupied(MapCoord(x + i, y - j)))
			{
				retVec.push_back(findSquadAtPos(MapCoord(x + i, y - j)));
			}
		}
	}
	return retVec;
}

bool BattleField::isAnyLivingSquadInRange(int x, int y, int range)
{
	std::vector<Squad> squads = allSquadsInRange(x, y, range);
	unsigned int i;
	if (squads.size() == 0)
	{
		return false;
	}
	else
	{
		bool living = false;
		for (i = 0; i < squads.size(); i++)
		{
			if (!squads.at(i).isDefeated())
			{
				living = true;
			}
		}
		return living;
	}
}

bool BattleField::isAnyLivingEnemyInRange(int x, int y, int range, tagID tag)
{
	std::vector<Squad> squads = allSquadsInRange(x, y, range);
	unsigned int i;
	if (squads.size() == 0)
	{
		return false;
	}
	else
	{
		bool livingEnemy = false;
		for (i = 0; i < squads.size(); i++)
		{
			if (!squads.at(i).isDefeated() && squads.at(i).getFlagTag() != tag)
			{
				livingEnemy = true;
			}
		}
		return livingEnemy;
	}
}

std::vector<Squad> BattleField::allLivingEnemiesInRange(int x, int y, int range, tagID tag)
{
	std::vector<Squad> allVec = allSquadsInRange(x, y, range);
	std::vector<Squad> retVec;
	unsigned int i;
	for (i = 0; i < allVec.size(); i++)
	{
		if (allVec.at(i).getFlagTag() != tag && !allVec.at(i).isDefeated())
		{
			retVec.push_back(allVec.at(i));
		}
	}
	return retVec;
}

bool BattleField::isAnySquadInRange(int x, int y, int range)
{
	if (allSquadsInRange(x, y, range).size() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}


Squad BattleField::getHoveredSquad(Cursor cursor)
{
	return findSquadAtPos(MapCoord(cursor.getPos().x, cursor.getPos().y));
}

bool BattleField::isHoveredEmpty(Cursor cursor)
{
	return !isCoordOccupied(MapCoord(cursor.getPos().x, cursor.getPos().y));
}

bool BattleField::doesHoveredExist(Cursor cursor)
{
	return bMap.doesTileExist(MapCoord(cursor.getPos().x, cursor.getPos().y));
}

bool BattleField::canIStandHere(MapCoord coord, Squad sqd)
{
	if (!bMap.withinBounds(coord) || !bMap.getTile(coord)->isStandable())
	{
		return false;
	}
	else
	{
		if (isCoordOccupied(coord) && findSquadAtPos(coord).getID() != sqd.getID())
		{
			return false; //om man själv redan står i rutan räknas den som ståbar
		}
		else
		{
			return true;
		}
	}
}


bool BattleField::canIPassHere(MapCoord coord, Squad sqd)
{
	if (!bMap.withinBounds(coord))
	{
		return false;
	}
	else if (!isCoordOccupied(coord))
	{
		return bMap.isCoordPassable(coord);
	}
	else
	{
		Squad occupee = findSquadAtPos(coord);
		return bMap.isCoordPassable(coord) && (sqd.getFlagTag() == occupee.getFlagTag());
	}
}

std::pair<BattleVisualData, std::vector<LevelUpData>> BattleField::doBattle(int attackerID, int defenderID)
{
	MapTile atkTile = *bMap.getTile(findSquadPos(attackerID));
	MapTile defTile = *bMap.getTile(findSquadPos(defenderID));
	Squad* attacker = &squads.find(attackerID)->second;
	Squad* defender = &squads.find(defenderID)->second;
	BattleStage bStage = BattleStage(atkTile.getTerrain(), defTile.getTerrain(), attacker, defender);
	bStage.doBattle();
	BattleVisualData visuData = bStage.getVisuals();
	std::vector<LevelUpData> levelData;

	if (attacker->getFlagTag() == tagID::player)
	{
		levelData = attacker->distributeExperience(bStage.getAttackerXP());
		visuData.setPostBattleXP(attacker->getUnitList().at(0).unit.experiencePoints);
	}
	else if (defender->getFlagTag() == tagID::player)
	{
		levelData = defender->distributeExperience(bStage.getDefenderXP());
		visuData.setPostBattleXP(defender->getUnitList().at(0).unit.experiencePoints);
	}

	if(attacker->isDefeated())
	{
		killSquad(*attacker);
	}
	if (defender->isDefeated())
	{
		killSquad(*defender);
	}

	return std::make_pair(visuData, levelData);
}


MoveData BattleField::moveSquad(MoveData moveData)
{
	moveSquadToCoord(moveData.movedSquadID, moveData.path.at(moveData.path.size() - 1));
	return moveData;
}


void BattleField::killSquad(Squad sqd)
{
	deadSquads.insert({ sqd.getID() , sqd });
	//ta bort från kartan
	removeSquadFromMap(sqd);
	//skicka dödsevent
}

bool BattleField::isSquadDead(int sqdID)
{
	std::map<int, Squad>::iterator it = deadSquads.find(sqdID);

	if (it != deadSquads.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BattleField::anyFlagSquadsLeft(tagID tag)
{
	return getAllLivingFlagSquads(tag).size() > 0;
}

std::vector<Squad> BattleField::getAllLivingFlagSquads(tagID tag)
{
	std::vector<Squad> retVal;
	unsigned int i;
	std::vector<SquadData> squadData = getSquadData();
	for (i = 0; i < squadData.size(); i++)
	{
		tagID squadTag = squadData.at(i).squad.getFlagTag();
		if (squadTag == tag && !squadData.at(i).squad.isDefeated())
		{
			retVal.push_back(squadData.at(i).squad);
		}
	}
	return retVal;
}

std::vector<Squad> BattleField::getAllDeadFlagSquads(tagID tag)
{
	std::vector<Squad> retVal;
	unsigned int i;
	std::vector<SquadData> squadData = getSquadData();
	for (i = 0; i < squadData.size(); i++)
	{
		tagID squadTag = squadData.at(i).squad.getFlagTag();
		if (squadTag == tag && squadData.at(i).squad.isDefeated())
		{
			retVal.push_back(squadData.at(i).squad);
		}
	}
	return retVal;
}

int BattleField::getMovementCost(MapCoord start, MapCoord dest, Squad sqd)
{
	if (!bMap.neighbouringTiles(start, dest))
	{
		return -1;
	}
	else
	{
		bool riverPassed = bMap.riverConnection(start, dest);
		if (riverPassed)
		{
			return sqd.getMoveRange();
		}
		else
		{
			return 1;
		}
	}
}