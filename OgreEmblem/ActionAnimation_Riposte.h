#pragma once
#include "ActionAnimation.h"

class ActionAnimation_Riposte : public ActionAnimation
{
private:
	//void moveSprites() override;
public:
	ActionAnimation_Riposte() {};
	ActionAnimation_Riposte(BattleAnimation* battleAnim, ActionResults results, bool isMaster, GraphicsAssets* assets, sf::RenderWindow* ww);

	ActionAnimation* clone() const override { return new ActionAnimation_Riposte(*this); };
	ActionAnimation* allocateNew() const override { return new ActionAnimation_Riposte(); };

	bool progressAction() override;
};
