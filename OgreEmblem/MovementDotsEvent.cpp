#include "MovementDotsEvent.h"
#include "MapAnimationLayer.h"

void MovementDotsEvent::applyToMapAnimationLayer(MapAnimationLayer* layer)
{
	layer->applyMovementDotsEvent(this);
}