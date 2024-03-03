#include "GiantStrength.h"
#include "ReactionStage.h"
#include "Fight.h"
#include "Unit.h"
#include "FightResults.h"

GiantStrength::GiantStrength()
{
	tag = BoonTag::enumGiantStrength;
	traitTag = TraitTag::enumGiantStrength;
}

bool GiantStrength::addEffectToUnitBeingAttacked(Fight* activeFight, FightPos ownPos, int ownID, StagedAttackResults* saRes, ActionResults* reactionSpace)
{
	if (saRes->stagedAttack.attackerID == ownID)
	{
		if (saRes->stagedAttack.defenderPos.squadPos.getX() == SquadColCoord::front)
		{
			FightPos behindPos = saRes->stagedAttack.defenderPos.getPosBehind();
			if (activeFight->getFightScenePtr()->isPosOccupied(behindPos))
			{
				int attackStrength = activeFight->getUnitStats(ownPos).attack;//int attackStrength = saRes->stagedEffect.damageTaken;// 
				Unit* damagedUnit = activeFight->findFighter(behindPos);
				bool died = false;
				activeFight->dealDamage(attackStrength, activeFight->findFighter(behindPos)->getID(), ownID, activeFight->getCurrentInstance(), reactionSpace, TraitTag::enumTraitNone);

				return true;
			}
		}
	}
	return false;
}