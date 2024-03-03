#pragma once
#include "PassiveBoon.h"

class PlusAttack : public PassiveBoon
{
private:
	int plusValue = 100;

public:
	PlusAttack();

	PassiveBoon* clone() const override { return new PlusAttack(*this); };
	PassiveBoon* allocateNew() const override { return new PlusAttack(); };

	//int applyToDealtAttackDamage(int incomingDamage) override;
	UnitStatistics applyToStats(UnitStatistics stats) override;
	//void affectBattle(BattleStage* bStage) override;
};