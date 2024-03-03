#include "UnitKilledEvent.h"
#include "MapAnimationLayer.h"

void UnitKilledEvent::applyToMapAnimationLayer(MapAnimationLayer* layer)
{ 
	layer->applyUnitKilledEvent(this); 
};