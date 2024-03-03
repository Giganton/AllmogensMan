#pragma once
#include "SquadPos.h"
#include "FightPos.h"

class Squad;
class PassiveBoon;

class BoonFightProperties
{
public:
	PassiveBoon* trait= nullptr;
	FightPos unitPos;

	BoonFightProperties() {};
	BoonFightProperties(PassiveBoon* trt, FightPos mapPos);
	bool doesItAffectThisPos(FightPos mapPos, Squad* attackers, Squad* defenders);

	~BoonFightProperties() { delete trait; };
	BoonFightProperties(const BoonFightProperties& cp);
	BoonFightProperties& operator=(const BoonFightProperties as);
};

class BoonFightContainer
{
private:
	std::vector<BoonFightProperties> traitList;
public:
	BoonFightContainer() {};

	void addTrait(BoonFightProperties trait);
	void addTrait(PassiveBoon* trait, FightPos mapPos);
	unsigned int getSize() { return traitList.size(); };
	std::vector<BoonFightProperties> getTraits() { return traitList; };
	BoonFightProperties getTraitProp(int i) { return traitList.at(i); };
	BoonFightContainer traitsThatAffectThisPos(FightPos mapPos, Squad* attackers, Squad* defenders);
};