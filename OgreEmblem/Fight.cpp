#include "Fight.h"
#include "Squad.h"

std::vector<FightPos> allPositions = {
	FightPos(SquadPos(0, 0),true),
	FightPos(SquadPos(0, 1),true),
	FightPos(SquadPos(0, 2),true),
	FightPos(SquadPos(1, 0),true),
	FightPos(SquadPos(1, 1),true),
	FightPos(SquadPos(1, 2),true),
	FightPos(SquadPos(0, 0),false),
	FightPos(SquadPos(0, 1),false),
	FightPos(SquadPos(0, 2),false),
	FightPos(SquadPos(1, 0),false),
	FightPos(SquadPos(1, 1),false),
	FightPos(SquadPos(1, 2),false) };

Fight::Fight(Squad* attSquad, Squad* defSquad)
{
	attackingSquad = attSquad;
	defendingSquad = defSquad;

	fightScene = FightScene(attSquad, defSquad);

	traitList = organizeTraitList(attackingSquad, defendingSquad);
}

void Fight::setupNextFight(int atkPosX, int atkPosY)
{
	attacker = FightPos(SquadPos(atkPosX, atkPosY), true);
	offensiveAction = attackingSquad->getUnitPtr(atkPosX, atkPosY)->getPrimaryAction();
	ready = true;
}

ActionResults Fight::fight()
{
	if (!ready)
	{
		throw new std::exception();
	}

	//std::vector<Targets> targets = offensiveAction->findTargets(attacker, this);
	//ActionResults retVal = prepareActionResults(targets);

	ActionResults retVal = offensiveAction->execute(attacker, this);

	//retVal = additionalExecutionEffects(retVal, targets);
	
	//checkReactions_EndOfFight(attacker, retVal.getReActionResultsPtr());
	checkReactions(ReactionTrigger::postFight, nullptr, retVal.getReActionResultsPtr(ReactionTiming::post));

	ready = false;
	return retVal;
}

ActionResults Fight::performAction(Unit* unit)
{
	Action* action = unit->getPrimaryAction();
	FightPos activatorPos = findPosition(unit->getID());
	return action->execute(activatorPos, this);
}

ReactionResultsList Fight::battleIsDone()
{
	ReactionResultsList retVal;
	checkReactions(ReactionTrigger::postBattle, nullptr, &retVal);

	return retVal;
}

std::vector<int> Fight::getAllUnitIDs()
{
	std::vector<int> retVal;
	unsigned int i;
	for (i = 0; i < allPositions.size(); i++)
	{
		if (fightScene.isPosOccupied(allPositions.at(i)))
		{
			retVal.push_back(findFighter(allPositions.at(i))->getID());
		}
	}
	for (i = 0; i < exiledZone.size(); i++)
	{
		retVal.push_back(exiledZone.at(i).getID());
	}

	return retVal;
}

Unit* Fight::getAttackingUnit() 
{ 
	return findFighter(FightPos(attacker.squadPos, true)); 
}

UnitStatistics Fight::getUnitStats(FightPos unitPos)
{
	UnitStatistics stats = findFighter(unitPos)->getStatistics();
	unsigned int i;
	for (i = 0; i < traitList.getSize(); i++)
	{
		if (traitList.getTraitProp(i).doesItAffectThisPos(unitPos, attackingSquad, defendingSquad))
		{
			stats = traitList.getTraitProp(i).trait->applyToStats(stats);
		}
	}
	return stats;
}

std::vector<FightPos> Fight::getAllOccupiedNeighbours(FightPos mapPos)
{
	std::vector<SquadPos> nbours = getNeighbours(mapPos.squadPos);
	std::vector<FightPos> retVal;
	unsigned int i;
	for (i = 0; i < nbours.size(); i++)
	{
		if (fightScene.isPosOccupied(FightPos(nbours.at(i), mapPos.attackingSide)))
		{
			retVal.push_back(FightPos(nbours.at(i), mapPos.attackingSide));
		}
	}
	return retVal;
}

Unit* Fight::findFighter(FightPos mapPos)
{
	return fightScene.getUnitOnPos(mapPos);
}

