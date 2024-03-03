#pragma once
#include "MenuManager.h"
#include "InputLink.h"

enum CampMenuActions { leaveCamp, editSquads };

class Camp;

class CampMenuState : public InputLink, public MenuManager
{
private:
	//Flag* managedFlag = nullptr;
	Camp* camp = nullptr;

	Menu createCampMenu();
	void performMenuAction(int action) override;
	void handleKeyPress(sf::Event keypress) override;
	bool* openMapBasket = nullptr;
public:
	CampMenuState() {};
	CampMenuState(int lvl, Camp* cmp, bool* mapBasket);

	CampMenuState* clone() const override { return new CampMenuState(*this); };
	CampMenuState* allocateNew() const override { return new CampMenuState(); };

	void setCampPtr(Camp* addr) override { camp = addr; };

	void openSquadManager();
	StructuredEvent* getOpeningEvent() override;

	void compileVisualStack(GraphicsInterface* graphInt) override;
};