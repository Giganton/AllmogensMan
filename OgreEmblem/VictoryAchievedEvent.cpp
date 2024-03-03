#include "VictoryAchievedEvent.h"
#include "MapAnimationLayer.h"

void VictoryAchievedEvent::applyToMapAnimationLayer(MapAnimationLayer* layer)
{
	layer->applyVictoryAchievedEvent(this);
}