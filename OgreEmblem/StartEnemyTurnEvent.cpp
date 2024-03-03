#include "StartEnemyTurnEvent.h"
#include "MapAnimationLayer.h"

void StartEnemyTurnEvent::applyToMapAnimationLayer(MapAnimationLayer* layer)
{
	layer->applyStartEnemyTurnEvent(this);
}