#include "BattleEvent.h"
#include "MapAnimationLayer.h"

void BattleEvent::applyToMapAnimationLayer(MapAnimationLayer* layer)
{
	layer->applyBattleEvent(this);
}