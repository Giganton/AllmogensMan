#include "Squad.h"
#include "Unit.h"
//#include "GraphicsUtils.h" //könstit
#include "StringHandler.h"

TacticalTile::TacticalTile()
{
	posX = -1;
	posY = -1;
	empty = true;
}

TacticalTile::TacticalTile(int x, int y)
{
	posX = x;
	posY = y;
	empty = true;
}

int TacticalTile::getOccupantID()
{
	if (empty)
	{
		throw new std::exception("tried to retrieve unit from empty tactical tile");
	}
	return occupantID;
}

std::vector<UnitInSquadData> Squad::getUnitList()
{
	std::vector<UnitInSquadData> retVal;
	int i, j;

	for (i = 0; i < TACTICAL_X; i++)
	{
		for (j = 0; j < TACTICAL_Y; j++)
		{
			if (!getTile(i, j)->isEmpty())
			{
				retVal.push_back(UnitInSquadData(getUnitPtr(i, j)->getData() , SquadPos(i, j)));
			}
		}
	}
	return retVal;
}

void TacticalTile::removeUnit()
{
	occupantID = -1;
	empty = true;
}

bool TacticalTile::placeUnit(int addee)
{
	if (empty)
	{
		occupantID = addee;
		empty = false;
		return true;
	}
	else
	{
		throw new std::exception();
	}
}

Squad::Squad(long int id)
{
	int i;
	int j;

	ID = id;

	moveRange = 5;
	movesLeft = 5;
	BrowsableIcon temp;
	setBrowserIcon(temp);

	for (i = 0; i < TACTICAL_X; i++)
	{
		for (j = 0; j < TACTICAL_Y; j++)
		{
			tacticalGrid[i][j] = TacticalTile(i, j);
		}
	}
	unitList.reserve(6);
}

Squad::Squad(long int id, Unit leaderUnit, StringHandler* strHandler) : Squad(id)
{
	leader = leaderUnit;
	leaderPresent = true;
	tacticalGrid[1][1].placeUnit(leader.getID());

	squadName = leaderUnit.getName() + "s " + strHandler->getGeneralPhrase(GeneralStringID::enumSquadString);
}

Squad::Squad(long int id, Unit leaderUnit, SquadPos pos, StringHandler* strHandler) : Squad(id)
{
	leader = leaderUnit;
	leaderPresent = true;
	tacticalGrid[pos.getX()][pos.getY()].placeUnit(leader.getID());

	squadName = leaderUnit.getName() + "s " + strHandler->getGeneralPhrase(GeneralStringID::enumSquadString);

}

/*HeroSquad::HeroSquad(Hero heroUnit, long int id) : Squad(id)
{
	hero = heroUnit;
	tacticalGrid[1][1].placeUnit(&hero);
}*/

BrowsingData Squad::getBrowserData() //ska egentligen inte göras här
{
	BrowsingData bData;
	BrowsableIcon icon;
	std::vector<BrowsableIconTag> tags;
	std::vector<std::pair<float, float>> offsets;
	unsigned int i, j;
	for (i = 0; i < TACTICAL_X; i++)
	{
		for (j = 0; j < TACTICAL_Y; j++)
		{
			TacticalTile tile = tacticalGrid[i][j];
			if (!tile.isEmpty())
			{
				//std::pair<float, float> off = std::make_pair(j * (MAP_SPRITE_W + 2), i * (MAP_SPRITE_H + 2));
				//icon.incorporateIcon(getUnitPtr(i, j)->getIcon(), off);
			}
		}
	}
	bData.setIcon(icon);
	return bData;
}

/*Unit* Squad::getLeadUnit()
{
	if (empty)
	{
		throw new std::exception();
	}
	return findUnitPtr(leaderID);
}*/

TacticalTile* Squad::getTile(int x, int y)
{
	if (x >= TACTICAL_X || x < 0 || y >= TACTICAL_Y || y < 0)
	{
		throw new std::exception("getTile x or y out of bounds");
	}
	return &tacticalGrid[x][y];
}

Unit* Squad::findUnitPtr(int id)
{
	unsigned int i;
	for (i = 0; i < unitList.size(); i++)
	{
		if (unitList.at(i).getID() == id)
		{
			return &unitList.at(i);
		}
	}
	if (leaderPresent && leader.getID() == id)
	{
		return &leader;
	}
	throw new std::exception();
	return nullptr;
}

