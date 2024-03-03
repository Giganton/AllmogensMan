#pragma once
#include "Action.h"

class Fight;
class Unit;

class Martyr : public ReAction
{
private:
	FightPos oldSelfPos;
	FightPos oldOtherPos;

	int posTransformTag = -1;

	std::vector<Unit> tempUnitSpace;
	bool activated = false;
	bool cleanedUp = false;
	bool martyrDied = false;
public:
	Martyr();

	ReAction* clone() const override { return new Martyr(*this); };
	ReAction* allocateNew() const override { return new Martyr(); };

	virtual void postFightCleanup() override;

	//ska vara unitbeingattacked
	bool reactToUnitAboutToBeAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults) override;
	bool reactToUnitDying(Fight* activeFight, FightPos ownPos, int ownID, DeathStage* dStage, ActionResults* reactionResults) override;
	//bool reactToNeighbourBeingAttacked(Fight* activeFight, FightPos ownPos, AttackStage* aStage, ActionResults* reactionResults) override;
	//bool reactToAllyHavingBeenAttacked(Fight* activeFight, FightPos attackingPos, FightPos defendingPos, FightPos ownPos, ActionResults* reactionResults) override;

	//bool reactToEndOfFight_Mandatory(Fight* activeFight, FightPos attackingPos, FightPos ownPos, ActionResults* reactionResults) override;

	//bool reactToSelfDying(Fight* activeFight, FightPos ownPos, ActionResults* reactionResults) override;

	bool cleanupPositionalChanges(Fight* activeFight, ActionResults* reactionResults) override;
	//FightResults execute(Unit* attacker, SquadPos atkPos, std::vector<std::pair<std::vector<SquadPos>, std::vector<SquadPos>>> targets, Squad* defenders) override;
};