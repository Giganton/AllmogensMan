#include "TurnKeeper.h"
#include "Flag.h"
#include "BattleField.h"

TurnKeeper::TurnKeeper(std::vector<Flag*> teams, BattleField* battleField)
{
	bField = battleField;
	participants = teams;
	activateTeam(teams.at(0));
	activeIndex = 0;
}

void TurnKeeper::activateTeam(Flag* team)
{
	activeTeam = team;
	unsigned int i;
	std::vector<Squad> squads = team->getSquads();
	squadsInAction.clear();

	for (i = 0; i < squads.size(); i++)
	{
		if (!bField->isSquadDead(squads.at(i).getID()))
		{
			squadsInAction.push_back(squads.at(i).getID());
		}
	}
}

bool TurnKeeper::isSquadActive(int squadID)
{
	unsigned int i;
	for (i = 0; i < squadsInAction.size(); i++)
	{
		if (squadsInAction.at(i) == squadID)
		{
			return true;
		}
	}
	return false;
}

void TurnKeeper::putToRest(int squadID)
{
	unsigned int i;
	if (squadsInAction.size() == 0)
	{
		throw new std::exception;
	}

	for (i = 0; i < squadsInAction.size(); i++)
	{
		if (squadsInAction.at(i) == squadID)
		{
			squadsInAction.erase(squadsInAction.begin() + i);
			/*if (squadsInAction.size() == 0)
			{
				turnIsFinished = true;
			}*/
			break;
		}
		else if (i == squadsInAction.size() - 1)
		{
			throw new std::exception();
		}
	}
}

void TurnKeeper::endTurn()
{
	unsigned int i;
	std::vector<Squad*> activeSquads = activeTeam->getSquadPointers();
	for (i = 0; i < activeSquads.size(); i++)
	{
		activeSquads.at(i)->endTurn();
	}
	activeIndex = (activeIndex + 1) % participants.size();
	activateTeam(participants.at(activeIndex));
}