#include "CampAnimation.h"
#include "GraphicsAssets.h"


CampAnimation::CampAnimation(BrowserPackage* bPack, VerticalMenuPackage* vertMenuPackage, HorizontalMenuPackage* horMenuPackage, sf::RenderWindow* ww, GraphicsAssets* assets, StringHandler* strHandler)
{
	stringHandler = strHandler;
	squadManagerAnim = SquadManagerAnimation(bPack, vertMenuPackage, ww, assets, stringHandler);
	menuPack = horMenuPackage;
	window = ww;
}