#include "FightUtils.h"
#include "Unit.h"
#include "Squad.h"
/*
int F_UTIL::dealDamage(int attackDamage, SquadPos damagedSpot, bool damagedUnitIsAttacking, Squad* attackingSquad, Squad* defendingSquad, BoonFightContainer traits)
{
	unsigned int i;
	Squad* damagedSquad = defendingSquad;
	if (damagedUnitIsAttacking)
	{
		damagedSquad = attackingSquad;
	}
	Unit* unit = damagedSquad->getUnitPtr(damagedSpot);
	int defenseReduction = unit->getDefense();
	BoonFightContainer filteredTraits = traits.traitsThatAffectThisPos(damagedSpot, damagedUnitIsAttacking, attackingSquad, defendingSquad);
	for (i = 0; i < filteredTraits.getSize(); i++)
	{
		defenseReduction = filteredTraits.getTraitProp(i).trait->applyToDefenseValue(defenseReduction);
	}
	int reducedDamage = attackDamage - defenseReduction;
	if (reducedDamage < 0)
	{
		reducedDamage = 0;
	}
	unit->dealDamage(reducedDamage);
	return reducedDamage;
}

int F_UTIL::attackTarget(SquadPos attackingSpot, Squad* attackingSquad, SquadPos defendingSpot, Squad* defendingSquad, BoonFightContainer traits)
{
	unsigned int i;
	Unit* defendingUnit = defendingSquad->getUnitPtr(defendingSpot);
	Unit* attackingUnit = attackingSquad->getUnitPtr(attackingSpot);

	BoonFightContainer filteredTraits = traits.traitsThatAffectThisPos(attackingSpot, true, attackingSquad, defendingSquad);

	int attackValue = attackingUnit->getStatistics().attack;
	for (i = 0; i < filteredTraits.getSize(); i++)
	{
		BoonFightProperties trait = filteredTraits.getTraitProp(i);
		if (trait.attacker)
		{
			attackValue = trait.trait->applyToDealtAttackDamage(attackValue);
		}
	}

	int finalDamage = F_UTIL::dealDamage(attackValue, defendingSpot, false, attackingSquad, defendingSquad, traits);
	return finalDamage;
}*/