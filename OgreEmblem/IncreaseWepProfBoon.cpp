#include "IncreaseWepProfBoon.h"
#include "ReactionStage.h"
#include "Fight.h"
#include "Unit.h"
#include "FightResults.h"

IncreaseWepProfBoon::IncreaseWepProfBoon(BoonTag bTag, int WPinc)
{
	tag = bTag;
	WPincrease = WPinc;
	traitTag = TraitTag::enumIncreaseWepProfBoon;
}
bool IncreaseWepProfBoon::reactToUnitAboutToBeAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults)
{
	if (aStage->defenderID == ownID)
	{
		aStage->defenderWepProfLevel = aStage->defenderWepProfLevel + WPincrease;
	}
	if (aStage->attackerID == ownID)
	{
		aStage->attackerWepProfLevel = aStage->attackerWepProfLevel + WPincrease;
	}

	return true;
}