Unit Squad::findUnit(int id)
{
	unsigned int i;
	for (i = 0; i < unitList.size(); i++)
	{
		if (unitList.at(i).getID() == id)
		{
			return unitList.at(i);
		}
	}
	if (leaderPresent && leader.getID() == id)
	{
		return leader;
	}
	throw new std::exception();
	return Unit();
}

/*void Squad::setLeader(int id)
{
	leaderID = id;
	Unit* leadUnit = findUnitPtr(id);
	if (leadUnit->getProfession()->getName() == "Knekt")
	{
		setBrowserIcon(BrowsableIcon::squadKnight);
	}
	else if (leadUnit->getProfession()->getName() == "Trollkarl")
	{
		setBrowserIcon(BrowsableIcon::squadWizard);
	}
	else
	{
		throw new std::exception();
	}
}*/

Unit* Squad::getUnitPtr(int x, int y)
{
	return findUnitPtr(getTile(x, y)->getOccupantID());
}

SquadPos Squad::getPosFromIndex(int index)
{
	if (index < 0 || index > TACTICAL_X * TACTICAL_Y - 1)
	{
		throw new std::exception();
	}
	int y = index % TACTICAL_Y;
	int x = 0;
	if (index > 2)
	{
		x = 1;
	}
	return SquadPos(x, y);
}

TacticalTile* Squad::getTile(SquadPos mapPos)
{
	if (mapPos.getX() >= TACTICAL_X || mapPos.getX() < 0 || mapPos.getY() >= TACTICAL_Y || mapPos.getY() < 0)
	{
		throw new std::exception("getTile x or y out of bounds");
	}
	return &tacticalGrid[mapPos.getX()][mapPos.getY()];
}

bool Squad::addUnit(Unit addee, int posX, int posY)
{
	if (unitList.size() + 1 > unitCapacity)
	{
		throw new std::exception();
	}
	bool temp = false;
	if (addee.isLeader())
	{
		if (leaderPresent)
		{
			throw new std::exception();
		}
		leader = addee;
		leaderPresent = true;
		temp = getTile(posX, posY)->placeUnit(leader.getID());
	}
	else
	{
		unitList.push_back(addee);

		temp = getTile(posX, posY)->placeUnit(unitList.at(unitList.size() - 1).getID());
	}
	if (!temp)
	{
		throw new std::exception();
	}
	empty = false;

	return temp;
}

bool Squad::addUnit(Unit addee, int posIndex)
{
	SquadPos pos = getPosFromIndex(posIndex);
	return addUnit(addee, pos.getX(), pos.getY());
}

bool Squad::addUnit(Unit addee, SquadPos pos)
{
	return addUnit(addee, pos.getX(), pos.getY());
}

/*bool Squad::addUnit(Unit addee, int posX, int posY)
{
	bool retVal = addUnit(addee, posX, posY);
	if (isLeader)
	{
		//leader = getTile(posX, posY)->getUnitPtr();
		setLeader(addee.getID());
	}
	return retVal;
}*/

/*
bool Squad::removeUnit(Unit* removee)
{
	int i, j;
	for (i = 0; i < TACTICAL_X; i++)
	{
		for (j = 0; j < TACTICAL_Y; j++)
		{
			if (!tacticalGrid[i][j].isEmpty() && tacticalGrid[i][j].getUnit() == removee)
			{
				tacticalGrid[i][j].removeUnit();
				return true;
			}
		}
	}
	return false;
}
*/
Unit Squad::removeUnit(int x, int y)
{
	SquadPos mapPos = SquadPos(x, y);
	return removeUnit(mapPos);
}

Unit Squad::removeUnit(int posIndex)
{
	SquadPos pos = getPosFromIndex(posIndex);
	return removeUnit(pos);
}

Unit Squad::removeUnit(SquadPos mapPos) //ANVÄND ENBART DENNA NÄR UNITEN SKA BORT FÖR ALLTID
{
	TacticalTile* tile = getTile(mapPos.getX(), mapPos.getY());
	Unit retVal;
	if (tile->isEmpty())
	{
		throw new std::exception();
	}
	else
	{
		int rmID = tile->getOccupantID();
		tile->removeUnit();
		unsigned int i, j;
		empty = true;
		for (i = 0; i < TACTICAL_X; i++)
		{
			for (j = 0; j < TACTICAL_Y; j++)
			{
				if (!getTile(SquadPos(i, j))->isEmpty())
				{
					empty = false;
				}
			}
		}
		if (leader.getID() == rmID)
		{
			retVal = leader;
			leaderPresent = false;
		}
		else
		{
			for (i = 0; i < unitList.size(); i++)
			{
				if (unitList.at(i).getID() == rmID)
				{
					retVal = unitList.at(i);
					unitList.erase(unitList.begin() + i);
					i = i - 1;
				}
			}
		}
		
		return retVal;
	}
}

