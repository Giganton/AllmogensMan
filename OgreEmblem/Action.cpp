#include "Action.h"
#include "Squad.h"
//#include "SquadPos.h"
#include "Unit.h"
#include "FightResults.h"
#include<map>
#include "FightUtils.h"
#include "Fight.h"
#include "ReactionStage.h"
#include<time.h>
#include<chrono>
#include "allActions.h"

Action* createAction(ActionTag tag)
{
	switch (tag)
	{
	case ActionTag::Strike:
		return new Strike();
		break;
	case ActionTag::Blast:
		return new Blast();
		break;
	case ActionTag::LightningStrike:
		return new LightningStrike();
		break;
	//python-entry createAction
	default:
		throw new std::exception();
	}
}

ReAction* createReAction(ActionTag tag)
{
	switch (tag)
	{
	case ActionTag::Martyr:
		return new Martyr();
		break;
	case ActionTag::Riposte:
		return new Riposte();
		break;
	case ActionTag::Rage:
		return new Rage();
		break;
	case ActionTag::DeathReaction:
		return new DeathReaction();
		break;
	default:
		throw new std::exception();
	}
}

ActionResults Action::execute(FightPos executorPos, Fight* activeFight)
{
	std::vector<Targets> targets = findTargets(executorPos, activeFight);
	ActionResults retVal = prepareActionResults(executorPos, activeFight, targets);
	retVal = performAction(activeFight->findFighter(executorPos)->getID(),targets, activeFight, retVal);
	//resultFrame.addFightEffect(effects);

	return retVal;
}

/*bool ReAction::attemptReaction_UnitBeingAttacked(Fight* activeFight, FightPos ownPos, AttackStage* aStage, ActionResults* reactionResults)
{
	bool retVal = false;
	std::vector<PositionalRelation> relations = aStage->defenderPos.getRelations(ownPos);

	if (doesPRvecAcontainPRvecB(relations, unitBeingAttacked_posRelTriggers))
	{
		retVal = reactToUnitAboutToBeAttacked(activeFight, ownPos, aStage, reactionResults);
	}

	return retVal;
}

bool ReAction::attemptReaction_UnitHavingBeenAttacked(Fight* activeFight, FightPos ownPos, AttackStage* aStage, ActionResults* reactionResults)
{
	bool retVal = false;
	std::vector<PositionalRelation> relations = aStage->defenderPos.getRelations(ownPos);

	if (doesPRvecAcontainPRvecB(relations, unitHavingBeenAttacked_posRelTriggers))
	{
		retVal = reactToUnitHavingBeenAttacked(activeFight, ownPos, aStage, reactionResults);
	}

	return retVal;
}

bool ReAction::attemptReaction_UnitDying(Fight* activeFight, FightPos ownPos, DeathStage* dStage, ActionResults* reactionResults)
{
	bool retVal = false;
	std::vector<PositionalRelation> relations = dStage->dyingUnitPos.getRelations(ownPos);

	if (doesPRvecAcontainPRvecB(relations, unitDying_posRelTriggers))
	{
		retVal = reactToUnitDying(activeFight, ownPos, dStage, reactionResults);
	}
	return retVal;
}

bool ReAction::attemptReaction_EndOfBattle(Fight* activeFight, FightPos ownPos, ActionResults* reactionResults)
{
	return reactToEndOfBattle(activeFight, ownPos, reactionResults);
}*/

