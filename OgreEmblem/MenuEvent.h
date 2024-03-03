#pragma once
#include "MenuVisualData.h"
#include "StructuredEvent.h"

enum class MenuEventType { opened, closed, changedSelected, selected, noEvent, hidden, shown };

class MenuEvent : public StructuredEvent
{
protected:
	MenuVisualData menuData;
	MenuEventType eventType = MenuEventType::noEvent;

public:
	MenuEvent() { };
	MenuEvent(MenuVisualData mData, MenuEventType mType, int lr);

	MenuEvent* allocateNew() const override { return new MenuEvent(); };
	MenuEvent* clone() const override { return new MenuEvent(*this); };

	MenuVisualData getMenuData() { return menuData; };
	MenuEventType getEventType() { return eventType; };

	virtual void applyToMapAnimationLayer(MapAnimationLayer* layer) override;
};