#include "OpenLevelUpScreenEvent.h"
#include "MapAnimationLayer.h"


void OpenLevelUpScreenEvent::applyToMapAnimationLayer(MapAnimationLayer* layer)
{
	layer->openLevelUpScreenLayer();
}