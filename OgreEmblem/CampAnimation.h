#pragma once
#include "SquadManagerAnimation.h"
#include "HorizontalMenuAnimation.h"
#include "CampMenuLayer.h"

class GraphicsAssets;

class CampAnimation
{
private:
	SquadManagerAnimation squadManagerAnim;
	//CampMenuLayer menuLayer;
	sf::RenderWindow* window = nullptr;
	StringHandler* stringHandler = nullptr;

	HorizontalMenuPackage* menuPack = nullptr;
public:
	CampAnimation() {};
	CampAnimation(BrowserPackage* bPack, VerticalMenuPackage* vertMenuPackage, HorizontalMenuPackage* horMenuPackage, sf::RenderWindow* ww, GraphicsAssets* assets, StringHandler* strHandler);

	//void update(StructuredEventQueue gQueue);
	//void draw();
	//void applySquadManagerEvent(SquadManagerEvent* evnt) { squadManagerAnim.applySquadManagerEvent(evnt); };

	SquadManagerAnimation* getSquadManagerAnimPtr() { return &squadManagerAnim; };
	HorizontalMenuPackage* getHorizontalMenuPackage() { return menuPack; };

};