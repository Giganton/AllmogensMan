#include "SquadManagerLayer.h"
#include "SquadManagerEvent.h"

/*void SquadManagerLayer::trackSquadManagerEvent(SquadManagerEvent* evnt)
{
	if (evnt->getDepth() > layer)
	{
		if (middleMan)
		{
			nextLevel->trackSquadManagerEvent(evnt);
		}
		else if (evnt->getDepth() == layer + 1)
		{
			evnt->openNewAnimationLayer(this);
			nextLevel->trackSquadManagerEvent(evnt);
		}
		else
		{
			throw new std::exception();
		}
	}
	else if (evnt->getDepth() == layer)
	{
		//applySquadManagerEvent(evnt);
		evnt->actUponSquadManagerLayer(this);
	}
	else
	{
		throw new std::exception();
	}
}

void SquadManagerLayer::applySquadManagerEvent(SquadManagerEvent* evnt)
{
	evnt->actUponSquadManagerLayer(this);
}*/