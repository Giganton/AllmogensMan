#include "DeathReaction.h"
#include "FightResults.h"
#include "Fight.h"
#include "Unit.h"

DeathReaction::DeathReaction()
{
	tag = ActionTag::DeathReaction;
}

bool DeathReaction::reactToUnitTakingDamage(Fight* activeFight, FightPos ownPos, int ownID, DealDamageStage* dmgStage, ActionResults* reactionResults)
{
	Unit* unit = activeFight->findFighter(ownID);
	if (unit->getHP() <= 0)
	{
		;// activeFight->killUnit(unit, ownPos, )
	}
	return false;
}