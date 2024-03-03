#pragma once
#include "PassiveBoon.h"

class Gains : public PassiveBoon
{
private:
	int plusValue = 1;

public:
	Gains();

	PassiveBoon* clone() const override { return new Gains(*this); };
	PassiveBoon* allocateNew() const override { return new Gains(); };

	//int applyToDealtAttackDamage(int incomingDamage) override;
	UnitStatistics applyToStats(UnitStatistics stats) override;
	//void affectBattle(BattleStage* bStage) override;
};