void Squad::removeAllUnits()
{
	int i, j;
	for (i = 0; i < TACTICAL_X; i++)
	{
		for (j = 0; j < TACTICAL_Y; j++)
		{
			SquadPos mapPos = SquadPos(i, j);
			if (!getTile(mapPos)->isEmpty())
			{
				removeUnit(SquadPos(i, j));
			}
		}
	}
	unitList.clear();
	empty = true;
}

std::vector<Unit*> Squad::getAllUnitPtrs()
{
	unsigned int i;
	std::vector<Unit*> retVal;
	for (i = 0; i < unitList.size(); i++)
	{
		retVal.push_back(&unitList.at(i));
	}
	if (leaderPresent)
	{
		retVal.push_back(&leader);
	}
	return retVal;
}

std::vector<Unit*> Squad::getAllLivingUnitPtrs()
{
	std::vector<Unit*> retVal = getAllUnitPtrs();
	unsigned int i;
	for (i = 0; i < retVal.size(); i++)
	{
		if (retVal.at(i)->isDead())
		{
			retVal.erase(retVal.begin() + i);
			i = i - 1;
		}
	}
	return retVal;
}

SquadPos Squad::whereIsThisUnit(int id)
{
	unsigned int i, j;
	for (i = 0; i < TACTICAL_X; i++)
	{
		for (j = 0; j < TACTICAL_Y; j++)
		{
			if (!getTile(i, j)->isEmpty() && getTile(i,j)->getOccupantID() == id)
			{
				return SquadPos(i, j);
			}
		}
	}
	throw new std::exception();
	return SquadPos();
}

bool Squad::isThisUnitIn(int id)
{
	unsigned int i;
	for (i = 0; i < unitList.size(); i++)
	{
		if (unitList.at(i).getID() == id)
		{
			return true;
		}
	}

	if (leaderPresent)
	{
		return (leader.getID() == id);
	}

	return false;
}

std::string Squad::getLeaderName()
{
	if (leaderPresent)
	{
		return leader.getName();
	}
	else
	{
		throw new std::exception();
	}
}

std::vector<Unit> Squad::getAllUnits()
{
	/*std::vector<Unit> retVal;
	int i, j;
	for (i = 0; i < TACTICAL_X; i++)
	{
		for (j = 0; j < TACTICAL_Y; j++)
		{
			if (!getTile(i, j)->isEmpty())
			{
				retVal.push_back(getTile(i, j)->getUnit());
			}
		}
	}
	return retVal;*/
	std::vector<Unit> retVal = unitList;
	if (leaderPresent)
	{
		retVal.push_back(leader);
	}
	return retVal;
}

std::vector<ProfessionTag> Squad::getBackProfTags()
{
	std::vector<ProfessionTag> retVal;
	int i;
	for (i = 0; i < TACTICAL_Y; i++)
	{
		if (!getTile(0, i)->isEmpty())
		{
			retVal.push_back(getUnitPtr(0, i)->getData().profession);
		}
		else
		{
			retVal.push_back(ProfessionTag::enumProfNone);
		}
	}
	return retVal;
}

std::vector<ProfessionTag> Squad::getFrontProfTags()
{
	std::vector<ProfessionTag> retVal;
	int i;
	for (i = 0; i < TACTICAL_Y; i++)
	{
		if (!getTile(1, i)->isEmpty())
		{
			retVal.push_back(getUnitPtr(1, i)->getData().profession);
		}
		else
		{
			retVal.push_back(ProfessionTag::enumProfNone);
		}
	}
	return retVal;
}

long int Squad::getID()
{ 
	return ID; 
}

std::vector<int> Squad::getFrontIDs()
{
	std::vector<int> retVal;
	int i;
	for (i = 0; i < TACTICAL_Y; i++)
	{
		if (!getTile(1, i)->isEmpty())
		{
			retVal.push_back(getTile(1, i)->getOccupantID());
		}
		else
		{
			retVal.push_back(-1);
		}
	}
	return retVal;
}

