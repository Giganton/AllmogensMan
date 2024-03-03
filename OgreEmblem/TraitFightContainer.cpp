#include "TraitFightContainer.h"
#include "Squad.h"
#include "PassiveBoon.h"

BoonFightProperties::BoonFightProperties(const BoonFightProperties& cp)
{
	trait = cp.trait->clone();
	unitPos = cp.unitPos;
}

BoonFightProperties& BoonFightProperties::operator=(const BoonFightProperties cp)
{
	trait = cp.trait->clone();
	unitPos = cp.unitPos;

	return *this;
}

BoonFightProperties::BoonFightProperties(PassiveBoon* trt, FightPos mapPos)
{ 
	trait = trt->clone(); 
	unitPos = mapPos; 
}

bool BoonFightProperties::doesItAffectThisPos(FightPos mapPos, Squad* attackers, Squad* defenders)
{
	TraitAffectedUnits method;
	int posHP, posMaxHP;
	if (mapPos.attackingSide)
	{
		posHP = attackers->getUnitPtr(mapPos.squadPos)->getHP();
		posMaxHP = attackers->getUnitPtr(mapPos.squadPos)->getMaxHP();
		if (unitPos.attackingSide)
		{
			method = trait->getAffectedFriendlies();
		}
		else
		{
			method = trait->getAffectedEnemies();
		}
	}
	else
	{
		posHP = defenders->getUnitPtr(mapPos.squadPos)->getHP();
		posMaxHP = defenders->getUnitPtr(mapPos.squadPos)->getMaxHP();
		if (!unitPos.attackingSide)
		{
			method = trait->getAffectedFriendlies();
		}
		else
		{
			method = trait->getAffectedEnemies();
		}
	}
	switch (method)
	{
	case TraitAffectedUnits::none:
		return false;
	case TraitAffectedUnits::all:
		return true;
	case TraitAffectedUnits::backColumn:
		return mapPos.squadPos.getX() == SquadColCoord::back;
	case TraitAffectedUnits::frontColumn:
		return mapPos.squadPos.getX() == SquadColCoord::front;
	case TraitAffectedUnits::inDanger:
		return  posHP < (posMaxHP / 2);
	case TraitAffectedUnits::sameSpot:
		return mapPos.squadPos == unitPos.squadPos;
	default:
		throw new std::exception();
		return false;
	}
}

void BoonFightContainer::addTrait(BoonFightProperties trait)
{
	traitList.push_back(trait);
}

void BoonFightContainer::addTrait(PassiveBoon* trait, FightPos mapPos)
{
	addTrait(BoonFightProperties(trait, mapPos));
}

BoonFightContainer BoonFightContainer::traitsThatAffectThisPos(FightPos mapPos, Squad* attackers, Squad* defenders)
{
	BoonFightContainer retVal;
	unsigned int i;
	for (i = 0; i < traitList.size(); i++)
	{
		BoonFightProperties trait = traitList.at(i);
		bool temp;
		if (trait.doesItAffectThisPos(mapPos, attackers, defenders))
		{
			retVal.addTrait(trait);
		}
	}
	return retVal;
}