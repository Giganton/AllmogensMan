#pragma once
#include <SFML/Graphics.hpp>
#include "GraphicsInterface.h"
#include "MouseSignal.h"
#include "GraphicalEvent.h"
#include "ExternalStateControls.h"

class BattleManager;
class Camp;

class InputLink
{
protected:
	InputLink* nextLevel = nullptr;
	bool middleMan = false;
	bool closeMe = false;
	bool initTrigger = true;
	int ID = -1;

	bool closable = true;

	int level = -1;

	MouseSignal latestSignal;

	StructuredEventQueue eventQueue;

	virtual void handleKeyPress(sf::Event keyPress) {};
	virtual void handleMouseEvent(sf::Event mouseEvent) {};
	void handleInput(sf::Event event);
	virtual void closeFollowers();
	virtual void close() { closeMe = true; };

	virtual void applyMouseSignal(MouseSignal signal) { latestSignal = signal; };

	virtual void setBattleManagerPtr(BattleManager* addr) {};
	virtual void setCampPtr(Camp* addr) {};
	virtual void handleSignal(AnimationSignal signal) {};
	virtual void preSubLevelClosing() {};
	virtual void postSubLevelClosing() {};

	virtual ExternalStateControls generateExternalControls() { return ExternalStateControls(); };

public:
	virtual ~InputLink();
	virtual void receiveInput(sf::Event keyPress);
	bool shouldBeClosed();
	virtual InputLink* clone() const = 0;
	virtual InputLink* allocateNew() const = 0;
	bool triggered() { return initTrigger; };
	bool isLeaf() { return !middleMan; };
	bool isClosable();
	virtual bool isBusy() { return false; };
	void tryClosingSubLevel();
	void closingRound();
	void openLink(InputLink* link);

	virtual StructuredEventQueue pullClosingEvents();// { return GraphicalEventQueue(); };
	virtual StructuredEvent* getOpeningEvent() = 0;

	virtual void passMouseSignals(std::vector<MouseSignal> signals);

	virtual void compileVisualStack(GraphicsInterface* graphInt);
	void updateManagerPointers(Camp* campPtr, BattleManager* bManPtr);
	
	ExternalStateControls collectExternalControls(ExternalStateControls controls);

};