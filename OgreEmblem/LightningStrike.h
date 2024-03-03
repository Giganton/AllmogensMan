#pragma once
#include "Action.h"
#include "FightResults.h"

class LightningStrike : public Action
{
private:
	int primaryDamage = 10;

	ActionResults performAction(int userID, std::vector<Targets> targets, Fight* activeFight, ActionResults resultsFrame) override;
public:
	LightningStrike();
	Action* clone() const override { return new LightningStrike(*this); };
	Action* allocateNew() const override { return new LightningStrike(); };
};