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
class Boon;
class ReAction;
class Action;

class Trait
{
protected:
	TraitTag tag = TraitTag::enumTraitNone;
	std::vector<Boon*> boons;
	std::vector<ReAction*> reactions;
	std::vector<Action*> actions;

public:
	Trait() {};
	Trait(TraitTag tTag);
	Trait(TraitTag tTag, int utilityInt);

	~Trait();
	Trait(const Trait& cP);
	Trait& operator=(const Trait aP);


	virtual void applyToActionSetup(ActionSetup* actionSetup);

	TraitTag getTag() { return tag; };
};

/*class LesserTrait : public Trait
{
public:
	LesserTrait() {};

	virtual LesserTrait* clone() const = 0;
	virtual LesserTrait* allocateNew() const = 0;
};

class MajorTrait : public Trait
{
public:
	MajorTrait() {};

	virtual MajorTrait* clone() const = 0;
	virtual MajorTrait* allocateNew() const = 0;
};

class ProfessionTrait : public Trait
{
protected:
	int baseWP = -1;
public:
	ProfessionTrait() {};

	virtual ProfessionTrait* clone() const = 0;
	virtual ProfessionTrait* allocateNew() const = 0;
};

MajorTrait* getMajorTraitByTag(TraitTag tag);
LesserTrait* getLesserTraitByTag(TraitTag tag);*/