#include "InitLevelUpScreenEvent.h"
#include "LevelUpScreenLayer.h"
#include "SquadPos.h"


InitLevelUpScreenEvent::InitLevelUpScreenEvent(int level, std::vector<UnitData> uData, std::vector<int> newLvls, std::pair<Trait, Trait> traitChc) : StructuredEvent(level)
{ 
	leveledUnitsData = uData; 
	newLevels = newLvls;
	firstTraitChoice = std::make_pair(traitChc.first.getTag(), traitChc.second.getTag());
}

void InitLevelUpScreenEvent::applyToLevelUpScreenLayer(LevelUpScreenLayer* layer)
{
	layer->applyInitLevelUpScreenEvent(this);
}