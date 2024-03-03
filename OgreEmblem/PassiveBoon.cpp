#include "PassiveBoon.h"
#include "Squad.h"

/*std::vector<FightEffect> PassiveBoon::addSecondaryEffect(FightPos affectedPos, FightPos primaryTarget, TraitFightProperties traitActivationData, Fight* activeFight)
{ 
	int activatorID = activeFight->findFighter(traitActivationData.unitPos)->getID();

	TraitResults retVal(tag, activatorID, traitActivationData.unitPos);

	std::vector<FightEffect> secondaryResults = performSecondaryEffects(affectedPos,primaryTarget,activeFight);
	
	unsigned int i;
	for (i = 0; i < secondaryResults.size(); i++)
	{
		secondaryResults.at(i).sourceTrait = tag;
	}

	//retVal.addFightEffect(secondaryResults);

	return secondaryResults;
}*/

/*TraitResults PassiveBoon::addOnAttackEffect(FightPos affectedPos, FightPos primaryTarget, TraitFightProperties traitActivationData, Fight* activeFight, int attackNr)
{
	int activatorID = activeFight->findFighter(traitActivationData.unitPos)->getID();

	TraitResults retVal(tag, activatorID, traitActivationData.unitPos);

	std::vector<FightEffect> secondaryResults = performOnAttackEffects(affectedPos, primaryTarget, activeFight, attackNr);
	unsigned int i;
	retVal.addFightEffect(secondaryResults);

	return retVal;
}*/

/*PassiveBoon* getMajorTraitByTag(TraitTag tag)
{
	switch (tag)
	{
	case enumPlusAttack:
		return new PlusAttack();
	case enumPlusDefense:
		return new PlusDefense();
	case enumHugeStrength:
		return new HugeStrength();
	case enumNaturalSelection:
		return new NaturalSelection();
	case enumGains:
		return new Gains();
	default:
		throw new std::exception();
		return new PlusAttack();
	}
}*/