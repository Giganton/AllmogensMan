#pragma once
#include "InputLink.h"
#include "TraitList.h"

class Squad;
class iUnit;
class BattleField;

class LevelUpHandler : public InputLink
{
private:
	std::vector<Squad*> squadsWithUnits;
	std::vector<Unit*> unitsToLevel;
	std::vector<int> newLevels;

	Unit* currentlyLeveledUnit = nullptr;
	//std::pair<LesserTrait*, LesserTrait*> traitChoice;
	std::pair<Trait, Trait> traitChoice;
	int traitSlots;
	bool leftIsPicked = true;

	void handleKeyPress(sf::Event keyPress) override;
	void handleXPress();
	//std::pair<LesserTrait*, LesserTrait*> produceTraitChoice(Unit* unit);
	std::pair<Trait, Trait> produceTraitChoice(Unit* unit);
	void prepareUnitForLeveling(Unit* unit);
public:
	LevelUpHandler() {};
	LevelUpHandler(int lvl, std::vector<LevelUpData> levelData, BattleField* bField);
	//~LevelUpHandler();
	//LevelUpHandler(const LevelUpHandler& cp);
	//LevelUpHandler& operator=(const LevelUpHandler as);
	InputLink* clone() const override { return new LevelUpHandler(*this); };
	InputLink* allocateNew() const override { return new LevelUpHandler(); };

	StructuredEvent* getOpeningEvent() override;
};