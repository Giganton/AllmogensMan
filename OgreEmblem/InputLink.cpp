#include "InputLink.h"
#include "SquadManagerEvent.h"

InputLink::~InputLink()
{
	if (middleMan)
	{
		delete nextLevel;
		middleMan = false;
	}
}

void InputLink::receiveInput(sf::Event keyPress)
{
	if (middleMan)
	{
		if (keyPress.key.code == sf::Keyboard::Z && nextLevel->isLeaf() && nextLevel->isClosable())
		{
			closeFollowers();
		}
		else
		{
			nextLevel->receiveInput(keyPress);
			if (nextLevel->shouldBeClosed())
			{
				closeFollowers();
			}
			else
			{
				initTrigger = nextLevel->triggered();
			}
		}
	}
	else
	{
		handleInput(keyPress);
	}
	tryClosingSubLevel();
}

void InputLink::handleInput(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		handleKeyPress(event);
	}
	else if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
	{
		handleMouseEvent(event);
	}
}

bool InputLink::isClosable() 
{
	return closable; 
}

bool InputLink::shouldBeClosed()
{ 
	return (closeMe && !isBusy()); 
}

void InputLink::closeFollowers()
{
	if (middleMan)
	{
		preSubLevelClosing();
		eventQueue.concatenateQueues(nextLevel->pullClosingEvents());
		CloseSubLayerEvent temp = CloseSubLayerEvent(level);
		eventQueue.addEvent(&temp);

		nextLevel->closeFollowers();
		delete nextLevel;
		nextLevel = nullptr;

		middleMan = false;
		postSubLevelClosing();
	}
	else
	{
		return;
	}
}

void InputLink::tryClosingSubLevel()
{
	if (middleMan && nextLevel->shouldBeClosed())
	{
		nextLevel->closeFollowers();
		closeFollowers();
		/*delete nextLevel;
		nextLevel = nullptr;
		middleMan = false;
		CloseSubLayerEvent temp = CloseSubLayerEvent(level);
		eventQueue.addEvent(&temp);*/
	}
}

void InputLink::passMouseSignals(std::vector<MouseSignal> signals)
{
	unsigned int i;
	for (i = 0; i < signals.size(); i++)
	{
		if (signals.at(i).getTargetLevel() == level)
		{
			applyMouseSignal(signals.at(i));
			signals.erase(signals.begin() + i);
			i = i - 1;
		}
	}
	if (signals.size() > 0)
	{
		if (middleMan)
		{
			nextLevel->passMouseSignals(signals);
		}
		else
		{
			signals.clear();
		}
	}
}

void InputLink::closingRound()
{
	tryClosingSubLevel();
	if (middleMan)
	{
		nextLevel->closingRound();
	}
}

StructuredEventQueue InputLink::pullClosingEvents()
{
	StructuredEventQueue retVal = StructuredEventQueue();
	if (middleMan)
	{
		retVal.concatenateQueues(nextLevel->pullClosingEvents());
		retVal.concatenateQueues(eventQueue);
		CloseSubLayerEvent temp = CloseSubLayerEvent(level);
		retVal.addEvent(&temp);
	}
	else
	{
		retVal.concatenateQueues(eventQueue);
	}
	return retVal;
}

void InputLink::updateManagerPointers(Camp* campPtr, BattleManager* bManPtr)
{
	setCampPtr(campPtr);
	setBattleManagerPtr(bManPtr);

	if (middleMan)
	{
		nextLevel->updateManagerPointers(campPtr, bManPtr);
	}
}

ExternalStateControls InputLink::collectExternalControls(ExternalStateControls controls)
{
	ExternalStateControls retVal;
	if (middleMan)
	{
		retVal = nextLevel->collectExternalControls(controls);
	}
	return compoundControls(retVal, generateExternalControls());
}

void InputLink::openLink(InputLink* link)
{
	closeFollowers(); 
	nextLevel = link; 
	middleMan = true;
	StructuredEvent* opening = nextLevel->getOpeningEvent();
	eventQueue.addEvent(opening);
	delete opening;
}

void InputLink::compileVisualStack(GraphicsInterface* graphInt)
{
	graphInt->addEvents(eventQueue);
	eventQueue.emptyQueue();
	if (middleMan)
	{
		nextLevel->compileVisualStack(graphInt);
	}

	std::vector<AnimationSignal> signalsToMe = graphInt->getSignals(level);
	while (!signalsToMe.empty())
	{
		handleSignal(signalsToMe.at(0));
		signalsToMe.erase(signalsToMe.begin());
	}
}