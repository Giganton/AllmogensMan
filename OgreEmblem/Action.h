#pragma once
#include<string>
#include "Fighter.h"
#include "FighterFormation.h"
#include<vector>
#include "SquadPos.h"
#include "ActionTag.h"
#include "TargetingType.h"
#include "TraitFightContainer.h"
#include "FightPos.h"
#include "Triggerable.h"

class Squad;
class iUnit;
class ActionResults;
class PassiveBoon;
class Fight;
//class FightEffect;
struct DealDamageChangeables;
struct AttackChangeables;
struct AttackStage;
struct DeathStage;
struct DealDamageStage;
class FightScene;

class Targets
{
private:
	std::pair<FightPos , int> primary; //inten representerar unitID för uniten som står på positionen, bra att ha i animationen eftersom det en sprite inte alltid kommer att stå på precis sin position, tex som följd av Martyr. Det är dock inte alltid det står en unit på en position som väljs som mål och då ska det stå -1 i inten.
	std::vector<std::pair<FightPos, int>> secondary;

public:
	Targets() {};
	Targets(std::pair<FightPos, int> prim, std::vector<std::pair<FightPos, int>> sec) { primary = prim; secondary = sec; };

	std::pair<FightPos, int> getPrimaryTarget() { return primary; };
	std::vector<std::pair<FightPos, int>> getSecondaryTargets() { return secondary; };
};

class BaseAction
{
protected:
	std::string name = "";
	ActionTag tag = ActionTag::none;
	TargetingType targetingType = TargetingType::none;

	int ownerID = -1;

	FightPos findFirstOccupiedSpot(std::vector < SquadPos > targetPriority, FightScene* formation, bool attackingSide);
	std::vector<SquadPos> findAllOccupiedSpots(std::vector < SquadPos > targets, Squad* formation);
	FightPos findLeastHPSpot(FightScene* formation, bool atkSide);
	std::vector<FightPos> pickRandomOccupiedByLivingSpot(FightScene* formation, bool attackingSide);

	std::vector<SquadPos> meleeTargetPriority(SquadPos atkPos);
	std::vector<SquadPos> magicalTargetPriority(SquadPos atkPos);

public:

	std::string getName() { return name; };
	ActionTag getTag() { return tag; };

	virtual bool cleanupPositionalChanges(Fight* activeFight, ActionResults* reactionResults) { return false; };

	int getOwnerID() { return ownerID; };
	void setOwnerID(int newID) { ownerID = newID; };
};

class Action : public BaseAction
{
protected:

	//int dealDamage(int incomingDamage, Unit* unit);
	//int attackTarget(SquadPos attackingSpot, Squad* attackingSquad, SquadPos defendingSpot, Squad* defendingSquad, BoonFightContainer traits);

	virtual ActionResults performAction(int usedID, std::vector<Targets> targets, Fight* activeFight, ActionResults resultsFrame) = 0;

public:
	virtual Action* clone() const = 0;
	virtual Action* allocateNew() const = 0;
	//void execute(Unit* user, int posX, int posY, Squad* homeSqd, Squad* awaySqd, FightResults* results);
	ActionResults execute(FightPos executorPose, Fight* activeFight);
	//SquadPos findTargetPos(int posX, int posY, Squad* awaySqd);
	virtual std::vector<FightPos> getSecondaryTargets(FightPos defenderPos, Fight* activeFight) { return std::vector<FightPos>(); };
	std::vector<FightPos> findPrimaryTargetPos(FightPos attackerPos, Fight* activeFight, TargetingType targetingMethod);
	std::vector<Targets> findTargets(FightPos attackerPos, Fight* activeFight);
	ActionResults prepareActionResults(FightPos pos, Fight* fight, std::vector<Targets> targets);
};

class ReAction : public BaseAction, public Triggerable
{
protected:
	int nrOfUses = 0;

	//ActionResults performAction(std::vector<Targets> targets, Fight* activeFight, ActionResults resultsFrame) override;

public:
	std::vector<PositionalRelation> unitBeingAttacked_posRelTriggers = { PositionalRelation::invalid };
	std::vector<PositionalRelation> unitHavingBeenAttacked_posRelTriggers = { PositionalRelation::invalid };
	std::vector<PositionalRelation> unitDying_posRelTriggers = { PositionalRelation::invalid };
	std::vector<PositionalRelation> unitTakingDamage_posRelTriggers = { PositionalRelation::invalid };

	virtual ReAction* clone() const = 0;
	virtual ReAction* allocateNew() const = 0;

	virtual void postFightCleanup() {};

	bool modifyUnitBeingAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults) override { return false; };
	virtual bool reactToEndOfFight_Mandatory(Fight* activeFight, FightPos attackingPos, FightPos ownPos, ActionResults* reactionResults);
};

Action* createAction(ActionTag tag);
ReAction* createReAction(ActionTag tag);