#pragma once
#include "Browsable.h"
#include<vector>

class BrowserVisualData
{
private:
	std::vector<std::pair<BrowsableIcon, bool>> listIcons;
	int maxColumns = -1;
	int cursorX = -1;
	int cursorY = -1;
public:
	BrowserVisualData() {};
	BrowserVisualData(std::vector<std::pair<BrowsableIcon, bool>> icons, int maxC, int cursX, int cursY) { listIcons = icons; maxColumns = maxC; cursorX = cursX; cursorY = cursY; };

	std::vector<std::pair<BrowsableIcon, bool>> getIcons() { return listIcons; };
	int getMaxColumns() { return maxColumns; };
	int getCursorPosX() { return cursorX; };
	int getCursorPosY() { return cursorY; };
};