Unit* Fight::findFighter(int id)
{
	return fightScene.getUnitWithID(id);
}

void Fight::addToExile(std::vector<Unit> exiled)
{
	unsigned int i;
	for (i = 0; i < exiled.size(); i++)
	{
		exiledZone.push_back(exiled.at(i));
	}
}

std::vector<Unit> Fight::takeFromExile(int id)
{
	unsigned int i;
	for (i = 0; i < exiledZone.size(); i++)
	{
		if (exiledZone.at(i).getID() == id)
		{
			Unit retVal = exiledZone.at(i);
			exiledZone.erase(exiledZone.begin() + i);
			return { retVal };
		}
	}
	throw new std::exception();
	return { Unit() };
}

bool Fight::isUnitInExile(int id)
{
	return fightScene.isUnitInExile(id);
}


void Fight::addPosTransform(int tag, FightPos pos1, FightPos pos2, ReactionTrigger cleanupTrigger, BaseAction* cleanupReaction)
{
	unsigned int i;
	for (i = 0; i < positionTransforms.size(); i++)
	{
		if (positionTransforms.at(i).getTag() == tag)
		{
			throw new std::exception();
		}
	}
	positionTransforms.push_back(PosTransform(pos1, pos2, tag, cleanupTrigger, cleanupReaction));
}

FightPos Fight::transformPosByTag(int tag, FightPos pos)
{
	int i;
	FightPos retVal = pos;
	for (i = ((int)positionTransforms.size() - 1); i >= 0; i--)
	{
		if (tag == positionTransforms.at(i).getTag())
		{
			return retVal;
		}
		else
		{
			retVal = positionTransforms.at(i).transformOldPosition(retVal);
		}
	}

	throw new std::exception();
	return FightPos();
}

int Fight::getNewPosTransformTag()
{
	if (positionTransforms.size() > 0)
	{
		return positionTransforms.at(positionTransforms.size() - 1).getTag() + 1;
	}
	else
	{
		return 1;
	}
}

FightPos Fight::findPosition(int id)
{
	return fightScene.FindUnitPosition(id);
}

int Fight::dealDamage(int attackDamage, int damagedID, int sourceID, int instanceNr, ActionResults* reactionSpace, TraitTag sourceTrait)
{
	std::vector<Targets> targets;
	targets.push_back(Targets(std::make_pair(findPosition(damagedID), damagedID), {}));
	ActionResults damageResults = ActionResults(ActionTag::Damage, sourceID, findPosition(sourceID), targets);

	DealDamageStage dmgStage;

	Unit* damagedUnit = findFighter(damagedID);

	dmgStage.incomingDamage = attackDamage;
	dmgStage.damageReduction = damagedUnit->getDefense();
	dmgStage.takerPos = findPosition(damagedID);
	dmgStage.takerID = damagedID;
	dmgStage.initiated = true;


	//checkReactions_UnitTakingDamage(attackDamage, damagedSpot, &damageDetails, reactionSpace);
	checkReactions(ReactionTrigger::modifyDamage, &dmgStage, damageResults.getReActionResultsPtr(ReactionTiming::pre));
	checkReactions(ReactionTrigger::preDamage, &dmgStage, damageResults.getReActionResultsPtr(ReactionTiming::pre));

	int reducedDamage = attackDamage - dmgStage.damageReduction;
	if (reducedDamage < 0)
	{
		reducedDamage = 0;
	}

	bool unitWasDead = findFighter(dmgStage.takerPos)->isDead();
	dmgStage.finalDamage = reducedDamage;
	findFighter(dmgStage.takerPos)->dealDamage(reducedDamage);
	damageResults.addSpecifics(reducedDamage);
	reactionSpace->getReActionResultsPtr(ReactionTiming::intra)->addReactionResults(damageResults);

	if (findFighter(dmgStage.takerPos)->getHP() == 0 && !unitWasDead)
	{
		killUnit(damagedID, sourceID, &damageResults);
	}

	checkReactions(ReactionTrigger::postDamage, &dmgStage, damageResults.getReActionResultsPtr(ReactionTiming::post));

	//*signIfDeath = (!unitWasDead && findFighter(dmgStage.takerPos)->isDead());

	return reducedDamage;
}

