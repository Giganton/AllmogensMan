#pragma once
#include "StructuredEvent.h"
#include "Trait.h"
#include "Unit.h"

class LevelUpScreenLayer;

class NextLevelupEvent : public StructuredEvent
{
private:
	UnitData leveledUnitData;
	int newLevel = -1;
	std::pair<TraitTag, TraitTag> traitChoice;

public:
	NextLevelupEvent() {};
	//NextLevelupEvent(int level, UnitData unitD, int newLvl, std::pair<Trait*, Trait*> traitchc);
	NextLevelupEvent(int level, UnitData unitD, int newLvl, std::pair<Trait, Trait> traitchc);
	StructuredEvent* clone() const override { return new NextLevelupEvent(*this); };
	StructuredEvent* allocateNew() const override { return new NextLevelupEvent(); };

	void applyToLevelUpScreenLayer(LevelUpScreenLayer* layer) override;

	UnitData getUnitData() { return leveledUnitData; };
	std::pair<TraitTag, TraitTag> getTraits() { return traitChoice; };
	int getNewLevels() { return newLevel; };
};