#pragma once
#include "Menu.h"
#include <SFML/Graphics.hpp>

class MenuManager
{
protected:
	Menu menu;
	bool active = false;

	virtual void controlMenu(sf::Event keyPress);
	virtual void openMenu(Menu mn) { active = true; menu = mn; menu.activate(); menu.setSelected(0); atMenuOpening(); };
	virtual void atMenuOpening() {};
	virtual void atMenuClosing() {};
	virtual void selectionAction() {};
	virtual void closeMenu() { active = false; menu.deActivate(); atMenuClosing(); };
	bool isMenuActive() { return active; };
	virtual void performMenuAction(int action) = 0;
public:
	MenuManager() {};
};
