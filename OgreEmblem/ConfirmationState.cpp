#include "ConfirmationState.h"
#include "OpenConfirmationEvent.h"
#include "ConfirmationMouseButtons.h"
#include "InitConfirmationEvent.h"

ConfirmationState::ConfirmationState(int lvl, std::string descText, std::string confText, std::string denText, bool* answBucket)
{
	level = lvl;
	descriptionText = descText;
	confirmText = confText;
	denyText = denText;

	InitConfirmationEvent evnt = InitConfirmationEvent(level, descriptionText, confirmText, denyText);
	eventQueue.addEvent(&evnt);

	answerBucket = answBucket;
}

StructuredEvent* ConfirmationState::getOpeningEvent()
{
	return new OpenConfirmationEvent(level - 1);
}

void ConfirmationState::handleKeyPress(sf::Event inputEvent)
{

}

void ConfirmationState::handleMouseEvent(sf::Event mouseEvent)
{
	if (mouseEvent.type == sf::Event::MouseButtonPressed)
	{
		if (mouseEvent.mouseButton.button == sf::Mouse::Left)
		{
			handleMouseClickLeft(mouseEvent);
		}
	}
}

void ConfirmationState::handleMouseClickLeft(sf::Event mouseEvent)
{
	if (latestSignal.getHoveredId() == ConfirmationMouseButtons::none)
	{

	}
	else if (latestSignal.getHoveredId() == ConfirmationMouseButtons::confirmed)
	{
		*answerBucket = true;
		close();
	}
	else if (latestSignal.getHoveredId() == ConfirmationMouseButtons::denied)
	{
		*answerBucket = false;
		close();
	}
	else
	{
		throw new std::exception();
	}

}

