#include "Martyr.h"
#include "Fight.h"
#include "Unit.h"
#include "Squad.h"
#include "ActionSpecifics.h"


Martyr::Martyr()
{
	name = "Martyr";
	tag = ActionTag::Martyr;

	unitBeingAttacked_posRelTriggers = { PositionalRelation::neighbour };
	unitDying_posRelTriggers = { PositionalRelation::samePos };
	//isBlocking = true;
}

bool Martyr::reactToUnitAboutToBeAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults)
{
	if (doesPRvecAcontainPRvecB(aStage->defenderPos.getRelations(ownPos), { PositionalRelation::neighbour }))
	{
		if (!activated)
		{
			Targets target = Targets(std::make_pair(aStage->defenderPos, aStage->defenderID), {});
			std::vector<Targets> targetList;
			targetList.push_back(target);


			ActionResults results = ActionResults(tag, activeFight->findFighter(ownPos)->getID(), ownPos, targetList);
			results.addSpecifics(MartyrSpecifics::ms_jumpingTo);

			//Squad* defendingSquad = activeFight->getDefenders();
			FightScene* scene = activeFight->getFightScenePtr();
			results.getInstancesPtr()->push_back(activeFight->takeInstanceNr());

			aStage->defenderID = scene->getUnitOnPos(ownPos)->getID();

			// lägg till posförflyttning i fighten så att den kan hanteras rätt
			//defendingSquad->swapUnits(aStage->defenderPos.squadPos, ownPos.squadPos);
			tempUnitSpace.push_back(*scene->getUnitOnPos(aStage->defenderPos));
			scene->exileUnitOnPos(aStage->defenderPos);
			scene->moveUnit(ownPos, aStage->defenderPos);
			posTransformTag = activeFight->getNewPosTransformTag();
			activeFight->addPosTransform(posTransformTag, aStage->defenderPos, ownPos, ReactionTrigger::postBattle, this);

			//Unit exiledUnit = defendingSquad->removeUnit(ownPos.squadPos);
			//tempUnitSpace.push_back(exiledUnit);

			//activeFight->addToExile({ tempUnitSpace });
			results.actionDidResolve();
			activated = true;

			oldSelfPos = ownPos;
			oldOtherPos = aStage->defenderPos;

			*reactionResults = results;

			return true;
		}

		else
		{
			return false;
		}
	}
	return false;
}

bool Martyr::cleanupPositionalChanges(Fight* activeFight, ActionResults* reactionResults)
{
	if (activated && !cleanedUp)
	{
		FightPos transformedSelfPos = activeFight->transformPosByTag(posTransformTag, oldSelfPos);
		FightPos transformedOtherPos = activeFight->transformPosByTag(posTransformTag, oldOtherPos);

		Targets target = Targets(std::make_pair(transformedSelfPos, activeFight->getFightScenePtr()->getUnitID_unsafe(transformedSelfPos)) , {});
		std::vector<Targets> targetList = { target };
		ActionResults results = ActionResults(tag, ownerID, oldSelfPos, targetList);

		results.actionDidResolve();
		results.addSpecifics(MartyrSpecifics::ms_jumpingHome);

		if (martyrDied)
		{
			results.addSpecifics(MartyrSpecifics::ms_martyrDied);
		}
		else
		{
			results.addSpecifics(MartyrSpecifics::ms_martyrSurvived);
		}

		//Squad* defendingSquad = activeFight->getDefenders();
		//Unit unitThatIsBack = activeFight->takeFromExile(tempUnitSpace.at(0).getID()).at(0);

		FightScene* scene = activeFight->getFightScenePtr();
		scene->moveUnit(transformedOtherPos, transformedSelfPos);
		scene->returnFromExile(tempUnitSpace.at(0).getID(), transformedOtherPos);

		activeFight->removePosTransform(posTransformTag);

		//defendingSquad->addUnit(unitThatIsBack, transformedSelfPos.squadPos);
		//defendingSquad->swapUnits(transformedOtherPos.squadPos, transformedSelfPos.squadPos);

		results.getInstancesPtr()->push_back(activeFight->takeInstanceNr());

		tempUnitSpace.clear();
		activated = false;

		*reactionResults = results;
		cleanedUp = true;

		return true;
	}
	else
	{
		return false;
	}
}
void Martyr::postFightCleanup()
{
	oldSelfPos = FightPos();
	oldOtherPos = FightPos();

	posTransformTag = -1;

	tempUnitSpace.clear();
	activated = false;
	cleanedUp = false;
	martyrDied = false;
}

bool Martyr::reactToUnitDying(Fight* activeFight, FightPos ownPos, int ownID, DeathStage* dStage, ActionResults* reactionResults)
{
	if (dStage->dyingUnitPos.isEqual(ownPos))
	{
		if (activated && !cleanedUp)
		{
			martyrDied = true;
			cleanupPositionalChanges(activeFight, reactionResults);
			return true;
		}
	}

	return false;
}

/*bool Martyr::reactToSelfDying(Fight* activeFight, FightPos ownPos, ActionResults* reactionResults)
{
	if (activated && !cleanedUp)
	{
		cleanupPositionalChanges(activeFight, reactionResults);
		return true;
	}
	return false;
}*/

/*bool Martyr::reactToAllyHavingBeenAttacked(Fight* activeFight, FightPos attackingPos, FightPos defendingPos, FightPos ownPos, ActionResults* reactionResults)
{
	if (activated)
	{
		Targets target = Targets(defendingPos, {});
		std::vector<Targets> targetList = { };
		ActionResults results = ActionResults(tag, activeFight->findFighter(ownPos)->getID(), ownPos, targetList);

		Squad* defendingSquad = activeFight->getDefenders();
		activeFight->takeFromExile(tempUnitSpace.at(0).getID());
		defendingSquad->addUnit(tempUnitSpace.at(0), ownPos.squadPos);
		defendingSquad->swapUnits(defendingPos.squadPos, ownPos.squadPos);

		tempUnitSpace.clear();
		activated = false;

		*reactionResults = results;

		return true;
	}
	else
	{
		return false;
	}
}*/

/*bool Martyr::reactToEndOfFight_Mandatory(Fight* activeFight, FightPos attackingPos, FightPos ownPos, ActionResults* reactionResults)
{
	if (activated && !cleanedUp)
	{
		cleanupPositionalChanges(activeFight, reactionResults);
		return true;
	}
	return false;
}*/

/*bool Martyr::reactToDamageBeingTakenByAlly(Fight* activeFight, FightPos damagedPos, FightPos ownPos, ActionResults* reactionResults, DealDamageChangeables* damageResults)
{
	if (damageResults->damageRedirected)
	{
		return false;
	}
	else
	{
		std::vector<Targets> targets = { Targets(damagedPos, {}) };
		ActionResults results = ActionResults(tag, activeFight->findFighter(ownPos)->getID(), ownPos, targets);
		results.actionDidResolve();

		damageResults->damageRedirected = true;
		damageResults->redirectedTarget = activeFight->findFighter(ownPos);

		*reactionResults = results;

		return true;
	}
}*/