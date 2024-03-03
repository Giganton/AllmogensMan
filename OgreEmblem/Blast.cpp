#include "Blast.h"
#include "Squad.h"
#include "Unit.h"
#include "FightResults.h"
#include "Fight.h"

Blast::Blast()
{
	name = "Blast";
	targetingType = TargetingType::magical;
	tag = ActionTag::Blast;
}

ActionResults Blast::performAction(int userID, std::vector<Targets> targets, Fight* activeFight, ActionResults resultsFrame)
{
	unsigned int i,j;
	ActionResults retVal2;
	//FightEffect partialEffect;
	int inst = activeFight->takeInstanceNr();
	resultsFrame.addInstanceNr(inst);
	for (i = 0; i < targets.size(); i++)
	{
		Unit* primaryTarget = activeFight->findFighter(targets.at(i).getPrimaryTarget().first);
		activeFight->dealDamage(primaryDamage, targets.at(i).getPrimaryTarget().second, userID, inst, &resultsFrame, TraitTag::enumTraitNone);

		for (j = 0; j < targets.at(i).getSecondaryTargets().size(); j++)
		{
			Unit* secondaryTarget = activeFight->findFighter(targets.at(i).getSecondaryTargets().at(j).first);
			activeFight->dealDamage(areaFraction * primaryDamage, targets.at(i).getSecondaryTargets().at(j).second, userID, inst, &resultsFrame, TraitTag::enumTraitNone);
		}
	}

	return resultsFrame;
}

std::vector<FightPos> Blast::getSecondaryTargets(FightPos defenderPos, Fight* activeFight)
{
	return activeFight->getAllOccupiedNeighbours(defenderPos);
}