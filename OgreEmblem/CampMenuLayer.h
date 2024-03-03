#pragma once
#include "CampLayer.h"
#include "HorizontalMenuAnimation.h"

class MenuVisualEvent;
class OpenSquadManagerEvent;

class CampMenuLayer : public CampLayer
{
private:
	UTIL::ScreenCoord menuOffset = UTIL::ScreenCoord(500, 800);
	HorizontalMenuAnimation menuAnim;
public:
	CampMenuLayer() {};
	CampMenuLayer(CampAnimation* cAnim, int layer, sf::RenderWindow* window, GraphicsAssets* assts, StringHandler* strHandler);

	CampMenuLayer(const CampMenuLayer& cpEQ);
	CampMenuLayer& operator=(const CampMenuLayer asEQ);
	~CampMenuLayer() { AnimationLayer::~AnimationLayer(); };
	CampMenuLayer* clone() override { return new CampMenuLayer(*this); };

	//void applyCampMenuEvent(CampMenuEvent* evnt) override;
	//void applyOpenSquadManagerEvent(OpenSquadManagerEvent* evnt) override;

	void draw() override;

	void applyEvent(StructuredEvent* evnt) override;
	void openSquadManagerLayer();
	void applyMenuEvent(MenuVisualEvent event);

};