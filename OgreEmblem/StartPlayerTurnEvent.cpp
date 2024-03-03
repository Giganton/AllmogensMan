#include "StartPlayerTurnEvent.h"
#include "MapAnimationLayer.h"

void StartPlayerTurnEvent::applyToMapAnimationLayer(MapAnimationLayer* layer)
{
	layer->	applyStartPlayerTurnEvent(this);
}