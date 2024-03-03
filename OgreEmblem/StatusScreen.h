#pragma once
#include<vector>
#include "Squad.h"
#include "Cursor.h"
#include "Menu.h"
#include <SFML/Graphics.hpp> //needed for keypress
#include "ManagerState.h"
#include "Manager.h"
#include "CursorHandler.h"
#include "ScreenVisualData.h"
#include "OpenBattleMapEvent.h"

enum StatusScreenStates { initial, swapping };

enum StatusScreenMenuActions { initializeSwap, performSwap, closeStatusMenu };

class StatusState : public ManagerState , public CursorState
{
private:
	CursorPos posToSwap;
	Squad* shownSquad = nullptr;

public:
	StatusState() {};
	StatusState(int st);
	StatusState(int st, int x, int y) : StatusState(st) { cursorPosX = x; cursorPosY = y; };

	void enterState(int st) override;
	void setSwappingPos(CursorPos mapPos) { posToSwap = mapPos; };
	CursorPos getSwappingPos() { return posToSwap; };

	void setSquad(Squad* sqd) { shownSquad = sqd; };
	Squad* getSquad() { return shownSquad; };
};



class StatusScreen : public Manager
{
private:
	
	StatusState currentState;
	std::vector<StatusState> prevStates = { };
	
	Squad* shownSquad = nullptr;
	
	GridCursorHandler curHandler;
	CursorPos posToSwap;

	//methods
	//StatusState* getInternalState() override { return &currentState; };
	void activateMenu() override { currentState.activateMenu(); };
	void deactivateMenu() override { currentState.deActivateMenu(); };
	void enterState(int state) override { currentState.enterState(state); };
	int getState() override { return currentState.getState(); };
	void returnToPrevState() override;
	void saveState() override;
	void deleteHistory() override;
	void loadFromState() override;
	void captureState() override;

	void performMenuAction(int action) override;

	Menu createSwapMenu();
	Menu createStatusMenu();

	void controlStatusScreen(sf::Event keyPress);
public:
	StatusScreen() {};
	StatusScreen(int id) : Manager(id) { currentState.setState(StatusScreenStates::initial); };
	StatusScreen(int id, Squad* sqd);
	StatusScreen(int id, StatusScreenStates state) : Manager(id) { currentState = state; loadFromState(); };

	bool isMenuActive() override { return currentState.isMenuActive(); };

	StatusScreen* clone() const override { return new StatusScreen(*this); };
	StatusScreen* allocateNew() const override { return new StatusScreen(ID); };
	StatusScreen(const StatusScreen& cpSS);
	StatusScreen& operator=(const StatusScreen asSS);
	~StatusScreen() override { InputLink::~InputLink(); };

	void handleKeyPress(sf::Event keyPress) override;

	Squad getSquad() { return *shownSquad; };
	ScreenVisualData getVisuals();

	void initSwap();
	void performSwap();

	Unit* getHoveredUnit();

	void compileVisualStack(GraphicsInterface* stack) override;
	StructuredEvent* getOpeningEvent() { throw new std::exception(); return new OpenBattleMapEvent(level - 1); };
};