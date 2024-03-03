#include "Formation.h"
#include "ReactionStage.h"
#include "Fight.h"
#include "Unit.h"
#include "FightResults.h"

Formation::Formation()
{
	tag = BoonTag::enumFormation;
	traitTag = TraitTag::enumFormation;
}

bool Formation::modifyFormationBoonTrigger(Fight* activeFight, FightPos ownPos, int ownID, ModifyFormationBoonStage* formBoonStage, ActionResults* reactionResults)
{
	if (formBoonStage->activatorPos.isNeighbourTo(ownPos))
	{
		formBoonStage->triggers = formBoonStage->triggers + 1;
		return true;
	}
	return false;
}

bool Formation::modifyUnitBeingAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults)
{
	if (aStage->attackerPos.isEqual(ownPos) || aStage->defenderPos.isEqual(ownPos))
	{
		ModifyFormationBoonStage stage;
		stage.activatorPos = ownPos;
		stage.FormationActivatorID = ownID;
		stage.initiated = true;
		stage.triggers = 0;

		activeFight->checkReactions(ReactionTrigger::modifyFormationBoonTrigger, &stage, reactionResults->getReActionResultsPtr(ReactionTiming::pre));
		aStage->attackerWepProfLevel = aStage->attackerWepProfLevel + stage.triggers*2;

		return true;
	}
	return false;

}