#pragma once
#include "ActionAnimation.h"

class ActionAnimation_Attached : public ActionAnimation
{
private:
	//void moveSprites() override;
public:
	ActionAnimation_Attached() {};
	ActionAnimation_Attached(BattleAnimation* battleAnim, ActionResults results, bool isMaster, GraphicsAssets* assets, sf::RenderWindow* ww);

	ActionAnimation* clone() const override { return new ActionAnimation_Attached(*this); };
	ActionAnimation* allocateNew() const override { return new ActionAnimation_Attached(); };

	bool progressAction() override;
};