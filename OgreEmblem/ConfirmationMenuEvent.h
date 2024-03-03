#pragma once
#include "MenuEvent.h"

class ConfirmationMenuEvent : public MenuEvent
{
private:
	std::string menuText;
public:
	ConfirmationMenuEvent() {};
	ConfirmationMenuEvent(MenuVisualData mData, MenuEventType mType, std::string mText, int lr) : MenuEvent(mData, mType, lr) { menuText = mText; };
	ConfirmationMenuEvent(MenuVisualData mData, MenuEventType mType, int lr) : MenuEvent(mData, mType, lr) { };

	MenuEvent* allocateNew() const override { return new ConfirmationMenuEvent(); };
	MenuEvent* clone() const override { return new ConfirmationMenuEvent(*this); };

	void applyToMapAnimationLayer(MapAnimationLayer* layer) override;
	std::string getMenuText() { return menuText; };
};