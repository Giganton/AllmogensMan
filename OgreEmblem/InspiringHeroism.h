#pragma once
#include "Boon.h"

class InspiringHeroism : public Boon
{
private:

public:
	InspiringHeroism();

	Boon* clone() const override { return new InspiringHeroism(*this); };
	Boon* allocateNew() const override { return new InspiringHeroism(); };

	bool reactToUnitDying(Fight* activeFight, FightPos ownPos, int ownID, DeathStage* dStage, ActionResults* reactionResults) override;
};
