#pragma once
#include "PassiveBoon.h"

class PlusDefense : public PassiveBoon
{
private:
	int plusValue = 100;

public:
	PlusDefense();

	PassiveBoon* clone() const override { return new PlusDefense(*this); };
	PassiveBoon* allocateNew() const override { return new PlusDefense(); };

	int applyToDefenseValue(int incomingDamage) override;
	//void affectBattle(BattleStage* bStage) override;
};