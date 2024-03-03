#pragma once
#include "Menu.h"
#include "Squad.h"
#include "Cursor.h"

class ManagerState
{
protected:
	int state = -1;
	Menu menuCopy;
	bool menuIsActive = false;
public:
	void setState(int st) { state = st; };
	void setMenu(Menu mn) { menuCopy = mn; };

	void activateMenu() { menuIsActive = true; };
	void deActivateMenu() { menuIsActive = false; };

	virtual void enterState(int state) = 0;

	int getState() { return state; };
	Menu getMenu() { return menuCopy; };
	bool isMenuActive() { return menuIsActive; };
};

class CursorState
{
protected:
	int cursorPosX = 0;
	int cursorPosY = 0;
public:
	void setCursorPos(int x, int y) { cursorPosX = x; cursorPosY = y; };
	void setCursorPos(CursorPos mapPos) { cursorPosX = mapPos.x; cursorPosY = mapPos.y; }

	int getCursorPosX() { return cursorPosX; };
	int getCursorPosY() { return cursorPosY; };
};