#pragma once
#include "Boon.h"

class Formation : public Boon
{
private:

public:
	Formation();

	Boon* clone() const override { return new Formation(*this); };
	Boon* allocateNew() const override { return new Formation(); };

	bool modifyFormationBoonTrigger(Fight* activeFight, FightPos ownPow, int ownID, ModifyFormationBoonStage* formBoonStage, ActionResults* reactionResults) override;
	bool modifyUnitBeingAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults) override;
};
