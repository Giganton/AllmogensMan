#include "Unit.h"
#include "Action.h"
#include "SquadPos.h"
#include "Trait.h"

Unit::Unit(std::string nm, int mHP, int atk, int def, Profession* prof, int id)
{
	name = nm;
	statistics.maxHP = mHP;
	statistics.HP = mHP;
	statistics.attack = atk;
	statistics.defense = def;
	dead = false;
	//action = actn;
	career = Career(prof);

	profession = prof;
	ID = id;
	//traitTree = TraitTree(TraitTreeType::triangle);
	levelsLeft = 99;// traitTree.getNrOfNodes();
	switch (profession->getTag())
	{
	case ProfessionTag::enumWarrior:
		setBrowserIcon(BrowsableIconTag::unitKnight);
		break;
	case ProfessionTag::enumWizard:
		setBrowserIcon(BrowsableIconTag::unitWizard);
		break;
	case ProfessionTag::enumHero:
		setBrowserIcon(BrowsableIconTag::unitKnight);
		break;
	default:
		throw new std::exception();
	}
}

Unit::Unit(std::string nm, int mHP, int atk, int def, Profession* prof, int id, Career careerInput) : Unit(nm, mHP, atk, def, prof, id)
{
	career = careerInput;
}

/*Unit::~Unit()
{
	unsigned int i;
	for (i = 0; i < reactions.size(); i++)
	{
		delete(reactions.at(i));
	}
}

Unit::Unit(const Unit& cp)
{
	statistics = cp.statistics;
	traitTree = cp.traitTree;

	dead = cp.dead;

	ID = cp.ID;
	level = cp.level;
	levelsLeft = cp.levelsLeft;
	experiencePoints = cp.experiencePoints;
	leader = cp.leader;

	name = cp.name;
	profession = cp.profession;
	actionSetup = cp.actionSetup;

	unsigned int i;
	for (i = 0; i < cp.reactions.size(); i++)
	{
		reactions.push_back(cp.reactions.at(i)->clone());
	}
}

Unit& Unit::operator=(const Unit cp)
{
	statistics = cp.statistics;
	traitTree = cp.traitTree;

	dead = cp.dead;

	ID = cp.ID;
	level = cp.level;
	levelsLeft = cp.levelsLeft;
	experiencePoints = cp.experiencePoints;
	leader = cp.leader;

	name = cp.name;
	profession = cp.profession;
	actionSetup = cp.actionSetup;

	unsigned int i;
	for (i = 0; i < cp.reactions.size(); i++)
	{
		reactions.push_back(cp.reactions.at(i)->clone());
	}

	return *this;
}*/

void Unit::dealDamage(int incomingDamage) 
{
	statistics.HP = (statistics.HP - incomingDamage) > 0 ? statistics.HP - incomingDamage : 0;
	//std::cout << name + " tog " + std::to_string(incomingDamage) + " skada (" + std::to_string(HP) + "/" + std::to_string(maxHP) + ").";
	/*if (statistics.HP == 0)
	{
		//std::cout << " Dog. \n";
		dead = true;
	}
	else
	{
		//std::cout << "\n";
	}*/
}

void Unit::raiseFromDead()
{
	dead = false;
	statistics.HP = 1;
}

/*int Unit::getLevelUpSlot()
{
	return traitTree.getLevelupSlot();
}*/

UnitStatistics Unit::getStatistics()
{
	return statistics;
}

//void Unit::addLesserTrait(LesserTrait* trait)
void Unit::addLesserTrait(Trait trait)
{
	career.addLesserTrait(trait);
}

std::vector<Trait> Unit::getTraitList()
{
	std::vector<Trait> retVal;
	retVal.push_back(profession->getProfTrait());
	std::vector<Trait> temp = career.getAllTraits();
	retVal.insert(retVal.end(), temp.begin(), temp.end());
	return retVal;
}

std::vector<Trait*> Unit::getTraitPtrList()
{
	std::vector<Trait*> retVal;
	retVal.push_back(profession->getProfTraitPtr());
	std::vector<Trait*> temp = career.getAllTraitPtrs();
	retVal.insert(retVal.end(), temp.begin(), temp.end());
	return retVal;
}

/*void Unit::addTrait(Trait* trait, int traitSlotID)
{
	traitTree.addTrait(trait, traitSlotID);
	levelsLeft = levelsLeft - 1;
}

void Unit::addTraitRandomly(Trait* trait)
{
	traitTree.addTrait(trait, traitTree.getLevelupSlot());
	levelsLeft = levelsLeft - 1;
}*/

UnitData Unit::getData()
{
	UnitData retVal;
	retVal.statistics = statistics;
	retVal.dead = dead;
	retVal.ID = ID;
	retVal.name = name;
	retVal.profession = profession->getTag();
	retVal.experiencePoints = experiencePoints;
	retVal.level = level;
	//retVal.traitTree = traitTree.getVisualTree();
	retVal.career = career;
	if (actionSetup.isActionSet())
	{
		retVal.action = getPrimaryAction()->getTag();
	}
	else
	{
		retVal.action = ActionTag::none;
	}
	retVal.leader = leader;

	return retVal;
}

Fighter Unit::produceFighter()
{
	return Fighter(statistics, ID);
}

void Unit::levelUp()
{
	level = level + 1;
}

int Unit::grantXP(int xp)
{
	int retVal = 0; //antal levlingar
	int levelups = 0;
	if (levelsLeft > 0)
	{
		experiencePoints = experiencePoints + xp;
		while (experiencePoints > FORMLER::xpRequirementByLevel(level + 1))
		{
			levelUp();
			levelups = levelups + 1;
			retVal = retVal + 1;
			if (levelsLeft == levelups)
			{
				experiencePoints = FORMLER::xpRequirementByLevel(level);
				break;
			}
		}
	}
	return retVal;
}

Action* Unit::getPrimaryAction()
{
	std::vector<Action*>* actions = actionSetup.getFightActionsPtr();
	if (actions->size() == 0)
	{
		throw new std::exception();
	}

	return actions->at(actions->size() - 1);
}

void Unit::setupActionsForBattle(BattleStage* bStage)
{
	unsigned int i;
	actionSetup.clear();

	//std::vector<Trait*> traits = getTraitList();
	std::vector<Trait*> traits = getTraitPtrList();

	for (i = 0; i < traits.size(); i++)
	{
		traits.at(i)->applyToActionSetup(&actionSetup);
	}
}