#pragma once
#include "InputLink.h"
#include "OpenBattleMapEvent.h"



class RootLink : public InputLink
{
private:
	void handleKeyPress(sf::Event keyPress) override { throw new std::exception(); };
	ExternalStateControls* externalControls = nullptr;

	void preSubLevelClosing() override;
public:
	RootLink() { level = 0; };
	RootLink(ExternalStateControls* extCtrl);

	InputLink* clone() const override { return new RootLink(*this); };
	InputLink* allocateNew() const override { return new RootLink; };

	void closeAllFollowers() { closeFollowers(); };

	StructuredEvent* getOpeningEvent() override { throw new std::exception(); return new OpenBattleMapEvent(); };
};