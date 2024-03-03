#include "HeavyArmor.h"
#include "ReactionStage.h"
#include "Fight.h"
#include "Unit.h"
#include "FightResults.h"

HeavyArmor::HeavyArmor()
{
	tag = BoonTag::enumHeavyArmor;
	traitTag = TraitTag::enumHeavyArmor;
}

bool HeavyArmor::modifyUnitBeingAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults)
{
	if (aStage->defenderID == ownID)
	{
		aStage->defenderWepProfLevel = aStage->defenderWepProfLevel - 1;

		return true;
	}
	if (aStage->attackerID == ownID)
	{
		aStage->attackerWepProfLevel = aStage->attackerWepProfLevel - 1;

		return true;
	}

	return false;
}

bool HeavyArmor::modifyUnitTakingDamage(Fight* activeFight, FightPos ownPow, int ownID, DealDamageStage* dmgStage, ActionResults* reactionResults)
{
	if (dmgStage->takerID == ownID)
	{
		dmgStage->damageReduction = dmgStage->damageReduction + 2;

		return true;
	}
	return false;
}