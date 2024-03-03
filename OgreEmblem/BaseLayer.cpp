#include "BaseLayer.h"
#include "MapAnimationLayer.h"
#include "CampMenuLayer.h"
#include "DraftScreenLayer.h"

BaseLayer::BaseLayer(MapAnimation2 mapAnim, CampAnimation campAnim, sf::RenderWindow* ww, GraphicsAssets* asst, StringHandler* strHandler) : AnimationLayer(0, ww, asst, strHandler)
{
	mapAnimator = mapAnim;
	campAnimator = campAnim;
}

BaseLayer::BaseLayer(const BaseLayer& cpEQ)
{
	middleMan = cpEQ.middleMan;
	if (middleMan)
	{
		nextLevel = cpEQ.nextLevel->clone();
	}
	stringHandler = cpEQ.stringHandler;
	window = cpEQ.window;
	mapAnimator = cpEQ.mapAnimator;
	campAnimator = cpEQ.campAnimator;
}

BaseLayer& BaseLayer::operator=(const BaseLayer asEQ)
{
	middleMan = asEQ.middleMan;
	if (middleMan)
	{
		nextLevel = asEQ.nextLevel->clone();
	}
	window = asEQ.window;
	stringHandler = asEQ.stringHandler;
	mapAnimator = asEQ.mapAnimator;
	campAnimator = asEQ.campAnimator;

	return *this;
}

void BaseLayer::openCampMenuLayer()
{
	openNewLayer(new CampMenuLayer(&campAnimator, 1, window, assets, stringHandler));
}

void BaseLayer::openDraftScreenLayer()
{
	openNewLayer(new DraftScreenLayer(1, window, assets, stringHandler));
}

void BaseLayer::openMapAnimationLayer()
{
	openNewLayer(new MapAnimationLayer(mapAnimator, 1, window, assets, stringHandler));
}

void BaseLayer::draw()
{

}

void BaseLayer::applyEvent(StructuredEvent* evnt)
{
	evnt->applyToBaseLayer(this);
}