std::vector<int> Squad::getBackIDs()
{
	std::vector<int> retVal;
	int i;
	for (i = 0; i < TACTICAL_Y; i++)
	{
		if (!getTile(0, i)->isEmpty())
		{
			retVal.push_back(getTile(0, i)->getOccupantID());
		}
		else
		{
			retVal.push_back(-1);
		}
	}
	return retVal;
}

void Squad::swapUnits(SquadPos a, SquadPos b)
{
	Unit* unitA = getUnitPtr(a.getX(), a.getY());
	Unit* unitB = getUnitPtr(b.getX(), b.getY());

	getTile(a)->removeUnit();
	getTile(a)->placeUnit(unitB->getID());
	getTile(b)->removeUnit();
	getTile(b)->placeUnit(unitA->getID());
}

Unit Squad::insertSwapUnits(int oldUnitID, Unit newUnit)
{
	SquadPos unitPos = whereIsThisUnit(oldUnitID);
	Unit retVal = removeUnit(unitPos);

	addUnit(newUnit, unitPos.getX(), unitPos.getY());
	return retVal;
}

void Squad::swapUnitPositions(int unit1ID, int unit2ID)
{
	SquadPos pos1 = whereIsThisUnit(unit1ID);
	SquadPos pos2 = whereIsThisUnit(unit2ID);

	Unit unit1 = findUnit(unit1ID);
	Unit unit2 = findUnit(unit2ID);

	removeUnit(pos1);
	removeUnit(pos2);

	addUnit(unit1, pos2.getX(), pos2.getY());
	addUnit(unit2, pos1.getX(), pos1.getY());
}

bool Squad::isDefeated()
{
	bool rt = true;
	int i, j;
	for (i = 0; i < TACTICAL_X; i++)
	{
		for (j = 0; j < TACTICAL_Y; j++)
		{
			if (!tacticalGrid[i][j].isEmpty() && !getUnitPtr(i, j)->isDead())
			{
				rt = false;
				goto END;
			}
		}
	}
END: return rt;
}

void Squad::endTurn()
{
	movesLeft = moveRange;
}

void Squad::levelUpAll()
{
	unsigned int i;
	for (i = 0; i < unitList.size(); i++)
	{
		unitList.at(i).levelUp();
	}
	if (leaderPresent)
	{
		leader.levelUp();
	}
}

std::vector<LevelUpData> Squad::distributeExperience(int xp)
{
	unsigned int i;
	int livingUnits = 0;
	std::vector<LevelUpData> retVal;
	for (i = 0; i < unitList.size(); i++)
	{
		if (!unitList.at(i).isDead())
		{
			livingUnits = livingUnits + 1;
		}
	}
	if (leaderPresent && !leader.isDead())
	{
		livingUnits = livingUnits + 1;
	}

	if (livingUnits > 0)
	{
		int xpShare = xp / livingUnits;
		for (i = 0; i < unitList.size(); i++)
		{
			if (!unitList.at(i).isDead())
			{
				int levelUps = unitList.at(i).grantXP(xpShare);
				while (levelUps > 0)
				{
					LevelUpData entry = LevelUpData(ID, unitList.at(i).getID(), unitList.at(i).getLevel() - (levelUps - 1));
					retVal.push_back(entry);
					levelUps = levelUps - 1;
				}
			}
		}
		if (leaderPresent && !leader.isDead())
		{
			int levelUps = leader.grantXP(xpShare);
			while (levelUps > 0)
			{
				LevelUpData entry = LevelUpData(ID, leader.getID(), leader.getLevel() - (levelUps - 1));
				retVal.push_back(entry);
				levelUps = levelUps - 1;
			}
		}
	}
	return retVal;
}

FighterFormation Squad::getFormation()
{
	FighterFormation retVal;
	unsigned int i, j;
	for (i = 0; i < TACTICAL_X; i++)
	{
		for (j = 0; j < TACTICAL_Y; j++)
		{
			if (!getTile(i, j)->isEmpty())
			{
				retVal.setFighter(getUnitPtr(i, j), i, j);
			}
		}
	}
	return retVal;
}


void Squad::cleanDeadUnits()
{
	unsigned int i;
	for (i = 0; i < unitList.size(); i++)
	{
		if (unitList.at(i).isDead())
		{
			SquadPos mapPos = whereIsThisUnit(unitList.at(i).getID());
			removeUnit(mapPos);
			i = i - 1;
		}
	}
	if (leaderPresent)
	{
		if (leader.isDead())
		{
			leader.raiseFromDead();
		}
	}
}