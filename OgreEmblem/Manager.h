#pragma once
#include "ManagerState.h"
#include "Menu.h"
#include <SFML/Graphics.hpp> //needed for keypress
#include "InputLink.h"

enum ManagerExternalActions { baseNothing };

class Manager : public InputLink
{
private:
	Manager(const Manager& cpMan) {};
protected:

	Menu activeMenu;

	//methods
	//virtual ManagerState* getInternalState() = 0;
	virtual void activateMenu() = 0;
	virtual void deactivateMenu() = 0;
	virtual void enterState(int state) = 0;
	virtual void returnToPrevState() = 0;
	virtual void captureState() = 0;
	virtual void saveState() = 0;
	virtual void deleteHistory() = 0;
	virtual void loadFromState() = 0;

	virtual void performMenuAction(int action) = 0;
	void controlMenu(sf::Event keyPress);
	//virtual void handleInput(sf::Event keyPress) = 0;

	//void closeSubManagers();
	Manager() {};
	Manager(int id) { ID = id; };

public:

	//void receiveInput(sf::Event keyPress);

	void goToState(int state, bool saveHistory, bool deleteHistory);
	virtual int getState() = 0;

	Menu getActiveMenu();
	void closeMenu();
	void openMenu(Menu menu);
	virtual bool isMenuActive() = 0;

	//bool shouldBeClosed() { return closeMe; };

};