void Fight::killUnit(int killedID, int killerID, ActionResults* reactionSpace)
{
	std::vector<Targets> targets;
	targets.push_back(Targets(std::make_pair(findPosition(killedID), killedID), {}));
	ActionResults deathResults = ActionResults(ActionTag::Damage, killerID, findPosition(killerID), targets);

	DeathStage deathStage;
	deathStage.dyingUnitID = killedID;
	deathStage.dyingUnitPos = findPosition(killedID);
	deathStage.initiated = true;

	checkReactions(ReactionTrigger::unitDying, &deathStage, reactionSpace->getReActionResultsPtr(ReactionTiming::pre));

	deathStage.dyingUnitPos = findPosition(killedID);

	findFighter(killedID)->kill();
	
	//FightEffect deathEffect = FightEffect(killedUnit->getID(), killedPos, getCurrentInstance(), TraitTag::enumTraitNone);
	//deathEffect.affectedDied = true;

	//deathEffectSpot->push_back(deathEffect);
	//resultsPointer->addEffect(deathEffect);
	checkReactions(ReactionTrigger::unitDied, &deathStage, reactionSpace->getReActionResultsPtr(ReactionTiming::post));
}

void Fight::cleanUpPositioning(ReactionTrigger stageToClean, ReactionResultsList* reactionSpace)
{
	int i;
	ActionResults reactionResult;
	for (i = positionTransforms.size() - 1; i >= 0 ; i--)
	{
		if (positionTransforms.at(i).getCleanupTrigger() == stageToClean)
		{
			bool reacted = positionTransforms.at(i).getCleanupReaction()->cleanupPositionalChanges(this, &reactionResult);
			if (reacted && reactionResult.isInitiated())
			{
				reactionSpace->addReactionResults(reactionResult);
			}
		}
	}
}

void Fight::removePosTransform(int tag)
{
	unsigned int i;
	for (i = 0; i < positionTransforms.size(); i++)
	{
		if (positionTransforms.at(i).getTag() == tag)
		{
			positionTransforms.erase(positionTransforms.begin() + i);
		}
	}
}

void Fight::attackTarget(	FightPos attackingSpot, FightPos defendingSpot, ActionResults* reactionSpace,
							int* attackerWepProf, int* defenderWepProf)
{
	std::vector<Targets> targets;
	targets.push_back(Targets(std::make_pair(defendingSpot, findFighter(defendingSpot)->getID()), {}));
	ActionResults attackResults = ActionResults(ActionTag::Attack, findFighter(attackingSpot)->getID(), attackingSpot, targets);
	Unit* defendingUnit = findFighter(defendingSpot);
	Unit* attackingUnit = findFighter(attackingSpot);

	FightPos redirectedSpot;

	AttackStage stagedAttack;
	stagedAttack.attackerID = findFighter(attackingSpot)->getID();
	stagedAttack.defenderID = findFighter(defendingSpot)->getID();
	stagedAttack.attackerPos = attackingSpot;
	stagedAttack.defenderPos = defendingSpot;
	stagedAttack.initiated = true;

	int defenderID = findFighter(defendingSpot)->getID();
	int instanceNr = takeInstanceNr();

	checkReactions(ReactionTrigger::modifyAttack, &stagedAttack, attackResults.getReActionResultsPtr(ReactionTiming::pre));
	checkReactions(ReactionTrigger::preAttack, &stagedAttack, attackResults.getReActionResultsPtr(ReactionTiming::pre));

	//tag id _efter_ att pre-reaktionerna gjorts utifall någon flyttar runt gubbar
	defenderID = findFighter(defendingSpot)->getID();

	if (stagedAttack.attackBlocked && false)
	{
		stagedAttack.instanceNr = instanceNr;
		/*FightEffect blockedEffect = FightEffect(defenderID, defendingSpot, 0, false, instanceNr, TraitTag::enumTraitNone);
		blockedEffect.physicalBlock = true;
		attackResults.addEffect(blockedEffect);*/
	}
	else
	{
		bool signIfDeath;
		StagedAttackResults saRes;
		*attackerWepProf = stagedAttack.attackerWepProfLevel;
		*defenderWepProf = stagedAttack.defenderWepProfLevel;
		int attackValue = getUnitStats(stagedAttack.attackerPos).attack + stagedAttack.attackValueChange;
		if (stagedAttack.attackerWepProfLevel - stagedAttack.defenderWepProfLevel > 2)
		{
			attackValue = attackValue + 2;
		}
		else if (stagedAttack.attackerWepProfLevel - stagedAttack.defenderWepProfLevel < -2)
		{
			attackValue = attackValue / 2;
		}

		Fight::dealDamage(attackValue, stagedAttack.defenderID, stagedAttack.attackerID, instanceNr, reactionSpace, TraitTag::enumTraitNone);
		stagedAttack.instanceNr = instanceNr;

		saRes.stagedAttack = stagedAttack;

		checkReactions(ReactionTrigger::addEffectToAttack, &saRes, attackResults.getReActionResultsPtr(ReactionTiming::intra));
	}

	reactionSpace->getReActionResultsPtr(ReactionTiming::intra)->addReactionResults(attackResults);

	checkReactions(ReactionTrigger::postAttack, &stagedAttack, attackResults.getReActionResultsPtr(ReactionTiming::post));
}

