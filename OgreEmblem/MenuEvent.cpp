#include "MenuEvent.h"
#include "MapAnimationLayer.h"


MenuEvent::MenuEvent(MenuVisualData mData, MenuEventType mType, int lr) : StructuredEvent(lr) 
{
	menuData = mData; 
	eventType = mType; 
}

void MenuEvent::applyToMapAnimationLayer(MapAnimationLayer* layer) 
{ 
	layer->applyMenuEvent(this); 
}