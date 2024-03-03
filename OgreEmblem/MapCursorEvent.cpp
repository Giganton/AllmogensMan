#include "MapCursorEvent.h"
#include "MapAnimationLayer.h"

void MapCursorEvent::applyToMapAnimationLayer(MapAnimationLayer* layer)
{
	layer->applyMapCursorEvent(this);
}