#pragma once
#include "BrowserAnimation.h"
#include "VerticalMenuAnimation.h"
#include "CampLayer.h"

class SquadManagerEvent;
class MenuVisualEvent;
class BrowsingSquadsEvent;
class EditStateBrowserEvent;
class SquadManagerMenuEvent;
class EditStatePassCursorEvent;
class SquadMenuEvent;
class OpenSquadMenuEvent;
class OpenUnitMenuEvent;
class OpenSquadEditorEvent;
class GraphicsAssets;

class SquadManagerLayer : public AnimationLayer
{
protected:
	//SquadManagerLayer* nextLevel = nullptr;
	//bool middleMan = false;
	//sf::RenderWindow* window = nullptr;

	SquadManagerAnimation* squadManagerAnim = nullptr;

	//VerticalMenuAnimation squadMenu;
public:
	SquadManagerLayer() {};
	SquadManagerLayer(int lr, SquadManagerAnimation* anim, sf::RenderWindow* ww, GraphicsAssets* asst, StringHandler* strHandler) : AnimationLayer(lr, ww, asst, strHandler) { squadManagerAnim = anim; drawable = true; };

	virtual ~SquadManagerLayer() { if (middleMan) { delete nextLevel; } };

	//void trackSquadManagerEvent(SquadManagerEvent* event);
	//void applySquadManagerEvent(SquadManagerEvent* event);

	/*virtual void applyBrowsingSquadsEvent(BrowsingSquadsEvent* evnt) { throw new std::exception(); };
	virtual void applyEditStateBrowserEvent(EditStateBrowserEvent* evnt) { throw new std::exception(); };
	virtual void applySquadManagerMenuEvent(SquadManagerMenuEvent* evnt) { throw new std::exception(); };
	virtual void applyEditStatePassCursorEvent(EditStatePassCursorEvent* evnt) { throw new std::exception(); };
	virtual void applyOpenSquadMenuEvent(OpenSquadMenuEvent* evnt) { throw new std::exception(); };
	virtual void applyOpenUnitMenuEvent(OpenUnitMenuEvent* evnt) { throw new std::exception(); };
	virtual void applyOpenSquadEditorEvent(OpenSquadEditorEvent* evnt) { throw new std::exception(); };*/
	//virtual void draw() = 0;

	/*virtual void openSquadBrowserLayer() { throw new std::exception(); };
	virtual void openSquadMenuLayer() { throw new std::exception(); };
	virtual void openEditSquadLayer() { throw new std::exception(); };
	virtual void openMenuLayer() { throw new std::exception(); };*/

};

class SquadBrowserLayer : public SquadManagerLayer
{
private:
	BrowserAnimation squadBrowser;
	UTIL::ScreenCoord offset = UTIL::ScreenCoord(250, 0);
	float colOff = 200;
	float rowOff = 75;

public:
	SquadBrowserLayer() {};
	SquadBrowserLayer(SquadManagerAnimation* manager, int layer, sf::RenderWindow* ww, GraphicsAssets* assts, StringHandler* strHandler);
	SquadBrowserLayer(const SquadBrowserLayer& cpEQ);
	SquadBrowserLayer& operator=(const SquadBrowserLayer asEQ);
	~SquadBrowserLayer() { SquadManagerLayer::~SquadManagerLayer(); };

	void applyBrowserEvent(BrowserEvent* event);

	SquadBrowserLayer* clone() override { return new SquadBrowserLayer(*this); };

	//void applyBrowsingSquadsEvent(BrowsingSquadsEvent* evnt) override;
	//void applyOpenSquadMenuEvent(OpenSquadMenuEvent* evnt) override;
	//void applyOpenSquadEditorEvent(OpenSquadEditorEvent* evnt) override;

	void applyEvent(StructuredEvent* evnt) override;

	//void applySquadManagerEvent(SquadManagerEvent* event) override;
	void openSquadMenuLayer();
	void openEditSquadLayer();

	void draw() override;
};

class EditSquadLayer : public SquadManagerLayer
{
private:
	BrowserAnimation unitBrowser;
	BrowserAnimation squadBrowser;
	UTIL::ScreenCoord offset;

public:
	EditSquadLayer() {};
	EditSquadLayer(SquadManagerAnimation* mananim, int layer, sf::RenderWindow* ww, GraphicsAssets* assts, StringHandler* strHandler);

	EditSquadLayer(const EditSquadLayer& cpEQ);
	EditSquadLayer& operator=(const EditSquadLayer asEQ);
	~EditSquadLayer() { SquadManagerLayer::~SquadManagerLayer(); };

	EditSquadLayer* clone() override { return new EditSquadLayer(*this); };
	//void applySquadManagerEvent(SquadManagerEvent* event) override;

	/*void applyEditStateBrowserEvent(EditStateBrowserEvent* evnt) override;
	void applyEditStatePassCursorEvent(EditStatePassCursorEvent* evnt) override;
	void applyOpenUnitMenuEvent(OpenUnitMenuEvent* evnt) override;*/
	void draw() override;

	void openMenuLayer();

	void applyEvent(StructuredEvent* evnt) override;

	void applySquadBrowserEvent(BrowserEvent* event);
	void applyUnitBrowserEvent(BrowserEvent* event);

	void passBrowserCursor(bool passR2L);
};

class SquadMenuLayer : public SquadManagerLayer
{
private:
	MenuAnimation* squadMenu = nullptr;

public:
	SquadMenuLayer() {}
	SquadMenuLayer(SquadManagerAnimation* manager, int layer, UTIL::ScreenCoord xOff, sf::RenderWindow* ww, GraphicsAssets* assts, StringHandler* strHandler);
	SquadMenuLayer(const SquadMenuLayer& cpEQ);
	SquadMenuLayer& operator=(const SquadMenuLayer asEQ);
	~SquadMenuLayer() { SquadManagerLayer::~SquadManagerLayer(); delete squadMenu; };

	SquadMenuLayer* clone() override { return new SquadMenuLayer(*this); };

	/*void applySquadManagerMenuEvent(SquadManagerMenuEvent* evnt) override;
	void applyOpenSquadEditorEvent(OpenSquadEditorEvent* evnt) override;*/

	void applyEvent(StructuredEvent* evnt) override;
	void applyMenuEvent(MenuVisualEvent evnt);

	void draw() override;

	//void applySquadManagerEvent(SquadManagerEvent* event) override;
	void openEditSquadLayer();
};