#include "MovementTargetCrossEvent.h"
#include "MapAnimationLayer.h"

MovementTargetCrossEvent::MovementTargetCrossEvent(int level, MapCoord crd) : StructuredEvent(level)
{
	putDown = true;
	coord = crd;
}

MovementTargetCrossEvent::MovementTargetCrossEvent(MapCoord crd)
{
	putDown = true;
	coord = crd;
}

MovementTargetCrossEvent::MovementTargetCrossEvent(int level) : StructuredEvent(level)
{
	putDown = false;
}

MovementTargetCrossEvent::MovementTargetCrossEvent()
{
	putDown = false;
}

void MovementTargetCrossEvent::applyToMapAnimationLayer(MapAnimationLayer* layer)
{
	layer->applyMovementTargetCrossEvent(this);
}