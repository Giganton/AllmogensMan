#pragma once
#include "ActionAnimation.h"

class ActionAnimation_Rage : public ActionAnimation
{
private:
	//void moveSprites() override;
public:
	ActionAnimation_Rage() {};
	ActionAnimation_Rage(BattleAnimation* battleAnim, ActionResults results, bool isMaster, GraphicsAssets* assets, sf::RenderWindow* ww);

	ActionAnimation* clone() const override { return new ActionAnimation_Rage(*this); };
	ActionAnimation* allocateNew() const override { return new ActionAnimation_Rage(); };

	bool progressAction() override;
};