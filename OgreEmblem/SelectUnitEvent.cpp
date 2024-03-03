#include "SelectUnitEvent.h"
#include "DraftScreenLayer.h"

SelectUnitEvent::SelectUnitEvent(int layer, MouseSignal unit) : StructuredEvent(layer)
{
	clickedUnit = unit;
}

SelectUnitEvent::SelectUnitEvent(int layer) : StructuredEvent(layer)
{
	deselect = true;
}


void SelectUnitEvent::applyToDraftScreenLayer(DraftScreenLayer* layer)
{
	if (deselect)
	{
		layer->deselectUnit();
	}
	else
	{
		layer->selectUnit(clickedUnit);
	}
}