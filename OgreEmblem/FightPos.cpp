#include "FightPos.h"

std::vector<FightPos> getAllFightPositions()
{
	std::vector<FightPos> retVal;
	retVal.push_back(FightPos(SquadPos(0, 0), true));
	retVal.push_back(FightPos(SquadPos(0, 1), true));
	retVal.push_back(FightPos(SquadPos(0, 2), true));
	retVal.push_back(FightPos(SquadPos(1, 0), true));
	retVal.push_back(FightPos(SquadPos(1, 1), true));
	retVal.push_back(FightPos(SquadPos(1, 2), true));

	retVal.push_back(FightPos(SquadPos(0, 0), false));
	retVal.push_back(FightPos(SquadPos(0, 1), false));
	retVal.push_back(FightPos(SquadPos(0, 2), false));
	retVal.push_back(FightPos(SquadPos(1, 0), false));
	retVal.push_back(FightPos(SquadPos(1, 1), false));
	retVal.push_back(FightPos(SquadPos(1, 2), false));

	return retVal;
}

bool doesPRvecAcontainPRvecB(std::vector<PositionalRelation> A, std::vector<PositionalRelation> B)
{
	unsigned int i, j;

	for (i = 0; i < A.size(); i++)
	{
		for (j = 0; j < B.size(); j++)
		{
			if (A.at(i) == B.at(j))
			{
				B.erase(B.begin() + j);
				j = j - 1;
			}
		}
	}
	return B.size() == 0;
}

bool FightPos::isNeighbourTo(FightPos pos)
{
	if (attackingSide == pos.attackingSide)
	{
		unsigned int i;
		std::vector<SquadPos> nbours = getNeighbours(squadPos);
		for (i = 0; i < nbours.size(); i++)
		{
			if (nbours.at(i) == pos.squadPos)
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		return false;
	}
}

bool FightPos::operator<(const FightPos& rhs) const
{
	if (attackingSide && !rhs.attackingSide)
	{
		return false;
	}
	else if (!attackingSide && rhs.attackingSide)
	{
		return true;
	}
	else if (attackingSide == rhs.attackingSide)
	{
		return squadPos.getIndexRepresentation() < rhs.squadPos.getIndexRepresentation();
	}
	else
	{
		throw new std::exception();
		return false;
	}
}


std::vector<PositionalRelation> FightPos::getRelations(FightPos pos)
{
	std::vector<PositionalRelation> retVal;

	if (isEqual(pos))
	{
		retVal.push_back(PositionalRelation::samePos);
	}
	if (isNeighbourTo(pos))
	{
		retVal.push_back(PositionalRelation::neighbour);
	}
	if (isInFrontOf(pos))
	{
		retVal.push_back(PositionalRelation::inFrontOf);
	}
	if (isBehind(pos))
	{
		retVal.push_back(PositionalRelation::behind);
	}
	if (isOnSameSide(pos))
	{
		retVal.push_back(PositionalRelation::sameSide);
	}
	if (isInSameRow(pos))
	{
		retVal.push_back(PositionalRelation::sameRow);
	}
	if (isInSameCol(pos))
	{
		retVal.push_back(PositionalRelation::sameCol);
	}

	return retVal;
}

bool FightPos::isInSameRow(FightPos pos)
{
	return (squadPos.getY() == pos.squadPos.getY()) && isOnSameSide(pos);
}
bool FightPos::isInSameCol(FightPos pos)
{
	return (squadPos.getX() == pos.squadPos.getX()) && isOnSameSide(pos);

}

bool FightPos::isOnSameSide(FightPos pos)
{
	return attackingSide == pos.attackingSide;
}

bool FightPos::isInFrontOf(FightPos pos)
{
	if (isInSameRow(pos))
	{
		return squadPos.getX() > pos.squadPos.getX();
	}
	else
	{
		return false;
	}
}
bool FightPos::isBehind(FightPos pos)
{
	if (isInSameRow(pos))
	{
		return squadPos.getX() < pos.squadPos.getX();
	}
	else
	{
		return false;
	}
}

FightPos FightPos::getPosBehind()
{
	if (squadPos.getX() != SquadColCoord::front)
	{
		throw new std::exception();
	}
	return FightPos(SquadPos(SquadColCoord::back, squadPos.getY()), attackingSide);
}

bool FightPos::isEqual(FightPos comp)
{
	if (squadPos == comp.squadPos && (attackingSide == comp.attackingSide))
	{
		return true;
	}
	else
	{
		return false;
	}
}