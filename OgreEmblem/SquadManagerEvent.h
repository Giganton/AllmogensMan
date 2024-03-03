#pragma once
#include "CampEvent.h"
#include "BrowserEvent.h"
#include "MenuVisualEvent.h"

class SquadManagerLayer;
class SquadBrowserLayer;
class SquadMenuLayer;
class EditSquadLayer;

class SquadManagerEvent : public StructuredEvent
{
protected:
public:
	SquadManagerEvent() {};
	SquadManagerEvent(int lr) : StructuredEvent(lr) { };

	//virtual void actUponSquadManagerAnim(SquadManagerAnimation* anim);
	/*void actUponAnimationLayer(AnimationLayer* layer) override;
	virtual void actUponSquadManagerLayer(SquadManagerLayer* layer) { throw new std::exception(); };

	virtual void actUponSquadBrowserLayer(SquadBrowserLayer* layer) { throw new std::exception(); };
	virtual void actUponEditSquadLayer(EditSquadLayer* layer) { throw new std::exception(); };
	virtual void actUponSquadMenuLayer(SquadMenuLayer* layer) { throw new std::exception(); };*/
};

class BrowsingSquadsEvent : public SquadManagerEvent
{
private:
	BrowserEvent* browserEvent = nullptr;

public:
	BrowsingSquadsEvent() {};
	BrowsingSquadsEvent(int layer, BrowserEvent* event) : SquadManagerEvent(layer) { browserEvent = event->cloneAsBrowser(); };
	~BrowsingSquadsEvent();
	BrowsingSquadsEvent(const BrowsingSquadsEvent& cpEQ);
	BrowsingSquadsEvent& operator=(const BrowsingSquadsEvent asEQ);

	BrowsingSquadsEvent* allocateNew() const override { return new BrowsingSquadsEvent(); };
	BrowsingSquadsEvent* clone() const override { return new BrowsingSquadsEvent(*this); };

	//void actUponSquadManagerLayer(SquadManagerLayer* layer) override;
	//void actUponSquadBrowserLayer(SquadBrowserLayer* layer) override;
	void applyToSquadBrowserLayer(SquadBrowserLayer* layer) override;
	//void openNewAnimationLayer(AnimationLayer* currLayer) override;
};

class SquadManagerMenuEvent : public SquadManagerEvent
{
private:
	MenuVisualEvent menuEvent;

public:
	SquadManagerMenuEvent() {};
	SquadManagerMenuEvent(int layer, MenuVisualEvent evnt) : SquadManagerEvent(layer) { menuEvent = evnt; };

	SquadManagerMenuEvent* allocateNew() const override { return new SquadManagerMenuEvent(); };
	SquadManagerMenuEvent* clone() const override { return new SquadManagerMenuEvent(*this); };

	/*void actUponSquadManagerLayer(SquadManagerLayer* layer) override;
	void actUponSquadMenuLayer(SquadMenuLayer* layer) override;
	void actUponSquadBrowserLayer(SquadBrowserLayer* layer) override;*/

	void applyToSquadMenuLayer(SquadMenuLayer* layer) override;
	void applyToSquadBrowserLayer(SquadBrowserLayer* layer) override;
	void actUponMenuAnim(MenuAnimation* anim) { menuEvent.actUponMenuAnim(anim); };
	//void openNewAnimationLayer(SquadManagerLayer* currLayer);
	//void openNewAnimationLayer(AnimationLayer* currLayer) override;

};

class OpenSquadMenuEvent : public SquadManagerEvent
{
private:

public:
	OpenSquadMenuEvent() {};
	OpenSquadMenuEvent(int level) : SquadManagerEvent(level) {};

	StructuredEvent* clone() const override { return new OpenSquadMenuEvent(*this); };
	StructuredEvent* allocateNew() const override { return new OpenSquadMenuEvent(); };

	//void actUponSquadManagerLayer(SquadManagerLayer* layer) override;
	void actUponSquadBrowserLayer(SquadBrowserLayer* layer);

	void applyToSquadBrowserLayer(SquadBrowserLayer* layer);
};

class OpenUnitMenuEvent : public SquadManagerEvent
{
private:

public:
	OpenUnitMenuEvent() {};
	OpenUnitMenuEvent(int level) : SquadManagerEvent(level) {};

	StructuredEvent* clone() const override { return new OpenUnitMenuEvent(*this); };
	StructuredEvent* allocateNew() const override { return new OpenUnitMenuEvent(); };

	//void actUponSquadManagerLayer(SquadManagerLayer* layer) override;
	void actUponEditSquadLayer(EditSquadLayer* layer);
	void applyToEditSquadLayer(EditSquadLayer* layer) override;
};

class OpenSquadEditorEvent : public SquadManagerEvent
{
private:

public:
	OpenSquadEditorEvent() {};
	OpenSquadEditorEvent(int level) : SquadManagerEvent(level) {};

	StructuredEvent* clone() const override { return new OpenSquadEditorEvent(*this); };
	StructuredEvent* allocateNew() const override { return new OpenSquadEditorEvent(); };

	//void actUponSquadManagerLayer(SquadManagerLayer* layer) override;
	void actUponSquadMenuLayer(SquadMenuLayer* layer);
	void actUponSquadBrowserLayer(SquadBrowserLayer* layer);

	void applyToSquadMenuLayer(SquadMenuLayer* layer) override;
	void applyToSquadBrowserLayer(SquadBrowserLayer* layer) override;

};

class EditSquadEvent : public SquadManagerEvent
{
private:

public:
	EditSquadEvent() {};
	EditSquadEvent(int layer) : SquadManagerEvent(layer) {};

	//void openNewAnimationLayer(SquadManagerLayer* currLayer) override;
};

class EditStateBrowserEvent : public EditSquadEvent
{
private:
	BrowserEvent* browserEvent = nullptr;
	bool squadSide = false;

public:
	EditStateBrowserEvent() {};
	EditStateBrowserEvent(int layer, BrowserEvent* event, bool squadBrowserEvent) : EditSquadEvent(layer) { browserEvent = event->cloneAsBrowser(); squadSide = squadBrowserEvent; };

	EditStateBrowserEvent* allocateNew() const override { return new EditStateBrowserEvent(); };
	EditStateBrowserEvent* clone() const override { return new EditStateBrowserEvent(*this); };

	//void actUponSquadManagerLayer(SquadManagerLayer* layer) override;
	//void actUponEditSquadLayer(EditSquadLayer* layer) override;

	void applyToEditSquadLayer(EditSquadLayer* layer) override;
};

class EditStatePassCursorEvent : public EditSquadEvent
{
private:
	bool unitToSquad = false;
public:
	EditStatePassCursorEvent() {};
	EditStatePassCursorEvent(int layer, bool uts) : EditSquadEvent(layer) { unitToSquad = uts; };

	EditStatePassCursorEvent* allocateNew() const override { return new EditStatePassCursorEvent(); };
	EditStatePassCursorEvent* clone() const override { return new EditStatePassCursorEvent(*this); };

	//void actUponSquadManagerLayer(SquadManagerLayer* layer) override;
	//void actUponEditSquadLayer(EditSquadLayer* layer) override;

	void applyToEditSquadLayer(EditSquadLayer* layer) override;
};