/*bool ReAction::reactToUnitDying(Fight* activeFight, FightPos ownPos, DeathStage* dStage, ActionResults* reactionResults)
{
	return false;
}

bool ReAction::reactToEndOfBattle(Fight* activeFight, FightPos ownPos, ActionResults* reactionResults)
{
	return false;
}

bool ReAction::reactToUnitTakingDamage(Fight* activeFight, FightPos ownPow, DealDamageStage* dmgStage, ActionResults* reactionResults)
{
	return false;
}

bool ReAction::reactToUnitAboutToBeAttacked(Fight* activeFight, FightPos ownPos, AttackStage* aStage, ActionResults* reactionResults)
{
	return false;
}

bool ReAction::reactToUnitHavingBeenAttacked(Fight* activeFight, FightPos ownPos, AttackStage* aStage, ActionResults* reactionResults)
{
	return false;
}*/
/*
bool ReAction::reactToNeighbourBeingAttacked(Fight* activeFight, FightPos ownPos, AttackStage* aStage, ActionResults* reactionResults)
{
	return false;
}

bool ReAction::reactToSelfBeingAttacked(Fight* activeFight, FightPos attackingPos, FightPos defendingPos, FightPos ownPos, ActionResults* reactionResults, AttackStage* stagedAttack)
{
	return false;
}
bool ReAction::reactToDamageBeingTakenByAlly(Fight* activeFight, FightPos damagedPos, FightPos ownPos, ActionResults* reactionResults, DealDamageChangeables* damageResults)
{
	return false;
}

bool reactToDamageBeingTakenByAlly(Fight* activeFight, FightPos damagedPos, FightPos ownPos, ActionResults* reactionResults)
{
	return false;
}

bool ReAction::reactToSelfHavingBeenAttacked(Fight* activeFight, FightPos attackingPos, FightPos defendingPos, FightPos ownPos, ActionResults* reactionResults)
{
	return false;
}

bool ReAction::reactToAllyHavingBeenAttacked(Fight* activeFight, FightPos attackingPos, FightPos defendingPos, FightPos ownPos, ActionResults* reactionResults)
{
	return false;
}

bool ReAction::reactToNeighbourHavingBeenAttacked(Fight* activeFight, FightPos attackingPos, FightPos defendingPos, FightPos ownPos, ActionResults* reactionResults)
{
	return false;
}

bool ReAction::reactToSelfDying(Fight* activeFight, FightPos ownPos, ActionResults* reactionResults)
{
	return false;
}

bool ReAction::reactToAllyDying(Fight* activeFight, FightPos ownPos, ActionResults* reactionResults)
{
	return false;
}

bool ReAction::reactToNeighbourDying(Fight* activeFight, FightPos ownPos, ActionResults* reactionResults)
{
	return false;
}*/

bool ReAction::reactToEndOfFight_Mandatory(Fight* activeFight, FightPos attackingPos, FightPos ownPos, ActionResults* reactionResults)
{
	return false;
}
/*ActionResults ReAction::performAction(std::vector<Targets> targets, Fight* activeFight, ActionResults resultsFrame)
{ 
	throw new std::exception();
	return ActionResults(); 
}*/

std::vector<FightPos> Action::findPrimaryTargetPos(FightPos attackerPos, Fight* activeFight, TargetingType targetingMethod)
{
	std::vector<SpotPosition> targetPriority;
	FightPos temp;
	switch (targetingMethod)
	{
	case TargetingType::melee:
		return std::vector<FightPos>{findFirstOccupiedSpot(meleeTargetPriority(attackerPos.squadPos), activeFight->getFightScenePtr(), !attackerPos.attackingSide) };
		break;
	case TargetingType::magical:
		temp = findFirstOccupiedSpot(magicalTargetPriority(attackerPos.squadPos), activeFight->getFightScenePtr(), !attackerPos.attackingSide);
		if (temp.squadPos.getX() == -1 && temp.squadPos.getY() == -1)
		{
			return std::vector<FightPos>{};
		}
		else
		{
			return std::vector<FightPos>{ temp };
		}
		break;
	case TargetingType::leastHP:
		return std::vector<FightPos>{FightPos(findLeastHPSpot(activeFight->getFightScenePtr(), !attackerPos.attackingSide)) };
		break;
	case TargetingType::random:
		return pickRandomOccupiedByLivingSpot(activeFight->getFightScenePtr(), !attackerPos.attackingSide);
		break;
	default:
		throw new std::exception();
		return std::vector<FightPos>();
	}
}

std::vector<FightPos> BaseAction::pickRandomOccupiedByLivingSpot(FightScene* formation, bool attackingSide)
{
	std::vector<FightPos> livingUnitPos = formation->getAllLivingUnitPositions(attackingSide);
	std::vector<FightPos> retVal;
	if (livingUnitPos.size() > 0)
	{
		int randInd = rand() % livingUnitPos.size();
		//SquadPos position = formation->whereIsThisUnit(livingUnits.at(randInd)->getID());
		retVal.push_back(livingUnitPos.at(randInd));
	}
	return retVal;
}

ActionResults Action::prepareActionResults(FightPos pos, Fight* fight, std::vector<Targets> targets)
{
	ActionResults retVal;
	Unit* attackingUnit = fight->findFighter(pos);

	retVal.setActionTag(getTag());
	retVal.setActivatorID(attackingUnit->getID());
	retVal.setActivatorPos(pos);
	if (targets.size() > 0)
	{
		retVal.actionDidResolve();
	}
	retVal.setTargets(targets);
	std::vector<std::vector<bool>> primaryTargetIsDead;
	std::vector<std::vector<bool>> secondaryTargetIsDead;

	return retVal;
}

