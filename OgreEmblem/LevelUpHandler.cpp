#include "LevelUpHandler.h"
#include "Squad.h"
#include "BattleField.h"
#include "OpenLevelUpScreenEvent.h"
#include "InitLevelUpScreenEvent.h"
#include "LevelUpScreenInputEvent.h"
#include "NextLevelupEvent.h"

LevelUpHandler::LevelUpHandler(int lvl, std::vector<LevelUpData> levelData, BattleField* bField)
{
	level = lvl; //level på objektet, inte på "leveln"
	unsigned int i;
	std::vector<UnitData> unitData;
	for (i = 0; i < levelData.size(); i++)
	{
		squadsWithUnits.push_back(bField->getSquadPtrByID(levelData.at(i).squadID));
		unitsToLevel.push_back(squadsWithUnits.at(i)->findUnitPtr(levelData.at(i).unitID));
		unitData.push_back(unitsToLevel.at(i)->getData());
		newLevels.push_back(levelData.at(i).newLevel);
	}
	prepareUnitForLeveling(unitsToLevel.at(0));
	InitLevelUpScreenEvent evnt = InitLevelUpScreenEvent(level, unitData, newLevels, traitChoice);
	eventQueue.addEvent(&evnt);
}

/*LevelUpHandler::~LevelUpHandler()
{
	delete traitChoice.first;
	delete traitChoice.second;
}
LevelUpHandler::LevelUpHandler(const LevelUpHandler& cp)
{
	level = cp.level;
	squadsWithUnits = cp.squadsWithUnits;
	unitsToLevel = cp.unitsToLevel;
	newLevels = cp.newLevels;
	traitChoice = std::make_pair(cp.traitChoice.first->clone(), cp.traitChoice.second->clone());
	
	traitSlots = cp.traitSlots;
	leftIsPicked = cp.leftIsPicked;
}
LevelUpHandler& LevelUpHandler::operator=(const LevelUpHandler as)
{
	level = as.level;
	squadsWithUnits = as.squadsWithUnits;
	unitsToLevel = as.unitsToLevel;
	newLevels = as.newLevels;
	unsigned int i;
	traitChoice = std::make_pair(as.traitChoice.first->clone(), as.traitChoice.second->clone());
	traitSlots = as.traitSlots;
	leftIsPicked = as.leftIsPicked;

	return *this;
}*/

void LevelUpHandler::prepareUnitForLeveling(Unit* unit)
{
	currentlyLeveledUnit = unit;
	if (!currentlyLeveledUnit->isLevelable())
	{
		throw new std::exception();
	}

	//std::pair<LesserTrait*, LesserTrait*> slotPairs = produceTraitChoice(unit);
	std::pair<Trait, Trait> slotPairs = produceTraitChoice(unit);
	//traitSlots = slotPairs.first;
	traitChoice = slotPairs;
}

//std::pair<LesserTrait*, LesserTrait*> LevelUpHandler::produceTraitChoice(Unit* unit)
std::pair<Trait, Trait> LevelUpHandler::produceTraitChoice(Unit* unit)
{
	std::vector<TraitTag> traitPool = unit->getProfession()->getTraitPool();
	//std::vector<Trait*> traitList = unit->getTraitList();
	std::vector<Trait> traitList = unit->getTraitList();
	unsigned int i, j;
	while (traitList.size() > 0)
	{
		TraitTag unitsTag = traitList.at(0).getTag();
		//delete traitList.at(0);
		traitList.erase(traitList.begin());

		for (i = 0; i < traitPool.size(); i++)
		{
			if (traitPool.at(i) == unitsTag && traitPool.at(i) != TraitTag::enumDummyTrait)
			{
				traitPool.erase(traitPool.begin() + i);
				break;
			}
		}
	}
	int randIndex1 = rand() % traitPool.size();
	TraitTag randTrait1 = traitPool.at(randIndex1);
	if (traitPool.size() > 1)
	{
		traitPool.erase(traitPool.begin() + randIndex1);
	}
	TraitTag randTrait2 = traitPool.at(rand() % traitPool.size());

	//std::pair<LesserTrait*, LesserTrait*> traitChc = std::make_pair(getLesserTraitByTag(randTrait1), getLesserTraitByTag(randTrait2));
	std::pair<Trait, Trait> traitChc = std::make_pair(Trait(randTrait1), Trait(randTrait2));
	return traitChc;
}

void LevelUpHandler::handleKeyPress(sf::Event keyPress)
{
	int menuChoice;
	LevelUpScreenInputEvent evnt;

	if (!(keyPress.type == sf::Event::KeyPressed))
	{
		throw new std::exception();
	}
	switch (keyPress.key.code)
	{
	case sf::Keyboard::Left:
		if (leftIsPicked)
		{

		}
		else
		{
			leftIsPicked = true;
			evnt = LevelUpScreenInputEvent(level, LevelUpScreenEvent::MoveCursorLeft);
			eventQueue.addEvent(&evnt);
		}
		break;
	case sf::Keyboard::Right:
		if (leftIsPicked)
		{
			leftIsPicked = false;
			evnt = LevelUpScreenInputEvent(level, LevelUpScreenEvent::MoveCursorRight);
			eventQueue.addEvent(&evnt);
		}
		else
		{

		}
		break;
	case sf::Keyboard::X:
		handleXPress();
		break;
	}
}

void LevelUpHandler::handleXPress()
{
	if (leftIsPicked)
	{
		currentlyLeveledUnit->addLesserTrait(traitChoice.first);
	}
	else
	{
		currentlyLeveledUnit->addLesserTrait(traitChoice.second);
	}
	currentlyLeveledUnit->levelUp();

	unitsToLevel.erase(unitsToLevel.begin());
	squadsWithUnits.erase(squadsWithUnits.begin());
	newLevels.erase(newLevels.begin());

	LevelUpScreenInputEvent evnt = LevelUpScreenInputEvent(level, LevelUpScreenEvent::AcceptTrait);
	eventQueue.addEvent(&evnt);


	if (unitsToLevel.size() == 0)
	{
		closeMe = true;
	}
	else
	{
		prepareUnitForLeveling(unitsToLevel.at(0));
		NextLevelupEvent evnt2 = NextLevelupEvent(level, currentlyLeveledUnit->getData(), newLevels.at(0), traitChoice);
		eventQueue.addEvent(&evnt2);
	}
}

StructuredEvent* LevelUpHandler::getOpeningEvent()
{
	return new OpenLevelUpScreenEvent(level - 1);
}