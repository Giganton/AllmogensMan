#pragma once
#include "Graphics.h"
#include "StructuredEvent.h"
#include "MenuVisualEvent.h"

class CampLayer;
class CampMenuLayer;
class BaseLayer;

class CampEvent : public StructuredEvent
{
protected:

public:
	CampEvent() {};
	CampEvent(int lr) : StructuredEvent(lr) { };

	//virtual void actUponCampLayer(CampLayer* layer) { throw new std::exception(); };
	//void actUponAnimationLayer(AnimationLayer* layer) override;

	//void findBaseLayer(Graphics* graphics) override { graphics->applyCampEvent(this); };
};

class CampMenuEvent : public CampEvent
{
private:
	MenuVisualEvent menuEvent;

public:
	CampMenuEvent() {};
	CampMenuEvent(int level, MenuVisualEvent mData) : CampEvent(level) { menuEvent = mData; };

	//void actUponMenuAnim(MenuAnimation* anim) override { menuEvent.actUponMenuAnim(anim); };
	//void actUponCampMenuLayer(CampMenuLayer* layer) override;

	StructuredEvent* clone() const override { return new CampMenuEvent(*this); };
	StructuredEvent* allocateNew() const override { return new CampMenuEvent(); };

	//void actUponCampLayer(CampLayer* layer) override;

	void applyToCampMenuLayer(CampMenuLayer* layer) override;

	//void actUponCampMenuLayer(CampMenuLayer* layer);
};

class OpenSquadManagerEvent : public CampEvent
{
private:

public:
	OpenSquadManagerEvent() {};
	OpenSquadManagerEvent(int level) : CampEvent(level) {};

	StructuredEvent* clone() const override { return new OpenSquadManagerEvent(*this); };
	StructuredEvent* allocateNew() const override { return new OpenSquadManagerEvent(); };

	//void actUponCampLayer(CampLayer* layer) override;

	void applyToCampMenuLayer(CampMenuLayer* layer) override;

	//void actUponCampMenuLayer(CampMenuLayer* layer);
};

class OpenCampMenuEvent : public CampEvent
{
private:

public:
	OpenCampMenuEvent() {};
	OpenCampMenuEvent(int level) : CampEvent(level) {};

	StructuredEvent* clone() const override { return new OpenCampMenuEvent(*this); };
	StructuredEvent* allocateNew() const override { return new OpenCampMenuEvent(); };

	void applyToBaseLayer(BaseLayer* layer) override;
};