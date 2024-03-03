#include "ConfirmationMenuEvent.h"
#include "MapAnimationLayer.h"

void ConfirmationMenuEvent::applyToMapAnimationLayer(MapAnimationLayer* layer)
{
	layer->applyConfirmationMenuEvent(this);
}