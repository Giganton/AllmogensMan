#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <list>
#include "BattleAnimation.h"
#include "MapAnimation.h"
#include "StatusScreen.h"
#include "StatusAnimation.h"
#include "GraphicsInterface.h"
#include "MapAnimation2.h"
#include "Browsable.h"
#include "SquadManagerAnimation.h"
#include "SquadManagerInitVisuals.h"
#include "CampMenuLayer.h"
#include "CampAnimation.h"
#include "MapAnimationLayer.h"
#include "GraphicsAssets.h"
#include "MouseSignal.h"

#define FRAMELENGTH 1/60

class BattleStage;
class Profession;
class Action;
class Cursor;
class Menu;

class Graphics
{
private:
	GraphicsAssets assets;
	MapAnimation mapAnimation;
	MapAnimation2 mapAnimation2;
	StatusAnimation statusScreenAnimation;
	SquadManagerAnimation squadManimation;
	CampAnimation campAnimation;

	StructuredEventQueue events;

	AnimationLayer* baseLayer;
	StringHandler* stringHandler = nullptr;
	
	sf::RenderWindow* window;

	void loadUITextures(UIMenuPackage* uiPack);
	void loadGrassTextures(MapPackage* mPack);
	void loadRiverTextures(MapPackage* mPack);
	void loadJobTextures(TraitPackage* tPack);
	void loadTraitTextures(TraitPackage* tPack);
	void loadBattleAnimTextures(BattleAnimationPackage* bPack);
	void loadMapOverlayTextures(MapOverlayPackage* moPack);
	void loadProfessionPortraits(UnitPackage* unPack);
public:
	Graphics(std::list<Profession> profs, std::list<std::pair<Terrain, std::string>> terrains, sf::RenderWindow* ww, StringHandler* strHand);
	bool run();

	void initTextures(std::list<Profession> profs, std::list<std::pair<Terrain, std::string>> terrains);

	void drawMenu(Menu menu);
	void initMap(BattleMapVisualData mapData);

	void drawStatusScreen(ScreenVisualData screen);
	void drawVisualStack(GraphicsInterface* stackContainer);

	void applyEvents(GraphicsInterface* gInterface);
	std::vector<MouseSignal> passMousePos(sf::Vector2i mousePos);
	void draw();

	void clearWindow() { window->clear(); };
	
	GraphicsAssets* getAssetsPtr() { return &assets; };
};