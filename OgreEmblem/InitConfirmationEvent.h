#pragma once
#include "StructuredEvent.h"
#include<string>
#include "ConfirmationLayer.h"

class InitConfirmationEvent : public StructuredEvent
{
private:
	std::string descriptionString;
	std::string confirmString;
	std::string denyString;
public:
	InitConfirmationEvent() {};
	InitConfirmationEvent(int layer, std::string descText, std::string confirmText, std::string denyText) : StructuredEvent(layer) { descriptionString = descText; confirmString = confirmText; denyString = denyText; };

	StructuredEvent* clone() const override { return new InitConfirmationEvent(*this); };
	StructuredEvent* allocateNew() const override { return new InitConfirmationEvent(); };

	void applyToConfirmationLayer(ConfirmationLayer* layer) override { layer->initLayer(descriptionString, confirmString, denyString); };
};