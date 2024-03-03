#pragma once
#include "FightPos.h"
#include "TraitTag.h"
class ActionResults;
class AttackStage;
class DeathStage;
class DealDamageStage;
class Fight;
class StagedAttackResults;
class ModifyFormationBoonStage;
class ReactionResultsList;

class Triggerable
{
protected:

public:
	TraitTag traitTag = TraitTag::enumTraitNone;
	Triggerable() {};

	virtual bool reactToUnitAboutToBeAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults);
	virtual bool modifyUnitBeingAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults);
	//virtual bool addEffectToUnitBeingAttacked(Fight* activeFight, FightPos ownPos, int ownID, StagedAttackResults* saRes, ReactionResultsList* reactionSpace);
	virtual bool addEffectToUnitBeingAttacked(Fight* activeFight, FightPos ownPos, int ownID, StagedAttackResults* saRes, ActionResults* reactionSpace);
	virtual bool reactToUnitHavingBeenAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults);
	virtual bool reactToUnitDying(Fight* activeFight, FightPos ownPos, int ownID, DeathStage* dStage, ActionResults* reactionResults);
	virtual bool reactToUnitHavingDied(Fight* activeFight, FightPos ownPos, int ownID, DeathStage* dStage, ActionResults* reactionResults);
	virtual bool reactToEndOfBattle(Fight* activeFight, FightPos ownPos, int ownID, ActionResults* reactionResults);
	virtual bool reactToUnitAboutToTakeDamage(Fight* activeFight, FightPos ownPow, int ownID, DealDamageStage* dmgStage, ActionResults* reactionResults);
	virtual bool reactToUnitTakingDamage(Fight* activeFight, FightPos ownPow, int ownID, DealDamageStage* dmgStage, ActionResults* reactionResults);
	virtual bool modifyUnitTakingDamage(Fight* activeFight, FightPos ownPow, int ownID, DealDamageStage* dmgStage, ActionResults* reactionResults);
	virtual bool modifyFormationBoonTrigger(Fight* activeFight, FightPos ownPow, int ownID, ModifyFormationBoonStage* formBoonStage, ActionResults* reactionResults);
};