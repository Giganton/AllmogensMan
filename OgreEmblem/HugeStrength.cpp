#include "HugeStrength.h"
#include "BattleStage.h"
#include "Fight.h"
#include "FightUtils.h"


HugeStrength::HugeStrength()
{
	tag = TraitTag::enumHugeStrength;
	affectedFriendlies = TraitAffectedUnits::sameSpot;
}

bool HugeStrength::performOnAttackEffects(FightPos attackingUnitPos, FightPos attackTarget, Fight* activeFight, int effectInstanceNr, std::vector<ActionResults>* reactionSpace)
{
	if (attackTarget.squadPos.getX() == SquadColCoord::front)
	{
		FightPos behindPos = FightPos(SquadPos(SquadColCoord::back, attackTarget.squadPos.getY()),attackTarget.attackingSide);
		if (activeFight->getFightScenePtr()->isPosOccupied(behindPos))
		{
			Unit* struckUnit = activeFight->findFighter(behindPos);
			Unit* attackingUnit = activeFight->findFighter(attackingUnitPos);
			bool struckUnitWasDead = struckUnit->isDead();
			int attackStrength = activeFight->getUnitStats(attackingUnitPos).attack;
			//FightEffect temp = FightEffect(struckUnit->getID(), behindPos, effectInstanceNr, tag);
			int incomingDamage = 0;//activeFight->dealDamage(attackStrength, behindPos, &temp.affectedDied, reactionSpace);
			//temp.damageTaken = incomingDamage;
			//effectSpace->push_back(temp);

			return true;
		}
	}
	return false;
}