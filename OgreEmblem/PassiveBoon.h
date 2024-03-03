#pragma once
#include "TraitTag.h"
#include "TargetingType.h"
#include "SquadPos.h"
#include "FightResults.h"
#include "TraitFightContainer.h"
#include "FightPos.h"

class Squad;
class Fight;
struct AttackStage;
class ActionSetup;

enum class TraitPhases { none , targeting , attack , attacked , damageReceived , damageDealt , onDeath , onKill};
enum class TraitAffectedUnits { none, all, sameSpot, primaryTargets, inDanger, frontColumn, backColumn };

class PassiveBoon
{
protected:
	TraitTag tag = TraitTag::enumTraitNone;

	TraitAffectedUnits affectedFriendlies = TraitAffectedUnits::none;
	TraitAffectedUnits affectedEnemies = TraitAffectedUnits::none;
public:
	PassiveBoon() {};

	virtual PassiveBoon* clone() const = 0;
	virtual PassiveBoon* allocateNew() const = 0;

	virtual bool applyToDealtAttackDamage(AttackStage* attackChangeSpace) { return false; };
	virtual int applyToDefenseValue(int incomingDamage) { return incomingDamage; };
	virtual int applyToGivenMagicalDamage(int incomingDamage) { return incomingDamage; };
	virtual UnitStatistics applyToStats(UnitStatistics stats) { return stats; };

	//std::vector<FightEffect> addSecondaryEffect(FightPos affectedPos, FightPos primaryTarget, BoonFightProperties traitActivationData, Fight* activeFight);
	//TraitResults addOnAttackEffect(FightPos affectedPos, FightPos primaryTarget, BoonFightProperties traitActivationData, Fight* activeFight, int attackNr);
	virtual bool performSecondaryEffects(FightPos affectedPos, FightPos primaryTarget, Fight* activeFight, std::vector<ActionResults>* reactionSpace) { return false; }
	virtual bool performOnAttackEffects(FightPos attackingUnitPos, FightPos attackTarget, Fight* activeFight, int effectInstanceNr, std::vector<ActionResults>* reactionSpace) { return false; }
	virtual TargetingType changePrimaryTargetingType(TargetingType normalTargetingType) { return normalTargetingType; };

	TraitAffectedUnits getAffectedFriendlies() { return affectedFriendlies; };
	TraitAffectedUnits getAffectedEnemies() { return affectedEnemies; };

	TraitTag getTag() { return tag; };
};

//PassiveBoon* getMajorTraitByTag(TraitTag tag);