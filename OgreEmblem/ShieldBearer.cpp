#include "ShieldBearer.h"
#include "ReactionStage.h"
#include "Fight.h"
#include "Unit.h"
#include "FightResults.h"


ShieldBearer::ShieldBearer()
{
	tag = BoonTag::enumShieldBearer;
	traitTag = TraitTag::enumShieldBearer;
}
bool ShieldBearer::modifyUnitBeingAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults)
{
	if (aStage->defenderID == ownID)
	{
		aStage->defenderWepProfLevel = aStage->defenderWepProfLevel + 2;

		return true;
	}

	return false;
}