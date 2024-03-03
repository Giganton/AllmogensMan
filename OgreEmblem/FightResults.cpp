#pragma once
#include "FightResults.h"

ActionResults::ActionResults()
{

}

/*void ActionResults::addDefenderDamage(int unitID, int incomingDamage)
{
	unsigned int i;
	int index = -1;
	for (i = 0; i < dID.size(); i++)
	{
		if (unitID == dID.at(i))
		{
			index = i;
		}
	}
	if (index == -1)
	{
		throw new std::exception();
	}
	else
	{
		dDamage.at(index) = dDamage.at(index) + incomingDamage;
	}
}

void ActionResults::addDefenderDeathStatus(int unitID, bool died)
{
	unsigned int i;
	int index = -1;
	for (i = 0; i < dID.size(); i++)
	{
		if (unitID == dID.at(i))
		{
			index = i;
		}
	}
	if (index == -1)
	{
		throw new std::exception();
	}
	else
	{
		dDied.at(index) = died;
	}
}

void ActionResults::addDefender(int unitID, SquadPos pos)
{
	addDefender(unitID, pos, false);
}

void ActionResults::addDefender(int unitID, SquadPos pos, bool died)
{
	unsigned int i;
	int index = -1;
	for (i = 0; i < dID.size(); i++)
	{
		if (unitID == dID.at(i))
		{
			index = i;
		}
	}
	if (index == -1)
	{
		dID.push_back(unitID);
		defenderPos.push_back(pos);
		dDied.push_back(died);
		dDamage.push_back(0);
	}
	else
	{
	}
}
bool ActionResults::didDDie(int unitID)
{
	unsigned int i;
	int index = -1;
	for (i = 0; i < dID.size(); i++)
	{
		if (unitID == dID.at(i))
		{
			index = i;
		}
	}
	if (index == -1)
	{
		throw new std::exception();
	}
	else
	{
		return dDied.at(index);
	}
}

void ActionResults::addAttacker(int unitID, SquadPos pos, bool died, int incomingDamage)
{
	aID = unitID;
	attackerPos = pos;
	aDied = died;
	aDamage = incomingDamage;
}*/


