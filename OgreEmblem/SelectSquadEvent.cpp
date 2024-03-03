#include "SelectSquadEvent.h"
#include "DraftScreenLayer.h"

SelectSquadEvent::SelectSquadEvent(int layer, MouseSignal squad, bool isForWindowOne) : StructuredEvent(layer)
{
	clickedSquadSignal = squad;
	signalEvent = true;
	windowOne = isForWindowOne;

	signalEvent = true;
}

SelectSquadEvent::SelectSquadEvent(int layer, Squad squad, bool isForWindowOne) : StructuredEvent(layer)
{
	clickedSquad = squad;
	signalEvent = true;
	windowOne = isForWindowOne;

	signalEvent = false;
}

SelectSquadEvent::SelectSquadEvent(int layer, bool isForWindowOne) : StructuredEvent(layer)
{
	deselect = true;
	windowOne = isForWindowOne;
}

SelectSquadEvent::SelectSquadEvent(int layer) : StructuredEvent(layer)
{
	windowOne = true;
	emptySquad = true;
}


void SelectSquadEvent::applyToDraftScreenLayer(DraftScreenLayer* layer)
{
	if (deselect)
	{
		layer->deselectSquad(windowOne);
	}
	else
	{
		if (emptySquad)
		{
			layer->selectNewEmptySquad(windowOne);
		}
		else
		{
			if (signalEvent)
			{
				layer->selectSquad(clickedSquadSignal, windowOne);
			}
			else
			{
				layer->selectSquad(clickedSquad, windowOne);
			}
		}
	}
}