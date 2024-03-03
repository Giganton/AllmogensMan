#include "Gains.h"

Gains::Gains()
{
	tag = TraitTag::enumGains;
	affectedFriendlies = TraitAffectedUnits::sameSpot;
}

UnitStatistics Gains::applyToStats(UnitStatistics stats)
{
	UnitStatistics newStats = stats;
	newStats.attack = stats.attack + plusValue;
	newStats.defense = stats.defense + plusValue;
	return newStats;
}