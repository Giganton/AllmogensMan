#pragma once
#include "FightPos.h"
#include "FightResults.h"


struct AttackStage;
struct DealDamageStage;
struct DeathStage;
struct produceModifyFormationBoonStage;

std::vector<PositionalRelation> drawPosRelFromAttack_defender(AttackStage* aStage);
std::vector<PositionalRelation> drawPosRelFromAttack_attacker(AttackStage* aStage);

struct ReactionStage
{
	bool containsPosRelation = false;
	bool initiated = false;

	virtual void clean() = 0;
	virtual ReactionStage* clone() = 0;

	virtual AttackStage* produceAttackStage() { throw new std::exception(); };
	virtual DealDamageStage* produceDealDamageStage() { throw new std::exception(); };
	virtual DeathStage* produceDeathStage() { throw new std::exception(); };
	virtual StagedAttackResults* produceStagedAttackResults() { throw new std::exception(); };
	virtual ModifyFormationBoonStage* produceModifyFormationBoonStage() { throw new std::exception(); };
};

struct AttackStage : public ReactionStage
{
	int instanceNr = -1;
	int attackerID = -1;
	int defenderID = -1;

	FightPos defenderPos;
	FightPos attackerPos;

	bool attackBlocked = false;

	int attackValueChange = 0;
	int defenseValueChange = 0;
	int attackerWepProfLevel = 0;
	int defenderWepProfLevel = 0;

	AttackStage();
	void clean() override;
	ReactionStage* clone() { return new AttackStage(*this); };

	AttackStage* produceAttackStage() override { return this; };
};

struct StagedAttackResults : public ReactionStage
{
	AttackStage stagedAttack;

	//FightEffect stagedEffect;
	//std::vector<FightEffect> additionalEffects;

	StagedAttackResults();
	void clean() override;
	ReactionStage* clone() { return new StagedAttackResults(*this); };

	StagedAttackResults* produceStagedAttackResults() override { return this; };
};

struct DeathStage : public ReactionStage
{
	int dyingUnitID = -1;
	FightPos dyingUnitPos;

	DeathStage();
	void clean() override;
	ReactionStage* clone() { return new DeathStage(*this); };

	DeathStage* produceDeathStage() override { return this; };
};

struct DealDamageStage : public ReactionStage
{
	int dealerID = -1;
	int takerID = -1;
	FightPos takerPos;

	int incomingDamage = -1;
	int damageReduction = -1;
	int finalDamage = -1;

	DealDamageStage();

	void clean() override;
	ReactionStage* clone() { return new DealDamageStage(*this); };

	DealDamageStage* produceDealDamageStage() override { return this; };
};


struct ModifyFormationBoonStage : public ReactionStage
{
	int FormationActivatorID = -1;
	FightPos activatorPos;

	int triggers = 0;

	ModifyFormationBoonStage() {};

	void clean() override;
	ReactionStage* clone() { return new ModifyFormationBoonStage(*this); };

	ModifyFormationBoonStage* produceModifyFormationBoonStage() override { return this; };
};
