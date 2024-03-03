#include "LevelUpScreenInputEvent.h"
#include "LevelUpScreenLayer.h"
#include "SquadPos.h"

void LevelUpScreenInputEvent::applyToLevelUpScreenLayer(LevelUpScreenLayer* layer)
{
	layer->applyLevelUpScreenInputEvent(this);
}