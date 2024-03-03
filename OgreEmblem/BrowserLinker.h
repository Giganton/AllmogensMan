#pragma once
#include "Browser.h"
#include "Direction.h"

enum class BrowserSpot { none, center, left, top, bottom, right };

class PassEvent
{
public:
	PassEvent() {};
	PassEvent(BrowserSpot st, BrowserSpot dst) { start = st; dest = dst; };

	BrowserSpot start = BrowserSpot::none;
	BrowserSpot dest = BrowserSpot::none;
};

class BrowserLinker
{
private:
	Browser* center = nullptr;
	Browser* left = nullptr;
	Browser* upper = nullptr;
	Browser* right = nullptr;
	Browser* down = nullptr;

	Browser* active = nullptr;
	BrowserSpot activeSpot = BrowserSpot::none;

	std::vector<PassEvent> passings;

	BrowserSpot findNeighbour(Direction dir);
	Browser* getBrowser(BrowserSpot spot);
	void passCursor();
public: 
	BrowserLinker() {};

	void addBrowser(Browser* brows, BrowserSpot spot);

	void deactivateCluster() { active->deactivate(); };
	void activateCluster() { active->activate(); };

	void activateSpot(BrowserSpot spot);
	std::vector<PassEvent> pullPassings();

	void handleKeyPress(sf::Event keypress);

	Browser* getActiveBrowser() { return active; };
};