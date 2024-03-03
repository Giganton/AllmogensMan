#pragma once
#include "InputLink.h"

class ConfirmationState : public InputLink
{
private:
	std::string descriptionText;
	std::string confirmText;
	std::string denyText;

	bool* answerBucket = nullptr;

	void handleKeyPress(sf::Event inputEvent) override;
	void handleMouseEvent(sf::Event mouseEvent) override;
	void handleMouseClickLeft(sf::Event mouseEvent);
public:
	ConfirmationState() {};
	ConfirmationState(int level, std::string descText, std::string confText, std::string denText, bool* answBucket);

	ConfirmationState* clone() const override { return new ConfirmationState(*this); };
	ConfirmationState* allocateNew() const override { return new ConfirmationState(); };

	StructuredEvent* getOpeningEvent() override;
};