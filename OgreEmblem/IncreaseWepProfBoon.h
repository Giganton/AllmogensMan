#pragma once
#include "Boon.h"

class IncreaseWepProfBoon : public Boon
{
private:
	int WPincrease = -1;
public:
	IncreaseWepProfBoon() {};
	IncreaseWepProfBoon(BoonTag tag, int WPinc);

	Boon* clone() const override { return new IncreaseWepProfBoon(*this); };
	Boon* allocateNew() const override { return new IncreaseWepProfBoon(); };

	bool reactToUnitAboutToBeAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults) override;
};