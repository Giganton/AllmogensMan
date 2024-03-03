#pragma once
#include "StructuredEvent.h"
#include "LevelUpData.h"
#include "Trait.h"
#include "Unit.h"
class LevelUpScreenLayer;

class InitLevelUpScreenEvent : public StructuredEvent
{
private:
	std::vector<UnitData> leveledUnitsData;
	std::vector<int> newLevels;
	std::pair<TraitTag, TraitTag> firstTraitChoice;
public:
	InitLevelUpScreenEvent() {};
	//InitLevelUpScreenEvent(int level, std::vector<UnitData> lvlData, std::vector<int> newLvls, std::pair<Trait*, Trait*> traitChc);
	InitLevelUpScreenEvent(int level, std::vector<UnitData> lvlData, std::vector<int> newLvls, std::pair<Trait, Trait> traitChc);

	StructuredEvent* clone() const override { return new InitLevelUpScreenEvent(*this); };
	StructuredEvent* allocateNew() const override { return new InitLevelUpScreenEvent(); };

	void applyToLevelUpScreenLayer(LevelUpScreenLayer* layer) override;

	std::vector<UnitData> getUnitData() { return leveledUnitsData; };
	std::pair<TraitTag, TraitTag> getTraits() { return firstTraitChoice; };
	std::vector<int> getNewLevels() { return newLevels; };
};