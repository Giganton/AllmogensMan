#include "SetAttackTargetEvent.h"
#include "MapAnimationLayer.h"

void SetAttackTargetEvent::applyToMapAnimationLayer(MapAnimationLayer* layer)
{
	layer->applySetAttackTargetEvent(this);
}