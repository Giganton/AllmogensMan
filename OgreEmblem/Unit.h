#pragma once

#include<string>
#include "Browsable.h"
#include "Profession.h"
#include "Action.h"
#include "Fighter.h"
#include "UnitStatistics.h"
#include "Formler.h"
#include "TraitTree.h"
#include "ActionSetup.h"
#include "Career.h"

class BattleStage;
class Trait;

class ActionHandler
{
private:
	Action* action = nullptr;
public:
	ActionHandler(Action* actn) {}
};

struct UnitData
{
	UnitStatistics statistics;
	bool dead = false;

	int ID = -1;
	int level = 1;
	int experiencePoints = 0;

	bool leader = false;
	std::string name;
	//TraitTagTree traitTree;
	Career career;
	//Profession* profession = nullptr;
	ProfessionTag profession = ProfessionTag::enumProfNone;
	ActionTag action;
};

/*class iUnit : public Browsable
{

public:
	virtual int getHP() = 0;
	virtual int getMaxHP() = 0;
	virtual int getAttack() = 0;
	virtual int getDefense() = 0;
	virtual std::string getName() = 0;
	virtual bool isDead() = 0;
	virtual Action* getAction() = 0;
	virtual int getID() = 0;
	virtual void dealDamage(int incomingDamage) = 0;
	virtual UnitStatistics getStatistics() = 0;
	virtual UnitData getData() = 0;
	virtual Fighter produceFighter() = 0;
	virtual Profession* getProfession() = 0;
	virtual std::vector<Trait*> cloneTraits() = 0;
	virtual int getLevel() = 0;
	virtual void addTrait(Trait* trait, int traitSlotID) = 0;
	virtual void addTraitRandomly(Trait* trait) = 0;
	virtual int getLevelUpSlot() = 0;
	virtual std::vector<Trait*> getTraitList() = 0;
};*/

class Unit : public Browsable// : public iUnit
{
protected:
	UnitStatistics statistics;
	Career career;
	//TraitTree traitTree;

	bool dead = false;
	bool exiled = false;
	bool leader = false;

	int ID = -1;
	int level = 1;
	int levelsLeft = -1;
	int experiencePoints = 0;

	std::string name;
	Profession* profession = nullptr;
	//Action* action = nullptr;
	ActionSetup actionSetup;
	//std::vector<ReAction*> reactions;

public:
	Unit() {};
	Unit(std::string nm, int mHP, int atk, int def, Profession* prof, int id);
	Unit(std::string nm, int mHP, int atk, int def, Profession* prof, int id, Career careerInput);

	/*~Unit();
	Unit(const Unit& cp);
	Unit& operator=(const Unit as);*/

	void dealDamage(int incomingDamage);
	int getID() { return ID; };
	int getHP() { return statistics.HP; };
	int getMaxHP() { return statistics.maxHP; };
	int getAttack() { return statistics.attack; };
	int getDefense() { return statistics.defense; };
	std::string getName() { return name; };
	Profession* getProfession() { return profession; };
	std::string getProfName() { return profession->getName(); };
	bool isDead() { return dead; };
	void kill() { dead = true; };
	bool isExiled() { return exiled; };
	bool isLeader() { return leader; };
	int getLevel() { return level; };
	//int getLevelUpSlot();

	void makeLeader() { leader = true; };

	//std::vector<Trait*> cloneTraits() { return traitTree.copyAllTraits(); };
	//void addLesserTrait(LesserTrait* trait);
	void addLesserTrait(Trait trait);
	//void addTrait(Trait* trait, int traitSlotID);
	//void addTraitRandomly(Trait* trait);
	//std::vector<Trait*> getTraitList();
	std::vector<Trait> getTraitList();
	std::vector<Trait*> getTraitPtrList();


	//Action* getAction() { return action; };
	void setupActionsForBattle(BattleStage* bStage);
	Action* getPrimaryAction();
	ActionSetup getActionSetup() { return actionSetup; };
	ActionSetup* getActionSetupPtr() { return &actionSetup; };
	void addAction(Action* actn) { actionSetup.addAction(actn); actn->setOwnerID(ID); };
	std::vector<ReAction*>* getReActionsPtr() { return actionSetup.getReactionsPtr(); };
	void addReAction(ReAction* newReaction) { actionSetup.addReAction(newReaction); newReaction->setOwnerID(ID); };

	UnitStatistics getStatistics();
	UnitData getData();
	//int getMeleeSkill() { return profession->getMeleeSkill(); };

	Fighter produceFighter();
	bool isLevelable() { return !career.isCareerDone(); };
	void levelUp();
	int grantXP(int xp);

	void raiseFromDead();
	
};

/*class Hero : public Unit
{
private:

public:
	Hero() {};
	Hero(std::string nm, int mHP, int atk, int def, Profession* prof, Action* actn, int id) : Unit(nm, mHP, atk, def, prof, actn, id) {};

};*/