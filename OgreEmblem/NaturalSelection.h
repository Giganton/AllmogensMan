#pragma once
#include "PassiveBoon.h"


class NaturalSelection : public PassiveBoon
{
private:

public:
	NaturalSelection();

	PassiveBoon* clone() const override { return new NaturalSelection(*this); };
	PassiveBoon* allocateNew() const override { return new NaturalSelection(); };

	TargetingType changePrimaryTargetingType(TargetingType normalTargetingType) override;

	//void affectBattle(BattleStage* bStage) override;
};