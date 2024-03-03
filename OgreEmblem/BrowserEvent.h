#pragma once
#include "GraphicalEvent.h"
#include "Cursor.h"
#include "BrowserVisualData.h"

class BrowserAnimation;
class SquadManagerAnimation;

class BrowserEvent : public GraphicalEvent
{
public:
	BrowserEvent() {};

	//virtual void actOut(BrowserAnimation* anim) = 0;
	virtual BrowserEvent* cloneAsBrowser() const = 0;
	virtual void actUponBrowserAnim(BrowserAnimation* anim) = 0;
	//void actUponSquadManagerAnim(SquadManagerAnimation* anim) override { throw new std::exception(); };
	//void actUponMenuAnim(MenuAnimation* anim) override { throw new std::exception(); };
};

class BrowserCursorMove : public BrowserEvent
{
public:
	CursorPos start;
	CursorPos destination;

	BrowserCursorMove() {};
	BrowserCursorMove(CursorPos st, CursorPos dt) { start = st; destination = dt; };

	void actUponBrowserAnim(BrowserAnimation* anim) override;
	BrowserCursorMove* allocateNew() const override { return new BrowserCursorMove(); };
	BrowserCursorMove* clone() const override { return new BrowserCursorMove(*this); };
	BrowserEvent* cloneAsBrowser() const override { return new BrowserCursorMove(*this); };
};

class SelectionMade : public BrowserEvent
{
private:
	std::vector<int> toggledSelections = {};
public:
	SelectionMade() {};
	SelectionMade(std::vector<int> toggles) { toggledSelections = toggles; };

	SelectionMade* allocateNew() const override { return new SelectionMade(); };
	SelectionMade* clone() const override { return new SelectionMade(*this); };
	BrowserEvent* cloneAsBrowser() const override { return new SelectionMade(*this); };
	void actUponBrowserAnim(BrowserAnimation* anim) override;

	void addToggled(int nw) { toggledSelections.push_back(nw); };
	std::vector<int> getToggled() { return toggledSelections; };
};
/*
class ItemRemoved : public BrowserEvent
{
public:
	ItemRemoved() {};
	void actOut(BrowserAnimation* anim) override;
	ItemRemoved* allocateNew() const override { return new ItemRemoved(); };

};*/

class BrowserOpened : public BrowserEvent
{
private:
	BrowserVisualData initData;
public:
	BrowserOpened() {};
	BrowserOpened(BrowserVisualData data) { initData = data; };

	BrowserOpened* allocateNew() const override { return new BrowserOpened(); };
	BrowserOpened* clone() const override { return new BrowserOpened(*this); };
	BrowserEvent* cloneAsBrowser() const override { return new BrowserOpened(*this); };
	void actUponBrowserAnim(BrowserAnimation* anim) override;

};

class BrowserActiveness : public BrowserEvent
{
private:
	bool activated = false;
public:
	BrowserActiveness() {};
	BrowserActiveness(bool act) { activated = act; };

	BrowserActiveness* allocateNew() const override { return new BrowserActiveness(); };
	BrowserActiveness* clone() const override { return new BrowserActiveness(*this); };
	BrowserEvent* cloneAsBrowser() const override { return new BrowserActiveness(*this); };

	void actUponBrowserAnim(BrowserAnimation* anim) override;

};

class BrowserPickup : public BrowserEvent
{
private:
	CursorPos pickupPos;
public:
	BrowserPickup() {};
	BrowserPickup(CursorPos mapPos) { pickupPos = mapPos; };

	BrowserPickup* allocateNew() const override { return new BrowserPickup(); };
	BrowserPickup* clone() const override { return new BrowserPickup(*this); };
	BrowserEvent* cloneAsBrowser() const override { return new BrowserPickup(*this); };

	void actUponBrowserAnim(BrowserAnimation* anim) override;
};

class BrowserDrop : public BrowserEvent
{
private:
	CursorPos dropPos;
public:
	BrowserDrop() {};
	BrowserDrop(CursorPos mapPos) { dropPos = mapPos; };

	BrowserDrop* allocateNew() const override { return new BrowserDrop(); };
	BrowserDrop* clone() const override { return new BrowserDrop(*this); };
	BrowserEvent* cloneAsBrowser() const override { return new BrowserDrop(*this); };

	void actUponBrowserAnim(BrowserAnimation* anim) override;
};

class BrowserSwap : public BrowserEvent
{
private:
	CursorPos swapPos;

public:
	BrowserSwap() {};
	BrowserSwap(CursorPos mapPos) { swapPos = mapPos; };

	BrowserSwap* allocateNew() const override { return new BrowserSwap(); };
	BrowserSwap* clone() const override { return new BrowserSwap(*this); };
	BrowserEvent* cloneAsBrowser() const override { return new BrowserSwap(*this); };

	void actUponBrowserAnim(BrowserAnimation* anim) override;
};