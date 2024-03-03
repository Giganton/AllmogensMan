#include "Flag.h"

void Flag::addSquad(Squad sqd)
{
	sqd.tag(tag);
	squads.push_back(sqd);
}

void Flag::addSquadOverwrite(Squad sqd)
{
	unsigned int i;
	int id = sqd.getID();
	for (i = 0; i < squads.size(); i++)
	{
		if (squads.at(i).getID() == id)
		{
			squads.erase(squads.begin() + i);
			break;
		}
	}

	addSquad(sqd);
}

void Flag::addSquads(std::vector<Squad> squads)
{
	unsigned int i;
	for (i = 0; i < squads.size(); i++)
	{
		addSquad(squads.at(i));
	}
}

void Flag::addSquadsOverwrite(std::vector<Squad> squads)
{
	unsigned int i;
	for (i = 0; i < squads.size(); i++)
	{
		addSquadOverwrite(squads.at(i));
	}

}

std::vector<Squad*> Flag::getSquadPointers()
{
	unsigned int i;
	std::vector<Squad*> retVal;

	for (i = 0; i < squads.size(); i++)
	{
		retVal.push_back(&squads.at(i));
	}

	return retVal;
}

void Flag::removeSquad(int squadID)
{
	unsigned int i;
	for (i = 0; i < squads.size(); i++)
	{
		if (squads.at(i).getID() == squadID)
		{
			squads.erase(squads.begin() + i);
		}
	}
}

void Flag::addUnits(std::vector<Unit> units)
{
	unsigned int i;
	for (i = 0; i < units.size(); i++)
	{
		addUnit(units.at(i));
	}
}

void Flag::emptySquad(int squadID)
{
	Squad* squad = getSquadPointer(squadID);
	addUnits(squad->getAllUnits());
	squad->removeAllUnits();
}

void Flag::disbandSquad(int squadID)
{
	unsigned int i;
	for (i = 0; i < squads.size(); i++)
	{
		if (squads.at(i).getID() == squadID)
		{
			addUnits(squads.at(i).getAllUnits());
			squads.erase(squads.begin() + i);
		}
	}
}

/*void Flag::formNewSquad(std::vector<std::pair<bool, int>> frontRow, std::vector<std::pair<bool, int>> backRow, int leaderID)
{
	if (frontRow.size() != TACTICAL_Y || backRow.size() != TACTICAL_Y)
	{
		throw new std::exception();
	}
	Squad newSquad = idCreator->createSquad();
	unsigned int i;
	for (i = 0; i < frontRow.size(); i++)
	{
		if (!frontRow.at(i).first)
		{
			int id = frontRow.at(i).second;
			newSquad.addUnit(getUnit(id), 1, i);
			removeUnit(id);
		}
	}
	for (i = 0; i < backRow.size(); i++)
	{
		if (!backRow.at(i).first)
		{
			int id = backRow.at(i).second;
			newSquad.addUnit(getUnit(id), 0, i);
			removeUnit(id);
		}
	}
	//newSquad.setLeader(leaderID);
	addSquad(newSquad);
}*/

void Flag::fillSquad(int squadID, std::vector<std::pair<bool, int>> frontRow, std::vector<std::pair<bool, int>> backRow, int leaderID)
{
	if (frontRow.size() != TACTICAL_Y || backRow.size() != TACTICAL_Y)
	{
		throw new std::exception();
	}
	emptySquad(squadID);
	Squad* squad = getSquadPointer(squadID);
	
	unsigned int i;
	for (i = 0; i < frontRow.size(); i++)
	{
		if (!frontRow.at(i).first)
		{
			int id = frontRow.at(i).second;
			squad->addUnit(getUnit(id), 1, i);
			removeUnit(id);
		}
	}
	for (i = 0; i < backRow.size(); i++)
	{
		if (!backRow.at(i).first)
		{
			int id = backRow.at(i).second;
			squad->addUnit(getUnit(id), 0, i);
			removeUnit(id);
		}
	}
	//squad->setLeader(leaderID);
}


Squad* Flag::getSquadPointer(int ID)
{
	unsigned int i;
	for (i = 0; i < squads.size(); i++)
	{
		if (ID == squads.at(i).getID())
		{
			return &(squads.at(i));
		}
	}
	throw new std::exception();
	return nullptr;
}

Squad Flag::getSquad(int ID)
{
	unsigned int i;
	for (i = 0; i < squads.size(); i++)
	{
		if (ID == squads.at(i).getID())
		{
			return (squads.at(i));
		}
	}
	throw new std::exception();
	return Squad();
}

Unit* Flag::getUnitPtr(int id)
{
	unsigned int i;
	for (i = 0; i < bench.size(); i++)
	{
		if (id == bench.at(i).getID())
		{
			return &bench.at(i);
		}
	}
	throw new std::exception();
	return nullptr;
}

Unit Flag::getUnit(int id)
{
	return *getUnitPtr(id);
}

void Flag::removeUnit(int id)
{
	unsigned int i;
	unsigned int index = 0;
	for (i = 0; i < bench.size(); i++)
	{
		if (id == bench.at(i).getID())
		{
			index = i;
			break;
		}
	}
	bench.erase(bench.begin() + index);
}