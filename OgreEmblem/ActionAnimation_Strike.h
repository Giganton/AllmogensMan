#pragma once
#include "ActionAnimation.h"

class ActionAnimation_Strike : public ActionAnimation
{
private:
	int nrOfStrikesToRun = -1;
	int nrOfStrikesRan = -1;
	//void moveSprites() override;
public:
	ActionAnimation_Strike() {};
	ActionAnimation_Strike(BattleAnimation* battleAnim, ActionResults results, bool isMaster, GraphicsAssets* assets, sf::RenderWindow* ww);

	ActionAnimation* clone() const override { return new ActionAnimation_Strike(*this); };
	ActionAnimation* allocateNew() const override { return new ActionAnimation_Strike(); };

	bool progressAction() override;
};