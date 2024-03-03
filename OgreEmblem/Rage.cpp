#include "Rage.h"
#include "FightResults.h"
#include "Fight.h"
#include "Unit.h"

Rage::Rage()
{
	targetingType = TargetingType::random;
	tag = ActionTag::Rage;
}

bool Rage::reactToUnitTakingDamage(Fight* activeFight, FightPos ownPos, int ownID, DealDamageStage* dmgStage, ActionResults* reactionResults)
{
	if (dmgStage->takerID == ownID)
	{
		std::vector<Targets> targets;
		std::vector<FightPos> randomPos = pickRandomOccupiedByLivingSpot(activeFight->getFightScenePtr(), !ownPos.attackingSide);
		if (randomPos.size() > 0)
		{
			int targetID = activeFight->findFighter(randomPos.at(0))->getID();
			targets.push_back(Targets(std::make_pair(randomPos.at(0), targetID), {}));

			ActionResults results = ActionResults(tag, ownID, ownPos, targets);
			results.actionDidResolve();

			int atkWP, defWP;
			//std::vector<FightEffect> effects = activeFight->attackTarget(ownPos, randomPos.at(0), results.getInstancesPtr(), results.getReActionResultsPtr(), &atkWP, &defWP);
			activeFight->attackTarget(ownPos, randomPos.at(0), &results, &atkWP, &defWP);

			*reactionResults = results;
			return true;
		}
	}
	*reactionResults = ActionResults();
	return false;
}