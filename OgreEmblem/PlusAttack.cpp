#include "PlusAttack.h"


PlusAttack::PlusAttack() 
{ 
	tag = TraitTag::enumPlusAttack;
	affectedFriendlies = TraitAffectedUnits::sameSpot;
}

/*int PlusAttack::applyToDealtAttackDamage(int incomingDamage)
{
	return incomingDamage + plusValue;
}*/

UnitStatistics PlusAttack::applyToStats(UnitStatistics stats)
{
	UnitStatistics newStats = stats;
	newStats.attack = stats.attack + plusValue;
	return newStats;
}