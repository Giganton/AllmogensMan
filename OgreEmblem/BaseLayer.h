#pragma once
#include "AnimationLayer.h"
#include "CampAnimation.h"
#include "MapAnimation2.h"

class MapAnimation2;
class CampAnimation;

class BaseLayer : public AnimationLayer
{
private:
	MapAnimation2 mapAnimator;
	CampAnimation campAnimator;

public:
	BaseLayer() {};
	BaseLayer(MapAnimation2 mapAnim, CampAnimation campAnim, sf::RenderWindow* ww, GraphicsAssets* asst, StringHandler* strHandler);

	BaseLayer(const BaseLayer& cpEQ);
	BaseLayer& operator=(const BaseLayer asEQ);
	~BaseLayer() { AnimationLayer::~AnimationLayer(); };
	BaseLayer* clone() override { return new BaseLayer(*this); };

	void openCampMenuLayer();
	void openDraftScreenLayer();
	void openMapAnimationLayer();
	void closeAllLayers() { closeSubLayer(); };

	void applyEvent(StructuredEvent* evnt) override;

	void draw() override;
};

