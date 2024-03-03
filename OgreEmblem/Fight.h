#pragma once
#include "Fighter.h"
#include "FightResults.h"
#include "Action.h"
#include "FighterFormation.h"
#include "SquadPos.h"
#include "TraitFightContainer.h"
#include "PassiveBoon.h"
#include "ReactionStage.h"
#include "FightScene.h"

class Unit;

enum class ReactionTrigger {
								postBattle, 
	
								postFight,

								modifyAttack, 
								preAttack, 
								addEffectToAttack, 
								postAttack, 

								modifyDamage,
								preDamage,
								postDamage,

								unitDying ,
								unitDied ,

								modifyFormationBoonTrigger
 };

struct DealDamageChangeables
{
	int incomingDamage = -1;
	FightPos target;
	Unit* redirectedTarget = nullptr;
	bool damageRedirected;
};

/*struct AttackChangeables
{
	int attackValue = -1;
	bool attackBlocked = false;

};*/


class PosTransform
{
private:
	FightPos position1;
	FightPos position2;
	int tagID = -1;

	ReactionTrigger cleanupTrigger;
	BaseAction* cleanupReaction = nullptr;
public:
	PosTransform() {};
	PosTransform(FightPos pos1, FightPos pos2, int tag, ReactionTrigger cleanupTriggerPhase, BaseAction* cleanupReactionTrigger) { position1 = pos1; position2 = pos2; tagID = tag; cleanupTrigger = cleanupTriggerPhase; cleanupReaction = cleanupReactionTrigger; };

	FightPos transformOldPosition(FightPos pos);

	ReactionTrigger getCleanupTrigger() { return cleanupTrigger; };
	BaseAction* getCleanupReaction() { return cleanupReaction; };
	int getTag() { return tagID; };
};

class Fight
{
private:
	Squad* attackingSquad = nullptr;
	Squad* defendingSquad = nullptr;

	FightScene fightScene;

	bool ready = false;

	std::vector<Unit> exiledZone;
	std::vector<PosTransform> positionTransforms; //den här vektorn innehåller historisk information om hur stridspositionerna flyttats runt. Alla effekter som måste "minnas" en position måste när den ska använda minnet köra det genom denna vektor för att transformera positionen i minnet till nutidens slagfält. Detta görs genom funktionen transformByTag.

	BoonFightContainer traitList;

	FightPos attacker;
	Action* offensiveAction = nullptr;

	std::vector<std::pair<ReactionTrigger , BaseAction*>> positionalCleanupOrders;

	//FightResults results;
	
	int currentInstance = 1;

	/*******************************************************************************************************************************/
	BoonFightContainer organizeTraitList(Squad* atkerSquad, Squad* defendingSquad);
	void deleteTraitList(std::vector < std::pair < PassiveBoon*, SquadPos > > traitlist);

	ActionResults prepareActionResults(std::vector<Targets> targets);
	bool isPositionTraited(SquadPos posInQ, TraitAffectedUnits traitTrait, SquadPos unitPos, Squad* formation);

	void funnelReactionTrigger(ReactionTrigger triggerTag, Triggerable* triggerable, int ownerID, ReactionStage* rStage, ActionResults* reactionResults, ReactionResultsList* reactionSpace);

	void cleanUpPositioning(ReactionTrigger stageToClean, ReactionResultsList* reactionSpace);
public:
	Fight() {};
	Fight(Squad* attSquad, Squad* defSquad);

	void setupNextFight(int atkPosX, int atkPosY);
	ActionResults fight();

	FightScene* getFightScenePtr() { return &fightScene; };

	void checkReactions(ReactionTrigger stageOfFight, ReactionStage* rStage, ReactionResultsList* reactionSpace);

	FightPos getAttackingPos() { return attacker; };
	BoonFightContainer getAllTraits() { return traitList; };
	Unit* getAttackingUnit();
	UnitStatistics getUnitStats(FightPos unitPos);

	Unit* findFighter(FightPos mapPos);
	Unit* findFighter(int id);

	void addToExile(std::vector<Unit> exiled);
	std::vector<Unit> takeFromExile(int id);
	bool isUnitInExile(int id);

	void addPosTransform(int tag, FightPos pos1, FightPos pos2, ReactionTrigger cleanupTrigger, BaseAction* cleanupReaction);
	FightPos transformPosByTag(int tag, FightPos pos);
	int getNewPosTransformTag();

	void removePosTransform(int tag);


	FightPos findPosition(int id);
	std::vector<FightPos> getAllOccupiedNeighbours(FightPos mapPos);

	/***************************************************/
	void killUnit(int killedID, int killerID, ActionResults* reactionSpace);
	int dealDamage(int attackDamage, int damagedID, int sourceID, int instanceNr, ActionResults* reactionSpace, TraitTag sourceTrait);
	void attackTarget(	FightPos attackingSpot, FightPos defendingSpot, ActionResults* reactionSpace,
						int* attackerWepProf, int* defenderWepProf); //return values
	ActionResults performAction(Unit* unit);
	/***************************************************/
	int getCurrentInstance() { return currentInstance; };
	int takeInstanceNr() { currentInstance = currentInstance + 1; return currentInstance - 1; };

	std::vector<int> getAllUnitIDs();

	ReactionResultsList battleIsDone();
};