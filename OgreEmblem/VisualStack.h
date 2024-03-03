#pragma once
#include "MapManagerVisualData.h"
#include "ScreenVisualData.h"
#include "MapManagerVisualEventData.h"
#include "CampVisualData.h"

class VisualStack
{
private:
	MapManagerVisualData mapVis;
	bool mapVisible = false;
	MapManagerVisualEventData mapVis2;
	bool newMapInitiation = false;
	BattleMapVisualData mapInitData;

	ScreenVisualData statusVis;
	bool statusScreenVisible = false;

	bool CampVisible = false;
	CampVisualData squadManData;

	StructuredEventQueue campEvents;

	bool empty = true;
public:
	VisualStack() {};
	void setMapVisuals(MapManagerVisualData mv) { mapVis = mv; mapVisible = true; empty = false; };
	void setMapVisuals2(MapManagerVisualEventData mv) { mapVis2 = mv; mapVisible = true; empty = false; };
	void setMapInitData(BattleMapVisualData initData) { mapInitData = initData; newMapInitiation = true; };
	void setCampVisuals(CampVisualData sqData);
	MapManagerVisualData getMapVisuals() { return mapVis; };
	MapManagerVisualEventData getMapVisuals2() { return mapVis2; };
	bool isMapVisible() { return mapVisible; };
	CampVisualData getSquadManagerVisuals() { return squadManData; };
	BattleMapVisualData checkoutMapInitData() { return mapInitData; newMapInitiation = false; };
	bool isNewMapInitialized() { return newMapInitiation; };

	void setStatusScreenVisuals(ScreenVisualData sv) { statusVis = sv; statusScreenVisible = true; empty = false; };
	ScreenVisualData getStatusScreenVisuals() { return statusVis; };
	bool isStatusScreenVisible() { return statusScreenVisible; };
	bool isSquadManagerVisible() { return CampVisible; };
	bool stackIsEmpty() { return empty; };

	void addCampEvents(StructuredEventQueue queue) { campEvents.concatenateQueues(queue); };
	StructuredEventQueue getCampEvents() { return campEvents; };
	void setCampVisibility(bool bl) { CampVisible = bl; };
};