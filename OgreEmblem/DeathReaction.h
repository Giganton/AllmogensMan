#pragma once
#include "Action.h"

class Fight;

class DeathReaction : public ReAction
{
private:
public:
	DeathReaction();

	ReAction* clone() const override { return new DeathReaction(*this); };
	ReAction* allocateNew() const override { return new DeathReaction(); };


	bool reactToUnitTakingDamage(Fight* activeFight, FightPos ownPow, int ownID, DealDamageStage* dmgStage, ActionResults* reactionResults) override;

};