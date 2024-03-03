#include "PlusDefense.h"

PlusDefense::PlusDefense()
{ 
	tag = TraitTag::enumPlusDefense;
	affectedFriendlies = TraitAffectedUnits::sameSpot;
}

int PlusDefense::applyToDefenseValue(int defense)
{
	return defense + plusValue;
}