std::vector<std::pair<int, bool>> ActionResults::getDeathInfo()
{
	std::vector<std::pair<int, bool>> retVal;

	/*std::vector<FightEffect> effects = getEffects();
	unsigned int i;
	for (i = 0; i < effects.size(); i++)
	{
		if (effects.at(i).affectedDied)
		{
			retVal.push_back(std::make_pair(effects.at(i).affectedID, effects.at(i).affectedPos.attackingSide));
		}
	}*/

	return retVal;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*TraitResults::TraitResults()
{

}

std::vector<std::pair<int, bool>> TraitResults::getDeathInfo()
{
	std::vector<std::pair<int, bool>> retVal;

	std::vector<FightEffect> effects = getEffects();
	unsigned int i;
	for (i = 0; i < effects.size(); i++)
	{
		if (effects.at(i).affectedDied)
		{
			retVal.push_back(std::make_pair(effects.at(i).affectedID, effects.at(i).affectedPos.attackingSide));
		}
	}
	for (i = 0; i < responseTraits.size(); i++)
	{
		std::vector<std::pair<int, bool>> temp = responseTraits.at(i).getDeathInfo();
		retVal.insert(retVal.begin(), temp.begin(), temp.end());
	}

	return retVal;
}

FightResults::FightResults(int ownerID, FightPos ownerPos)
{
	//initialized = true;
	activatorID = ownerID;
	activatorPos = ownerPos;
}*/

ReactionResultsList::ReactionResultsList()
{

}

void ReactionResultsList::addReactionResults(ActionResults results)
{
	std::vector<ActionResults> vec;
	vec.push_back(results);
	resultsList.push_back(std::make_pair(-1, vec));
}

void ReactionResultsList::addReactionResults(int index, ActionResults results)
{
	int i;
	for (i = 0; i < resultsList.size(); i++)
	{
		if (resultsList.at(i).first == index)
		{
			resultsList.at(i).second.push_back(results);
			return;
		}
	}
	
	std::vector<ActionResults> vec;
	vec.push_back(results);
	resultsList.push_back(std::make_pair(index, vec));
}

ReactionResultsList* ActionResults::getReActionResultsPtr(ReactionTiming timing) 
{ 
	switch (timing)
	{
	case ReactionTiming::pre:
		return &preReactionSpace;
	case ReactionTiming::intra:
		return &intraReactionResults;
	case ReactionTiming::post:
		return &postReactionResults;
	default:
		throw new std::exception();
		return &preReactionSpace;
	}
}

ActionResults::ActionResults(ActionTag act, int ownerID, FightPos ownerPos, std::vector<Targets> targetList)
{
	action = act;
	targets = targetList;
	activatorID = ownerID;
	activatorPos = ownerPos;
}

/*void FightResults::addFightEffect(int unitID, FightPos unitPos, int incomingDamage, bool died)
{
	FightEffect addedEffect;
	addedEffect.affectedID = unitID;
	addedEffect.affectedPos = unitPos;
	addedEffect.affectedDied = died;
	addedEffect.damageTaken = incomingDamage;

	activationEffects.push_back(addedEffect);
}*/

/*void ActionResults::addFightEffect(int unitID, FightPos unitPos, int incomingDamage, bool died, int instanceNr)
{
	FightEffect addedEffect;
	addedEffect.affectedID = unitID;
	addedEffect.affectedPos = unitPos;
	addedEffect.affectedDied = died;
	addedEffect.damageTaken = incomingDamage;
	addedEffect.instanceNumber = instanceNr;

	activationEffects.push_back(addedEffect);
}

void FightResults::addFightEffect(std::vector<FightEffect> effect)
{
	unsigned int i;
	for (i = 0; i < effect.size(); i++)
	{
		activationEffects.push_back(effect.at(i));
	}
}

void ActionResults::addFightEffect(std::vector<FightEffect> effect)
{
	unsigned int i;
	for (i = 0; i < effect.size(); i++)
	{
		activationEffects.push_back(effect.at(i));
	}
}

void ActionResults::addActivatedTrait(FightEffect sEffect)
{
	activatedTraits.push_back(sEffect.sourceTrait);
	activationEffects.push_back(sEffect);
}

void ActionResults::addEffect(FightEffect effect)
{
	activationEffects.push_back(effect);
	int i;
	bool alreadyAddedInstance = false;
	for (i = 0; i < instances.size(); i++)
	{
		if (instances.at(i) == effect.instanceNumber)
		{
			alreadyAddedInstance = true;
		}
	}
	if (!alreadyAddedInstance)
	{
		instances.push_back(effect.instanceNumber);
	}
}

void ActionResults::addEffect(std::vector<FightEffect> effect)
{
	int i;
	for (i = 0; i < effect.size(); i++)
	{
		addEffect(effect.at(i));
	}
}

void ActionResults::addActivatedTrait(std::vector<FightEffect> sEffects)
{
	unsigned int i;
	for (i = 0; i < sEffects.size(); i++)
	{
		addActivatedTrait(sEffects.at(i));
	}
}*/

int ActionResults::findLowestInstanceNr()
{
	int lowest = 999999;
	unsigned int i;
	for (i = 0; i < instances.size(); i++)
	{
		if (instances.at(i) < lowest)
		{
			lowest = instances.at(i);
		}
	}
	for (i = 0; i < reActionResults.size(); i++)
	{
		int reactionLowest = reActionResults.at(i).findLowestInstanceNr();
		if (reactionLowest < lowest)
		{
			lowest = reactionLowest;
		}
	}
	return lowest;
}

int ActionResults::findHighestInstanceNr()
{
	int highest = -999999;
	unsigned int i;
	for (i = 0; i < instances.size(); i++)
	{
		if (instances.at(i) > highest)
		{
			highest = instances.at(i);
		}
	}
	for (i = 0; i < reActionResults.size(); i++)
	{
		int reactionHighest = reActionResults.at(i).findHighestInstanceNr();
		if (reactionHighest > highest)
		{
			highest = reactionHighest;
		}
	}
	return highest;
}