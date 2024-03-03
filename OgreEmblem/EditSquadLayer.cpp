#include "SquadManagerLayer.h"
#include "SquadManagerEvent.h"
#include "SquadManagerAnimation.h"

EditSquadLayer::EditSquadLayer(SquadManagerAnimation* mananim, int layer, sf::RenderWindow* ww, GraphicsAssets* assts, StringHandler* strHandler) : SquadManagerLayer(layer, mananim, ww, assts, strHandler)
{
	unitBrowser = BrowserAnimation(mananim->getBrowserPackage(), UTIL::ScreenCoord(500, 150), 150, 150, window);
	squadBrowser = BrowserAnimation(mananim->getBrowserPackage(), UTIL::ScreenCoord(100, 150), 150, 150, window);
}

EditSquadLayer::EditSquadLayer(const EditSquadLayer& cpEQ)
{
	middleMan = cpEQ.middleMan;
	if (middleMan)
	{
		nextLevel = cpEQ.nextLevel->clone();
	}
	window = cpEQ.window;
	offset = cpEQ.offset;
	layer = cpEQ.layer;
	squadBrowser = cpEQ.squadBrowser;
	unitBrowser = cpEQ.unitBrowser;
	squadManagerAnim = cpEQ.squadManagerAnim;

	drawable = cpEQ.drawable;
	seeThrough = cpEQ.seeThrough;
}

EditSquadLayer& EditSquadLayer::operator=(const EditSquadLayer asEQ)
{
	middleMan = asEQ.middleMan;
	if (middleMan)
	{
		nextLevel = asEQ.nextLevel->clone();
	}
	window = asEQ.window;
	offset = asEQ.offset;
	layer = asEQ.layer;
	squadBrowser = asEQ.squadBrowser;
	unitBrowser = asEQ.unitBrowser;
	squadManagerAnim = asEQ.squadManagerAnim;

	drawable = asEQ.drawable;
	seeThrough = asEQ.seeThrough;

	return *this;
}

/*void EditSquadLayer::applySquadManagerEvent(SquadManagerEvent* evnt)
{
	if (evnt->getDepth() != layer)
	{
		throw new std::exception();
	}
	evnt->actUponEditSquadLayer(this);
}*/

void EditSquadLayer::draw()
{
	window->clear();
	unitBrowser.draw();
	squadBrowser.draw();
}

void EditSquadLayer::applyEvent(StructuredEvent* evnt)
{
	evnt->applyToEditSquadLayer(this);
}

/*void EditSquadLayer::applyEditStateBrowserEvent(EditStateBrowserEvent* evnt)
{
	evnt->actUponEditSquadLayer(this);
}

void EditSquadLayer::applyEditStatePassCursorEvent(EditStatePassCursorEvent* evnt)
{
	evnt->actUponEditSquadLayer(this);
}

void EditSquadLayer::applyOpenUnitMenuEvent(OpenUnitMenuEvent* evnt)
{
	evnt->actUponEditSquadLayer(this);
}*/

void EditSquadLayer::applyUnitBrowserEvent(BrowserEvent* event)
{
	return event->actUponBrowserAnim(&unitBrowser);
}

void EditSquadLayer::applySquadBrowserEvent(BrowserEvent* event)
{
	return event->actUponBrowserAnim(&squadBrowser);
}

void EditSquadLayer::passBrowserCursor(bool passR2L)
{
	if (passR2L)
	{
		squadBrowser.receiveItem(unitBrowser.passItem());
	}
	else
	{
		unitBrowser.receiveItem(squadBrowser.passItem());
	}
}

void EditSquadLayer::openMenuLayer()
{
	nextLevel = new SquadMenuLayer(squadManagerAnim, layer + 1, offset, window,assets, stringHandler);
	middleMan = true;
}