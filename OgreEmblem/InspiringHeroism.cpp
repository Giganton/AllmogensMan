#include "InspiringHeroism.h"
#include "ReactionStage.h"
#include "Fight.h"
#include "Unit.h"
#include "FightResults.h"

InspiringHeroism::InspiringHeroism()
{
	tag = BoonTag::enumInspiringHeroism;
	traitTag = TraitTag::enumInspiringHeroism;
}

bool InspiringHeroism::reactToUnitDying(Fight* activeFight, FightPos ownPos, int ownID, DeathStage* dStage, ActionResults* reactionResults)
{
	if (dStage->dyingUnitID != ownID && dStage->dyingUnitPos.attackingSide == ownPos.attackingSide)
	{
		*reactionResults = activeFight->performAction(activeFight->findFighter(dStage->dyingUnitID));
	}
	return false;
}