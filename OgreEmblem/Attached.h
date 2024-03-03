#pragma once
#include "Boon.h"

class Attached : public Boon
{
private:
	int deadCounter = 0;
public:
	Attached();

	Boon* clone() const override { return new Attached(*this); };
	Boon* allocateNew() const override { return new Attached(); };

	bool reactToUnitHavingDied(Fight* activeFight, FightPos ownPos, int ownID, DeathStage* dStage, ActionResults* reactionResults) override;
	bool modifyUnitBeingAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults) override;
};
