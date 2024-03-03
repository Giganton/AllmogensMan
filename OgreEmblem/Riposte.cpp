#include "Riposte.h"
#include "FightResults.h"
#include "Fight.h"
#include "Unit.h"

Riposte::Riposte()
{
	name = "Riposte";
	targetingType = TargetingType::melee;
	tag = ActionTag::Riposte;

	unitBeingAttacked_posRelTriggers = { PositionalRelation::samePos };
	unitHavingBeenAttacked_posRelTriggers = { PositionalRelation::samePos };
	//isBlocking = true;
}

bool Riposte::reactToUnitAboutToBeAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults)
{
	if (aStage->defenderPos.isEqual(ownPos))
	{
		if (nrOfUses < maxxNrOfUses)
		{
			aStage->attackBlocked = true;
			return true;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool Riposte::reactToUnitHavingBeenAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults)
{
	if (aStage->defenderPos.isEqual(ownPos))
	{
		ActionResults retVal;
		Targets target = Targets(std::make_pair(aStage->attackerPos, aStage->attackerID), {});
		std::vector<Targets> targets;
		targets.push_back(target);

		int id = activeFight->findFighter(ownPos)->getID();
		if (nrOfUses < 1)
		{

			if (activeFight->findFighter(aStage->attackerPos)->isDead() || activeFight->findFighter(ownPos)->isDead())
			{
				retVal = ActionResults();
			}
			else
			{
				retVal = ActionResults(tag, id, ownPos, targets);
				retVal.actionDidResolve();
				//retVal.addInstanceNr(activeFight->takeInstanceNr()); 
				int atkWP, defWP;
				activeFight->attackTarget(ownPos, aStage->attackerPos, &retVal, &atkWP, &defWP);

				nrOfUses = nrOfUses + 1;
			}
		}
		else
		{
			retVal = ActionResults();
		}


		*reactionResults = retVal;
		return true;
	}
	else
	{
		return false;
	}
}

/*bool Riposte::reactToSelfBeingAttacked(Fight* activeFight, FightPos attackingPos, FightPos defendingPos, FightPos ownPos, ActionResults* reactionResults, AttackStage* stagedAttack)
{
	if (nrOfUses < maxxNrOfUses)
	{
		stagedAttack->attackBlocked = true;
		return true;
	}
	else
	{
		return true;
	}
}*/

/*bool Riposte::isTriggingAttackBlocked()
{
	return (nrOfUses < 1);
}*/

/*bool Riposte::reactToSelfHavingBeenAttacked(Fight* activeFight, FightPos attackingPos, FightPos defendingPos, FightPos ownPos, ActionResults* reactionResults)
{
	ActionResults retVal;
	Targets target = Targets(std::make_pair(attackingPos, activeFight->getFightScenePtr()->getUnitID_unsafe(attackingPos)), {});
	std::vector<Targets> targets;
	targets.push_back(target);

	int id = activeFight->findFighter(ownPos)->getID();
	if (nrOfUses < 1)
	{

		if (activeFight->findFighter(attackingPos)->isDead() || activeFight->findFighter(ownPos)->isDead())
		{
			retVal = ActionResults();
		}
		else
		{
			retVal = ActionResults(tag, id, ownPos, targets);
			retVal.actionDidResolve();
			//retVal.addInstanceNr(activeFight->takeInstanceNr());
			std::vector<FightEffect> effects = activeFight->attackTarget(ownPos, attackingPos, retVal.getInstancesPtr(), retVal.getReActionResultsPtr());
			retVal.addFightEffect(effects);

			nrOfUses = nrOfUses + 1;
		}
	}
	else
	{
		retVal = ActionResults();
	}
	

	*reactionResults = retVal;
	return true;
}*/