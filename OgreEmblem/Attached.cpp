#include "Attached.h"
#include "ReactionStage.h"
#include "Fight.h"
#include "Unit.h"
#include "FightResults.h"

Attached::Attached()
{
	tag = BoonTag::enumAttached;
	traitTag = TraitTag::enumAttached;
}

bool Attached::reactToUnitHavingDied(Fight* activeFight, FightPos ownPos, int ownID, DeathStage* dStage, ActionResults* reactionResults)
{
	if (dStage->dyingUnitPos.attackingSide == ownPos.attackingSide && dStage->dyingUnitID != ownID)
	{
		deadCounter = deadCounter + 1;

		return true;
	}

	return false;
}

bool Attached::modifyUnitBeingAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults)
{
	if (aStage->attackerID == ownID && deadCounter > 0)
	{
		aStage->attackValueChange = aStage->attackValueChange + deadCounter * 3;

		return true;
	}

	return false;
}
