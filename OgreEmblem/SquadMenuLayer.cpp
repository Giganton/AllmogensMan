#include "SquadManagerLayer.h"
#include "SquadManagerEvent.h"
#include "SquadManagerAnimation.h"

SquadMenuLayer::SquadMenuLayer(SquadManagerAnimation* anim, int layer, UTIL::ScreenCoord offset, sf::RenderWindow* ww, GraphicsAssets* assts, StringHandler* strHandler) : SquadManagerLayer(layer, anim, ww, assts, strHandler)
{
	squadMenu = new VerticalMenuAnimation(squadManagerAnim->getMenuPackage(), offset, ww);
}

SquadMenuLayer::SquadMenuLayer(const SquadMenuLayer& cpEQ)
{
	middleMan = cpEQ.middleMan;
	if (middleMan)
	{
		nextLevel = cpEQ.nextLevel->clone();
	}

	window = cpEQ.window;
	stringHandler = cpEQ.stringHandler;
	layer = cpEQ.layer;
	squadMenu = cpEQ.squadMenu->clone();
	squadManagerAnim = cpEQ.squadManagerAnim;

	drawable = cpEQ.drawable;
	seeThrough = cpEQ.seeThrough;
}

SquadMenuLayer& SquadMenuLayer::operator=(const SquadMenuLayer asEQ)
{
	middleMan = asEQ.middleMan;
	if (middleMan)
	{
		nextLevel = asEQ.nextLevel->clone();
	}

	window = asEQ.window;
	stringHandler = asEQ.stringHandler;
	layer = asEQ.layer;
	squadMenu = asEQ.squadMenu->clone();
	squadManagerAnim = asEQ.squadManagerAnim;

	drawable = asEQ.drawable;
	seeThrough = asEQ.seeThrough;

	return *this;
}

/*void SquadMenuLayer::applySquadManagerMenuEvent(SquadManagerMenuEvent* evnt)
{
	evnt->actUponSquadMenuLayer(this);
}

void SquadMenuLayer::applyOpenSquadEditorEvent(OpenSquadEditorEvent* evnt)
{
	evnt->actUponSquadMenuLayer(this);
}*/

void SquadMenuLayer::applyEvent(StructuredEvent* evnt)
{
	evnt->applyToSquadMenuLayer(this);
}

void SquadMenuLayer::applyMenuEvent(MenuVisualEvent evnt) 
{ 
	evnt.actUponMenuAnim(squadMenu); 
}

/*void SquadMenuLayer::applySquadManagerEvent(SquadManagerEvent* evnt)
{
	if (evnt->getDepth() != layer)
	{
		throw new std::exception();
	}
	evnt->actUponSquadMenuLayer(this);
}*/

void SquadMenuLayer::draw()
{
	squadMenu->draw();
}

void SquadMenuLayer::openEditSquadLayer()
{
	nextLevel = new EditSquadLayer(squadManagerAnim, layer + 1, window, assets, stringHandler);
	middleMan = true;
}