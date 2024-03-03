#pragma once
#include "Boon.h"

class GiantStrength : public Boon
{
private:

public:
	GiantStrength();

	Boon* clone() const override { return new GiantStrength(*this); };
	Boon* allocateNew() const override { return new GiantStrength(); };

	bool addEffectToUnitBeingAttacked(Fight* activeFight, FightPos ownPos, int ownID, StagedAttackResults* saRes, ActionResults* reactionSpace) override;
};