std::vector<Targets> Action::findTargets(FightPos attackerPos, Fight* activeFight)
{
	unsigned int i, j;
	std::vector<Targets> retVal;
	TargetingType method = targetingType;
	/*std::vector<BoonFightProperties> traitList = traits.getTraits();
	for (i = 0; i < traitList.size(); i++)
	{
		method = traitList.at(i).trait->changePrimaryTargetingType(targetingType);
	}*/

	std::vector<FightPos> primaryPos = findPrimaryTargetPos(attackerPos, activeFight, method);
	
	for (i = 0; i < primaryPos.size(); i++)
	{
		std::vector<FightPos> secondariesPos = getSecondaryTargets(primaryPos.at(i), activeFight);
		std::vector<std::pair<FightPos, int>> secondaryTargets;
		for (j = 0; j < secondariesPos.size(); j++)
		{
			int secondaryID = -1;
			if (activeFight->getFightScenePtr()->isPosOccupied(secondariesPos.at(j)))
			{
				secondaryID = activeFight->getFightScenePtr()->getUnitOnPos(secondariesPos.at(j))->getID();
			}
			secondaryTargets.push_back(std::make_pair( secondariesPos.at(j) , secondaryID ));
		}
		int primaryID = -1;
		if (activeFight->getFightScenePtr()->isPosOccupied(primaryPos.at(i)))
		{
			primaryID = activeFight->getFightScenePtr()->getUnitOnPos(primaryPos.at(i))->getID();
		}
		std::pair<FightPos, int> primaryTarget = (std::make_pair(primaryPos.at(i), primaryID));

		retVal.push_back(Targets(primaryTarget , secondaryTargets ));
	}
	return retVal;
}

FightPos BaseAction::findFirstOccupiedSpot(std::vector<SquadPos> targetPriority, FightScene* formation, bool attackingSide)
{
	unsigned int i, j, k;
	for (i = 0; i < targetPriority.size(); i++)
	{
		FightPos pos = FightPos(targetPriority.at(i), attackingSide);
		if (formation->isPosOccupied(pos) && !formation->getUnitOnPos(pos)->isDead())
		{
			return pos;
		}
	}
	return FightPos();
}

std::vector<SquadPos> BaseAction::findAllOccupiedSpots(std::vector < SquadPos > targets, Squad* formation)
{
	unsigned int i;
	std::vector<SquadPos> retVal;
	for (i = 0; i < targets.size(); i++)
	{
		if (!formation->getTile(targets.at(i))->isEmpty() && !formation->getUnitPtr(targets.at(i))->isDead())
		{
			retVal.push_back(targets.at(i));
		}
	}
	return retVal;

}

std::vector<SquadPos> BaseAction::meleeTargetPriority(SquadPos mapPos)
{
	std::vector<SquadPos> retVal;
	unsigned int i;
	if (mapPos.getY() == SquadRowCoord::mid)
	{
		for (i = 0; i < 2; i++)
		{
			int column = 1 - i;
			retVal.push_back(SquadPos(column, mapPos.getY()));
			int randNr = rand() % 1;
			SquadPos posTop = SquadPos(column, SquadRowCoord::top);
			SquadPos posBot = SquadPos(column, SquadRowCoord::bot);
			if (randNr == 1)
			{
				retVal.push_back(posTop);
				retVal.push_back(posBot);
			}
			else
			{
				retVal.push_back(posBot);
				retVal.push_back(posTop);
			}
		}
	}
	else
	{
		retVal.push_back(SquadPos(SquadColCoord::front, mapPos.getY()));
		retVal.push_back(SquadPos(SquadColCoord::front, SquadRowCoord::mid));
		retVal.push_back(SquadPos(SquadColCoord::back, mapPos.getY()));
		retVal.push_back(SquadPos(SquadColCoord::back, SquadRowCoord::mid));
		retVal.push_back(SquadPos(SquadColCoord::back, getOpposite(mapPos.getY())));
		retVal.push_back(SquadPos(SquadColCoord::front, getOpposite(mapPos.getY())));
	}
	return retVal;
}

std::vector<SquadPos> BaseAction::magicalTargetPriority(SquadPos atkPos)
{
	std::vector<SquadPos> retVal;
	retVal.push_back(SquadPos(getOtherColumn(atkPos.getX()), atkPos.getY()));
	retVal.push_back(atkPos);
	return retVal;
}

FightPos BaseAction::findLeastHPSpot(FightScene* formation, bool atkSide)
{
	int leastHP = 99999;
	FightPos leastHPSpot;
	int i, j;
	for (i = 0; i < TACTICAL_X; i++)
	{
		for (j = 0; j < TACTICAL_Y; j++)
		{
			FightPos testSpot = FightPos(SquadPos(i, j), atkSide);
			if (formation->isPosOccupied(testSpot) && leastHP > formation->getUnitOnPos(testSpot)->getHP())
			{
				leastHP = formation->getUnitOnPos(testSpot)->getHP();
				leastHPSpot = testSpot;
			}
		}
	}
	return leastHPSpot;
}