#pragma once
#include "Boon.h"

class HeavyArmor : public Boon
{
private:

public:
	HeavyArmor();

	Boon* clone() const override { return new HeavyArmor(*this); };
	Boon* allocateNew() const override { return new HeavyArmor(); };

	bool modifyUnitBeingAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults) override;
	bool modifyUnitTakingDamage(Fight* activeFight, FightPos ownPow, int ownID, DealDamageStage* dmgStage, ActionResults* reactionResults) override;
};