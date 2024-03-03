#pragma once
#include <SFML/Graphics.hpp>
//#include "ActionAnimation.h"
#include "ActionTag.h"
#include "Browsable.h"
#include "Direction.h"
#include "Terrain.h"
#include "ProfessionID.h"
#include "TraitTag.h"
#include "ActionTag.h"
#include "JobTag.h"

#define TRAIT_SLOT_SIZE 50

class TraitPackage
{
public:
	std::map< TraitTag, sf::Texture> traitTextures;
	std::map< JobTag, sf::Texture> jobTextures;
	sf::Texture traitBackgroundTexture;
	sf::Texture traitCursor;
	sf::Texture jobForeground;
	sf::Texture defaultJobTexture;


	sf::Image traitCircleHitBox;

	TraitPackage() {};
};

class MapOverlayPackage
{
public:
	sf::Texture victoryBanner;

	MapOverlayPackage() {};
};

class BattleAnimationPackage
{
public:
	sf::Texture lightningStrike;
};

class UnitPackage
{
public:
	std::map < ProfessionTag, sf::Texture> unitPortraitMap;
	sf::Texture defaultPortrait;
	sf::Texture portraitFrame;

	sf::Texture* getProfessionPortrait(ProfessionTag tag);
	sf::Vector2f getPortraitSize();

};

class UIMenuPackage
{
public:
	sf::Texture draftBackground;
};

class MapPackage
{
public:
	std::map < TerrainTypes, sf::Texture> terrainTextureMap;
	std::map < ProfessionTag, sf::Texture> squadTextureMap;
	std::map< Direction, sf::Texture> riverTextureMap;
	sf::Texture gridTexture;
	std::vector<sf::Texture> grassTextureSmall;
	std::vector<sf::Texture> grassTextureMid1;
	std::vector<sf::Texture> grassTextureMid2;
	std::vector<sf::Texture> grassTextureBig;
	sf::Texture riverTexture;
	sf::Texture riverEdgeTexture;
	sf::Texture skyTexture;
	sf::Texture cursorTexture;
	sf::Texture dotTexture;
	sf::Texture xTexture;

	MapPackage() {};
};

class HorizontalMenuPackage
{
public:
	sf::Texture left;
	sf::Texture middle;
	sf::Texture right;

	sf::Texture cursor;
	sf::Font font;

	HorizontalMenuPackage() {};
};

class VerticalMenuPackage
{
public:
	sf::Texture top;
	sf::Texture middle;
	sf::Texture bottom;

	sf::Texture cursor;
	sf::Font font;

	VerticalMenuPackage() {};
};

class ScreenPackage
{
public:
	sf::Texture cursor;
	sf::Font font;

	ScreenPackage() {};
};

class BrowserPackage
{
public:
	sf::Texture cursorTexture;
	sf::Texture background;
	std::map<BrowsableIconTag, std::pair<sf::Texture, sf::IntRect>> iconTextures;
	BrowserPackage() {};
};

class FontPackage
{
public:
	sf::Font standardFont;
	sf::Font nameFont;

	FontPackage() {};
};

class GraphicsAssets
{
public:
	GraphicsAssets() {};
	GraphicsAssets(	MapPackage mapPack, 
					VerticalMenuPackage vertPack, 
					HorizontalMenuPackage horPack, 
					ScreenPackage screenPack,
					BrowserPackage browserPack,
					std::map < ProfessionTag, sf::Texture> unitMap,
					BattleAnimationPackage bPack,
					MapOverlayPackage moPack,
					FontPackage foPack,
					UnitPackage unPack,
					UIMenuPackage uiPack) {
		mapPackage = mapPack; 
		verticalMapMenuPackage = vertPack; 
		horizontalMapMenuPackage = horPack; 
		screenPackage = screenPack; 
		browserPackage = browserPack; 
		unitTextureMap = unitMap; 
		battleAnimationPackage = bPack;
		mapOverlayPackage = moPack;
		fontPackage = foPack;
		uiPackage = uiPack;
	};


	MapPackage mapPackage;
	VerticalMenuPackage verticalMapMenuPackage;
	HorizontalMenuPackage horizontalMapMenuPackage;
	ScreenPackage screenPackage;
	BrowserPackage browserPackage;
	TraitPackage traitPackage;
	//std::map < ActionTag, ActionAnimation> actionMap;
	std::map < ProfessionTag, sf::Texture> unitTextureMap;
	BattleAnimationPackage battleAnimationPackage;
	MapOverlayPackage mapOverlayPackage;
	FontPackage fontPackage;
	UnitPackage unitPackage;
	UIMenuPackage uiPackage;
};