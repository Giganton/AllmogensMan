#pragma once
#include "GraphicalEvent.h"
#include "MenuVisualData.h"
#include "MenuAnimation.h"

class MenuVisualEvent : public GraphicalEvent
{
private:
	MenuVisualData visData;

public:
	MenuVisualEvent() {};
	MenuVisualEvent(MenuVisualData data) { visData = data; };

	MenuVisualEvent* allocateNew() const override { return new MenuVisualEvent(); };
	MenuVisualEvent* clone() const override { return new MenuVisualEvent(*this); };

	//void actUponBrowserAnim(BrowserAnimation* anim) override { throw new std::exception(); };
	//void actUponSquadManagerAnim(SquadManagerAnimation* anim) override { throw new std::exception(); };
	void actUponMenuAnim(MenuAnimation* anim) { anim->setMenuData(visData); anim->activate(); };


};