ActionResults Fight::prepareActionResults(std::vector<Targets> targets)
{
	ActionResults retVal;
	Unit* attackingUnit = findFighter(attacker);

	retVal.setActionTag(offensiveAction->getTag());
	retVal.setActivatorID(attackingUnit->getID());
	retVal.setActivatorPos(attacker);
	if (targets.size() > 0)
	{
		retVal.actionDidResolve();
	}
	retVal.setTargets(targets);

	std::vector<std::vector<bool>> primaryTargetIsDead;
	std::vector<std::vector<bool>> secondaryTargetIsDead;

	return retVal;
}

bool Fight::isPositionTraited(SquadPos posInQ, TraitAffectedUnits traitTrait, SquadPos unitPos, Squad* formation)
{
	switch (traitTrait)
	{
	case TraitAffectedUnits::all:
		return true;
	case TraitAffectedUnits::backColumn:
		return posInQ.getX() == SquadColCoord::back;
	case TraitAffectedUnits::frontColumn:
		return posInQ.getX() == SquadColCoord::front;
	case TraitAffectedUnits::inDanger:
		return formation->getUnitPtr(posInQ)->getHP() < formation->getUnitPtr(posInQ)->getMaxHP()/2;
	case TraitAffectedUnits::sameSpot:
		return posInQ == unitPos;
	default:
		throw new std::exception();
		return false;
	}
}

BoonFightContainer Fight::organizeTraitList(Squad* atkerSquad, Squad* defendingSquad)
{
	BoonFightContainer retVal;
	/*unsigned int i,j,k;
	for (i = 0; i < TACTICAL_X; i++)
	{
		for (j = 0; j < TACTICAL_Y; j++)
		{
			SquadPos mapPos = SquadPos(i, j);
			if (!atkerSquad->getTile(mapPos)->isEmpty())
			{
				Unit* unit = atkerSquad->getUnitPtr(mapPos);
				std::vector<PassiveBoon*> traitList = unit->cloneTraits();
				for (k = 0; k < traitList.size(); k++)
				{
					retVal.addTrait(traitList.at(k), FightPos(mapPos,true));
				}
			}
			if (!defendingSquad->getTile(mapPos)->isEmpty())
			{
				Unit* unit = defendingSquad->getUnitPtr(mapPos);
				std::vector<PassiveBoon*> traitList = unit->cloneTraits();
				for (k = 0; k < traitList.size(); k++)
				{
					retVal.addTrait(traitList.at(k), FightPos(mapPos, false));
				}
			}
		}
	}*/
	return retVal;
}

void Fight::deleteTraitList(std::vector < std::pair < PassiveBoon*, SquadPos > > traitList)
{
	unsigned int i;
	for (i = 0; i < traitList.size(); i++)
	{
		delete traitList.at(i).first;
	}
}

