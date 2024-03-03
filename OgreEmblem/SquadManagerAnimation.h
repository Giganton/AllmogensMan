#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "BrowserAnimation.h"
#include "VerticalMenuAnimation.h"
#include "GraphicsUtils.h"
#include "MenuVisualData.h"
#include "CampVisualData.h"
#include "SquadManagerInitVisuals.h"
#include "SquadManagerLayer.h"
#include "StringHandler.h"

class GraphicsAssets;

class SquadManagerAnimation
{
private:
	sf::RenderWindow* window = nullptr;
	StringHandler* stringHandler = nullptr;
	UTIL::ScreenCoord browserOffset = UTIL::ScreenCoord(250, 0);
	UTIL::ScreenCoord menuOffset = UTIL::ScreenCoord(250, 800);

	BrowserPackage* bPack = nullptr;
	VerticalMenuPackage* mPack = nullptr;

	SquadBrowserLayer squadBrowserLayer;

	//BrowserAnimation squadBrowserAnimation;
	//VerticalMenuAnimation mainMenuAnimation;

	//MenuVisualData mainMenuData;

public:
	SquadManagerAnimation() {};
	SquadManagerAnimation(BrowserPackage* bPack, VerticalMenuPackage* menuPackage, sf::RenderWindow* ww, GraphicsAssets* assts, StringHandler* strHandler);
	
	void drawEvents(StructuredEventQueue eventQueue);
	//void updateSquadsBrowser(BrowserEvent* event) { event->actUponBrowserAnim(&squadBrowserAnimation); };
	void update(StructuredEventQueue gQueue);
	void draw();
	void applySquadManagerEvent(StructuredEvent* evnt) { squadBrowserLayer.trackEvent(evnt); };

	BrowserPackage* getBrowserPackage() { return bPack; };
	VerticalMenuPackage* getMenuPackage() { return mPack; };
};