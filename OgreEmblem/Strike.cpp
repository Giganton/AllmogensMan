#include "Strike.h"
#include "Action.h"
#include "Squad.h"
#include "Unit.h"
#include "FightResults.h"
#include "FightUtils.h"

Strike::Strike()
{
	name = "Strike";
	targetingType = TargetingType::melee;
	tag = ActionTag::Strike;
}

ActionResults Strike::performAction(int userID, std::vector<Targets> targets, Fight* activeFight, ActionResults resultsFrame)
{
	unsigned int i, j, k;
	Unit* attacker = activeFight->getAttackingUnit();
	for (i = 0; i < targets.size(); i++)
	{
		FightPos primaryTarget = targets.at(i).getPrimaryTarget().first;
		int nrOfAttacks = 1;

		for (j = 0; j < nrOfAttacks; j++)
		{
			//partialEffect = FightEffect(targetedUnit->getID(), primaryTarget,j+1, TraitTag::enumTraitNone);
			//int finalDamage = activeFight->attackTarget(activeFight->getAttackingPos(), primaryTarget, &partialEffect.affectedDied);
			//resultsFrame.addInstanceNr(activeFight->takeInstanceNr());
			int attackerWepProfLevel = -1;
			int defenderWepProfLevel = -1;
			Unit* targetedUnit = activeFight->findFighter(primaryTarget);
			if (targetedUnit->isDead())
			{
				break;
			}
			activeFight->attackTarget(activeFight->findPosition(userID), primaryTarget, &resultsFrame, &attackerWepProfLevel, &defenderWepProfLevel);
			//partialEffect.damageTaken = finalDamage;
			if (attackerWepProfLevel - defenderWepProfLevel > 2)
			{
				nrOfAttacks = 2;
			}
		}
	}

	return resultsFrame;
}