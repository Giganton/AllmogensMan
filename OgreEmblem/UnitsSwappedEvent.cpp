#include "UnitsSwappedEvent.h"
#include "DraftScreenLayer.h"

UnitsSwappedEvent::UnitsSwappedEvent(int layer, Squad sqd) : StructuredEvent(layer)
{
	squad1 = sqd;
	internalSwap = true;
}

UnitsSwappedEvent::UnitsSwappedEvent(int layer, Squad sqd1, Squad sqd2) : StructuredEvent(layer)
{
	squad1 = sqd1;
	internalSwap = true;
	if (sqd1.getID() != sqd2.getID())
	{
		squad2 = sqd2;

		internalSwap = false;
	}
}

void UnitsSwappedEvent::applyToDraftScreenLayer(DraftScreenLayer* layer)
{
	layer->reloadSquad(squad1);
	if (!internalSwap)
	{
		layer->reloadSquad(squad2);
	}
}