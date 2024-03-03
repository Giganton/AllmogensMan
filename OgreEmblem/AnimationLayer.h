#pragma once
#include <SFML/Graphics.hpp>
#include "StructuredEvent.h"
#include "AnimationSignal.h"
#include "MouseSignal.h"
#include "StringHandler.h"

class OpenBattleMapEvent;

class CampEvent;
class SquadManagerEvent;
class MapEvent;
class GraphicsAssets;
class OpenConfirmationEvent;

class AnimationLayer
{
protected:
	std::vector<AnimationSignal> signals;
	std::vector<MouseSignal> mouseSignals;

	AnimationLayer* nextLevel = nullptr;
	bool middleMan = false;
	sf::RenderWindow* window = nullptr;
	GraphicsAssets* assets = nullptr;
	StringHandler* stringHandler = nullptr;

	bool holdNewEvents = false;
	bool drawable = false;
	bool seeThrough = true;

	int layer = -1;

	virtual void applyMousePos(sf::Vector2i mousePos) {};

	void openNewLayer(AnimationLayer* newLayer);
	virtual void draw() = 0;

public:
	AnimationLayer() {};
	AnimationLayer(int lr, sf::RenderWindow* ww, GraphicsAssets* assts, StringHandler* strHandler) { layer = lr; assets = assts; window = ww; stringHandler = strHandler; };

	virtual ~AnimationLayer() { if (middleMan) { delete nextLevel; } };
	virtual AnimationLayer* clone() = 0;

	bool trackEvent(StructuredEvent* event);
	virtual std::vector<MouseSignal> passMousePos(sf::Vector2i mousePos);
	void drawAll();

	//virtual void openSquadBrowserLayer() { throw new std::exception(); };
	//virtual void openSquadMenuLayer() { throw new std::exception(); };
	//virtual void openEditSquadLayer() { throw new std::exception(); };

	virtual void applyCampEvent(CampEvent* evnt) { throw new std::exception(); };
	virtual void applySquadManagerEvent(SquadManagerEvent* evnt) { throw new std::exception(); };
	virtual void applyMapEvent(MapEvent* evnt) { throw new std::exception(); };

	virtual void applyEvent(StructuredEvent* evnt) = 0;

	void closeSubLayer();
	std::vector<AnimationSignal> collectSignals();
	std::vector<MouseSignal> collectMouseSignals();

	bool isOnHold() { return holdNewEvents; };
	bool isSubOnHold();
	bool canSeeThrough() { return seeThrough; };

	void openConfirmationLayer();
	//virtual void applyStructuredEvent(StructuredEvent* event) = 0;
};