#include "NaturalSelection.h"


NaturalSelection::NaturalSelection()
{
	tag = TraitTag::enumNaturalSelection;
	affectedFriendlies = TraitAffectedUnits::sameSpot;
}

TargetingType NaturalSelection::changePrimaryTargetingType(TargetingType normalTargetingType)
{
	return TargetingType::leastHP;
}