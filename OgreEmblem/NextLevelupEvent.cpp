#include "NextLevelupEvent.h"
#include "LevelUpScreenLayer.h"
#include "SquadPos.h"

NextLevelupEvent::NextLevelupEvent(int level, UnitData unitD, int newLvl, std::pair<Trait, Trait> traitchc) : StructuredEvent(level)
{
	leveledUnitData = unitD;
	newLevel = newLvl;
	traitChoice = std::make_pair(traitchc.first.getTag(), traitchc.second.getTag());
}

void NextLevelupEvent::applyToLevelUpScreenLayer(LevelUpScreenLayer* layer)
{
	layer->applyNextLevelupEvent(this);
}