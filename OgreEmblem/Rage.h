#pragma once
#include "Action.h"

class Fight;

class Rage : public ReAction
{
private:

public:
	Rage();

	ReAction* clone() const override { return new Rage(*this); };
	ReAction* allocateNew() const override { return new Rage(); };


	bool reactToUnitTakingDamage(Fight* activeFight, FightPos ownPow, int ownID, DealDamageStage* dmgStage, ActionResults* reactionResults) override;
};