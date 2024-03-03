#pragma once
#include<vector>
#include "Menu.h"
#include "Unit.h"
#include "Cursor.h"
#include "Squad.h"

class ScreenVisualData
{
private:
	std::vector<UnitInSquadData> unitList = {};

	Menu activeMenu;
	bool menuIsActive = false;

	Unit* hoveredUnit;
	CursorPos cursorPos;

public:
	ScreenVisualData() {};

	std::vector<UnitInSquadData> getUnitList() { return unitList; };
	Unit* getHoveredUnit() { return hoveredUnit; };
	CursorPos getCursorPos() { return cursorPos; };

	void addUnit(Unit unit, SquadPos mapPos) { unitList.push_back(UnitInSquadData(unit.getData(), mapPos)); };
	void addUnit(UnitInSquadData unitData) { unitList.push_back(unitData); };
	void setUnitList(std::vector<UnitInSquadData> unData) { unitList = unData; };
	void setHovered(Unit* unit) { hoveredUnit = unit; };
	void setCursorPos(CursorPos cursPos) { cursorPos = cursPos; };
	void setActiveMenu(Menu mn) { activeMenu = mn; menuIsActive = true; };
	bool isMenuActive() { return menuIsActive; };
	Menu getActiveMenu();
};