void Fight::checkReactions(ReactionTrigger stageOfFight, ReactionStage* rStage, ReactionResultsList* reactionSpace)
{
	unsigned int i, j;
	std::vector<int> allIDs = getAllUnitIDs();

	for (i = 0; i < allIDs.size(); i++)
	{
		Unit* fighter = findFighter(allIDs.at(i));
		std::vector<ReAction*>* reactions = fighter->getReActionsPtr();
		std::vector<Triggerable*> triggers = fighter->getActionSetupPtr()->getAllTriggerables();

		for (j = 0; j < triggers.size(); j++)
		{
			if (!fighter->isDead() && !isUnitInExile(fighter->getID()))
			{
				ActionResults reactionResult;
				funnelReactionTrigger(stageOfFight, triggers.at(j), allIDs.at(i), rStage, &reactionResult, reactionSpace);
				if (reactionResult.isInitiated())
				{
					reactionSpace->addReactionResults(reactionResult);
				}
			}
		}
	}

	cleanUpPositioning(stageOfFight, reactionSpace);
}

void Fight::funnelReactionTrigger(ReactionTrigger triggerTag, Triggerable* triggerable, int ownerID, ReactionStage* rStage, ActionResults* reactionResults, ReactionResultsList* reactionSpace)
{
	AttackStage* aStage;
	StagedAttackResults* saRes;
	DeathStage* dStage;
	DealDamageStage* dmgStage;
	ModifyFormationBoonStage* formationBoonStage;
	FightPos ownPos = findPosition(ownerID);

	switch (triggerTag)
	{
	case ReactionTrigger::modifyAttack:
		aStage = rStage->produceAttackStage();
		triggerable->modifyUnitBeingAttacked(this, ownPos, ownerID, aStage, reactionResults);

		break;
	case ReactionTrigger::preAttack:
		aStage = rStage->produceAttackStage();
		triggerable->reactToUnitAboutToBeAttacked(this, ownPos, ownerID, aStage, reactionResults);

		break;
	case ReactionTrigger::addEffectToAttack:
		saRes = rStage->produceStagedAttackResults();
		triggerable->addEffectToUnitBeingAttacked(this, ownPos, ownerID, saRes, reactionResults);

		break;
	case ReactionTrigger::postAttack:
		aStage = rStage->produceAttackStage();
		triggerable->reactToUnitHavingBeenAttacked(this, ownPos, ownerID, aStage, reactionResults);
		
		break;
	case ReactionTrigger::postFight:

		break;
	case ReactionTrigger::postBattle:

		break;
	case ReactionTrigger::unitDying:
		dStage = rStage->produceDeathStage();
		triggerable->reactToUnitDying(this, ownPos, ownerID, dStage, reactionResults);

		break;
	case ReactionTrigger::unitDied:
		dStage = rStage->produceDeathStage();
		triggerable->reactToUnitHavingDied(this, ownPos, ownerID, dStage, reactionResults);

		break;
	case ReactionTrigger::modifyDamage:
		dmgStage = rStage->produceDealDamageStage();
		triggerable->modifyUnitTakingDamage(this, ownPos, ownerID, dmgStage, reactionResults);

		break;
	case ReactionTrigger::preDamage:
		dmgStage = rStage->produceDealDamageStage();
		triggerable->reactToUnitAboutToTakeDamage(this, ownPos, ownerID, dmgStage, reactionResults);

		break;
	case ReactionTrigger::postDamage:
		dmgStage = rStage->produceDealDamageStage();
		triggerable->reactToUnitTakingDamage(this, ownPos, ownerID, dmgStage, reactionResults);

		break;
	case ReactionTrigger::modifyFormationBoonTrigger:
		formationBoonStage = rStage->produceModifyFormationBoonStage();
		triggerable->modifyFormationBoonTrigger(this, ownPos, ownerID, formationBoonStage, reactionResults);

		break;
	default:
		throw new std::exception();
	}
}

/***********************************************************************************************************/
/*********************************************** Pos transform **************************************************/
/***********************************************************************************************************/


FightPos PosTransform::transformOldPosition(FightPos pos)
{
	if (pos.isEqual(position1))
	{
		return position2;
	}
	else if (pos.isEqual(position2))
	{
		return position1;
	}
	else
	{
		return pos;
	}
}
