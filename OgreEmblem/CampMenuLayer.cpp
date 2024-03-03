#include "CampMenuLayer.h"
#include "MenuVisualEvent.h"
#include "CampEvent.h"
#include "SquadManagerLayer.h"
#include "CampAnimation.h"
#include "MapAnimationLayer.h"


CampMenuLayer::CampMenuLayer(CampAnimation* cAnim, int layer, sf::RenderWindow* window, GraphicsAssets* assts, StringHandler* strHandler) : CampLayer(cAnim, layer, window, assts, strHandler)
{
	menuAnim = HorizontalMenuAnimation(cAnim->getHorizontalMenuPackage(), menuOffset, true, window);
}

CampMenuLayer::CampMenuLayer(const CampMenuLayer& cpEQ)
{
	middleMan = cpEQ.middleMan;
	if (middleMan)
	{
		nextLevel = cpEQ.nextLevel->clone();
	}
	window = cpEQ.window;
	stringHandler = cpEQ.stringHandler;
	layer = cpEQ.layer;
	menuAnim = cpEQ.menuAnim;

	campAnimation = cpEQ.campAnimation;
}

CampMenuLayer& CampMenuLayer::operator=(const CampMenuLayer asEQ)
{
	middleMan = asEQ.middleMan;
	if (middleMan)
	{
		nextLevel = asEQ.nextLevel->clone();
	}
	window = asEQ.window;
	stringHandler = asEQ.stringHandler;
	layer = asEQ.layer;
	menuAnim = asEQ.menuAnim;

	campAnimation = asEQ.campAnimation;

	return *this;
}

/*void CampMenuLayer::applyCampMenuEvent(CampMenuEvent* evnt)
{
	evnt->actUponCampMenuLayer(this);
}

void CampMenuLayer::applyOpenSquadManagerEvent(OpenSquadManagerEvent* evnt)
{
	evnt->actUponCampMenuLayer(this);
}*/

void CampMenuLayer::applyEvent(StructuredEvent* evnt)
{
	evnt->applyToCampMenuLayer(this);
}

void CampMenuLayer::applyMenuEvent(MenuVisualEvent evnt)
{
	evnt.actUponMenuAnim(&menuAnim);
}

void CampMenuLayer::draw()
{
	menuAnim.draw();
}

void CampMenuLayer::openSquadManagerLayer()
{
	openNewLayer(new SquadBrowserLayer(campAnimation->getSquadManagerAnimPtr(), layer + 1, window, assets, stringHandler));
}