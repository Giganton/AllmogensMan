#include "SquadManagerAnimation.h"
#include "GraphicsAssets.h"

SquadManagerAnimation::SquadManagerAnimation(BrowserPackage* brPack, VerticalMenuPackage* menuPack, sf::RenderWindow* ww, GraphicsAssets* assts, StringHandler* strHandler)
{
	window = ww;
	stringHandler = strHandler;
	bPack = brPack;
	mPack = menuPack;

	squadBrowserLayer = SquadBrowserLayer(this, 1, window, assts, stringHandler);
	//squadBrowserAnimation = BrowserAnimation(bPack, browserOffset, 50, 50, window);
	//mainMenuAnimation = VerticalMenuAnimation(menuPack, UTIL::ScreenCoord(0, window->getSize().y - 102), window);
}

void SquadManagerAnimation::update(StructuredEventQueue gQueue)
{
	drawEvents(gQueue);
}

void SquadManagerAnimation::draw()
{
	//squadBrowserAnimation.draw();
	//mainMenuAnimation.draw(mainMenuData);
	squadBrowserLayer.draw();
}

void SquadManagerAnimation::drawEvents(StructuredEventQueue eventQueue)
{
	while (eventQueue.size() > 0)
	{
		StructuredEvent* temp = eventQueue.pop();
		//temp->actUponSquadManagerAnim(this);
		delete temp;
	}
}