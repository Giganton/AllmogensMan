#include "Triggerable.h"
#include "Fight.h"
#include "ReactionStage.h"
#include "Unit.h"
//#include "FightResults.h"

bool Triggerable::reactToUnitAboutToBeAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults)
{
	return false;
}

bool Triggerable::modifyUnitBeingAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults)
{
	return false;
}

bool Triggerable::addEffectToUnitBeingAttacked(Fight* activeFight, FightPos ownPos, int ownID, StagedAttackResults* saRes, ActionResults* reactionSpace)
{
	return false;
}

bool Triggerable::reactToUnitHavingBeenAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults)
{
	return false;
}

bool Triggerable::reactToUnitDying(Fight* activeFight, FightPos ownPos, int ownID, DeathStage* dStage, ActionResults* reactionResults)
{
	return false;
}

bool Triggerable::reactToUnitHavingDied(Fight* activeFight, FightPos ownPos, int ownID, DeathStage* dStage, ActionResults* reactionResults)
{
	return false;
}

bool Triggerable::reactToEndOfBattle(Fight* activeFight, FightPos ownPos, int ownID, ActionResults* reactionResults)
{
	return false;
}

bool Triggerable::reactToUnitAboutToTakeDamage(Fight* activeFight, FightPos ownPow, int ownID, DealDamageStage* dmgStage, ActionResults* reactionResults)
{
	return false;
}

bool Triggerable::reactToUnitTakingDamage(Fight* activeFight, FightPos ownPow, int ownID, DealDamageStage* dmgStage, ActionResults* reactionResults)
{
	return false;
}
bool Triggerable::modifyUnitTakingDamage(Fight* activeFight, FightPos ownPow, int ownID, DealDamageStage* dmgStage, ActionResults* reactionResults)
{
	return false;
}

bool Triggerable::modifyFormationBoonTrigger(Fight* activeFight, FightPos ownPow, int ownID, ModifyFormationBoonStage* formBoonStage, ActionResults* reactionResults)
{
	return false;
}