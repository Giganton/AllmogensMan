#pragma once
#include<vector>
#include "CursorHandler.h"
#include <SFML/Graphics.hpp> //needed for keypress
#include "Browsable.h"
#include "BrowserVisualData.h"
#include "BrowserEvent.h"

class Browser
{
private:
	std::vector<BrowsingData> items;

	BrowsingData itemInHand;
	bool isHoldingItem = false;
	std::vector<int> selected;
	int rowMax = -1;
	int colMax = -1;
	int itemsToPick = -1;

	ListCursorHandler cursorHandler;
	bool active = false;
	bool done = false;
	bool doneAtFilled = true;

	//GraphicalEventQueue eventQueue;
	std::vector<BrowserEvent*> eventQueue;


	//metoder
	void select();
	void toggleHovered();
	int findCursorIndex();
	int findCursorIndex(CursorPos mapPos);
public:
	Browser() {};
	Browser(std::vector<BrowsingData> browsables, int nrOfItems, int rMax, int cMax, CursorEdgeType edgeT);
	~Browser();
	Browser(const Browser& cpEQ);
	Browser& operator=(const Browser asEQ);

	void handleKeyPress(sf::Event keyPress);
	std::vector<BrowsingData> getSelected();
	std::vector<int> getSelectedIndices() { return selected; };
	bool allAnimationsFinished() { return done; };
	BrowsingData getHovered();
	bool isHoveredSelected();
	void clearSelection() { selected.clear(); done = false; };
	std::vector<BrowsingData> getItems() { return items; };
	BrowsingData getItem(CursorPos mapPos);

	void pickUpItem();
	void dropItem();
	void swapItem();

	BrowsingData takeFromHand();
	void giveToHand(BrowsingData data);
	bool cursorHoldingItem() { return isHoldingItem; };

	void activate();
	void deactivate();
	bool isActive() { return active; };

	BrowserVisualData getBrowserVisualData();
	void addSelectionEvent(int selectionIndex);
	std::vector<BrowserEvent*> pullEventQueue(); //FARLIG FUNKTION


	Direction getCursorPassingDir() { return cursorHandler.getPassingDir(); };
	bool isCursorPassingEdge() { return cursorHandler.isPassingEdge(); };
	void allowCursor();
	void stopCursor() { cursorHandler.stopPassing(); };
	CursorPos getCursorPos() { return cursorHandler.getCursorPos(); };
	void setBorderType(CursorEdgeType edgeT) { cursorHandler.setEdgeType(edgeT); };
};