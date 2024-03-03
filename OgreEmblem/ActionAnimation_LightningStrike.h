#pragma once
#include "ActionAnimation.h"

class ActionAnimation_LightningStrike : public ActionAnimation
{
private:
	sf::Sprite boltSprite;
	bool drawBolt = false;
	std::clock_t startTime = 0; 
	UTIL::ScreenCoord boltSource;
	double fadePercent = 0;
public:
	ActionAnimation_LightningStrike() {};
	ActionAnimation_LightningStrike(BattleAnimation* battleAnim, ActionResults results, bool isMaster, GraphicsAssets* assets, sf::RenderWindow* ww);

	ActionAnimation* clone() const override { return new ActionAnimation_LightningStrike(*this); };
	ActionAnimation* allocateNew() const override { return new ActionAnimation_LightningStrike(); };

	bool progressAction() override;
};