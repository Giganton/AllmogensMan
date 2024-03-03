#pragma once
#include "Boon.h"

class ShieldBearer : public Boon
{
private:

public:
	ShieldBearer();

	Boon* clone() const override { return new ShieldBearer(*this); };
	Boon* allocateNew() const override { return new ShieldBearer(); };

	bool modifyUnitBeingAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults) override;
};