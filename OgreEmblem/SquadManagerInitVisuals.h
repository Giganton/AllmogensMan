#pragma once
#include "BrowserVisualData.h"
#include "MenuVisualData.h"

class SquadManagerInitVisuals
{
private:
	BrowserVisualData bData;
	MenuVisualData mData;
public:
	SquadManagerInitVisuals() {};
	SquadManagerInitVisuals(BrowserVisualData bd, MenuVisualData md) { bData = bd; mData = md; };

	BrowserVisualData getBrowserVisuals() { return bData; };
	void setBrowserVisuals(BrowserVisualData bd) { bData = bd; };
	MenuVisualData getMenuVisuals() { return mData; };
	void setMenuVisuals(MenuVisualData md) { mData = md; };
};