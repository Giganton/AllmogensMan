#pragma once
#include<string>
#include "ProfessionID.h"
#include "TraitList.h"
#include "Trait.h"

class ProfessionTrait;

class Profession
{
private:
	ProfessionTag tag = ProfessionTag::enumProfNone;
	std::string battleTextureFile;
	std::string mapTextureFile;
	std::string name;

	int baseWP = -1;

	//ProfessionTrait* profTrait = nullptr;
	Trait profTrait;

	std::vector<TraitTag> traitPool;

	void initWarrior();
	void initWizard();
	void initHero();
	void setProfTrait();
	void setBaseWP();
	void setBaseWP(int WP);
public:
	Profession(ProfessionTag pId);
	Profession(ProfessionTag pId, int WP);
	/*~Profession();
	Profession(const Profession& cpEQ);
	Profession& operator=(const Profession asEQ);*/

	std::string getName() { return name; };
	std::string getBattleTextureFile() { return battleTextureFile; };
	std::string getMapTextureFile() { return mapTextureFile; };
	ProfessionTag getTag() { return tag; };
	std::vector<TraitTag> getTraitPool() { return traitPool; };
	//int getMeleeSkill() { return meleeSkill; };
	//Trait* getProfTrait();
	Trait getProfTrait();
	Trait* getProfTraitPtr();
};