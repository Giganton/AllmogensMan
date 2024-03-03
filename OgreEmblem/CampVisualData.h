#pragma once
#include "BrowserEvent.h"
#include "MenuVisualData.h"
#include "CampVisualData.h"
#include "SquadManagerInitVisuals.h"

class CampVisualData
{
private:
	StructuredEventQueue eventQueue;
public:
	CampVisualData() {};

	void addCampEvents(StructuredEventQueue queue) { eventQueue.concatenateQueues(queue); };
	StructuredEventQueue getCampEvents() { return eventQueue; };
};