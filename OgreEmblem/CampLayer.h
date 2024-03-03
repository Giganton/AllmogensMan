#pragma once
#include "AnimationLayer.h"
#include "MapAnimation2.h"

class CampEvent;
class CampMenuEvent;
class CampAnimation;
class OpenSquadManagerEvent;
class OpenMapBrowserEvent;
class GraphicsAssets;

class CampLayer : public AnimationLayer
{
protected:
	CampAnimation* campAnimation = nullptr;

public:
	CampLayer() {};
	CampLayer(CampAnimation* campAnim, int layer, sf::RenderWindow* window, GraphicsAssets* asst, StringHandler* strHandler) : AnimationLayer(layer, window, asst, strHandler) { campAnimation = campAnim; drawable = true; };

	//void applyCampEvent(CampEvent* evnt) override;
	virtual void applyCampMenuEvent(CampMenuEvent* evnt) { throw new std::exception(); };
	virtual void applyOpenSquadManagerEvent(OpenSquadManagerEvent* evnt) { throw new std::exception(); };
};