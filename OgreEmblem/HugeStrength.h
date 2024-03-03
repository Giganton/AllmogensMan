#pragma once
#include "PassiveBoon.h"

class HugeStrength : public PassiveBoon
{
private:

public:
	HugeStrength();

	PassiveBoon* clone() const override { return new HugeStrength(*this); };
	PassiveBoon* allocateNew() const override { return new HugeStrength(); };

	bool performOnAttackEffects(FightPos attackingUnitPos, FightPos attackTarget, Fight* activeFight, int effectInstanceNr, std::vector<ActionResults>* reactionSpace) override;

	//void affectBattle(BattleStage* bStage) override;
};