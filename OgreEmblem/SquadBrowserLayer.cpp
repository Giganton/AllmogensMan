#include "SquadManagerLayer.h"
#include "SquadManagerEvent.h"
#include "SquadManagerAnimation.h"


SquadBrowserLayer::SquadBrowserLayer(SquadManagerAnimation* anim, int layer, sf::RenderWindow* ww, GraphicsAssets* assts, StringHandler* strHandler) : SquadManagerLayer(layer, anim, ww, assts, strHandler)
{
	squadBrowser = BrowserAnimation(anim->getBrowserPackage(), offset, colOff, rowOff, ww);
}

SquadBrowserLayer::SquadBrowserLayer(const SquadBrowserLayer& cpEQ)
{
	middleMan = cpEQ.middleMan;
	if (middleMan)
	{
		nextLevel = cpEQ.nextLevel->clone();
	}
	window = cpEQ.window;
	stringHandler = cpEQ.stringHandler;
	offset = cpEQ.offset;
	layer = cpEQ.layer;
	squadBrowser = cpEQ.squadBrowser;
	squadManagerAnim = cpEQ.squadManagerAnim;

	drawable = cpEQ.drawable;
	seeThrough = cpEQ.seeThrough;
}

SquadBrowserLayer& SquadBrowserLayer::operator=(const SquadBrowserLayer asEQ)
{
	middleMan = asEQ.middleMan;
	if (middleMan)
	{
		nextLevel = asEQ.nextLevel->clone();
	}
	window = asEQ.window;
	stringHandler = asEQ.stringHandler;
	offset = asEQ.offset;
	layer = asEQ.layer;
	squadBrowser = asEQ.squadBrowser;
	squadManagerAnim = asEQ.squadManagerAnim;

	drawable = asEQ.drawable;
	seeThrough = asEQ.seeThrough;

	return *this;
}

void SquadBrowserLayer::applyBrowserEvent(BrowserEvent* event) 
{ 
	return event->actUponBrowserAnim(&squadBrowser); 
}

/*void SquadBrowserLayer::applyBrowsingSquadsEvent(BrowsingSquadsEvent* evnt)
{
	evnt->actUponSquadBrowserLayer(this);
}

void SquadBrowserLayer::applyOpenSquadMenuEvent(OpenSquadMenuEvent* evnt)
{
	evnt->actUponSquadBrowserLayer(this);
}

void SquadBrowserLayer::applyOpenSquadEditorEvent(OpenSquadEditorEvent* evnt)
{
	evnt->actUponSquadBrowserLayer(this);
}*/

/*void SquadBrowserLayer::applySquadManagerEvent(SquadManagerEvent* evnt)
{
	if (evnt->getDepth() != layer)
	{
		throw new std::exception();
	}
	evnt->actUponSquadBrowserLayer(this);
}*/

void SquadBrowserLayer::draw()
{
	squadBrowser.draw();
}

void SquadBrowserLayer::openSquadMenuLayer()
{
	openNewLayer(new SquadMenuLayer(squadManagerAnim, layer + 1, offset, window, assets, stringHandler));
}

void SquadBrowserLayer::openEditSquadLayer()
{
	openNewLayer(new EditSquadLayer(squadManagerAnim, layer + 1, window, assets, stringHandler));
}


void SquadBrowserLayer::applyEvent(StructuredEvent* evnt)
{
	evnt->applyToSquadBrowserLayer(this);
}