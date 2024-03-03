#pragma once
#include "ActionAnimation.h"

class ActionAnimation_Attack : public ActionAnimation
{
private:
	int nrOfStrikesToRun = -1;
	int nrOfStrikesRan = -1;
	//void moveSprites() override;
public:
	ActionAnimation_Attack() {};
	ActionAnimation_Attack(BattleAnimation* battleAnim, ActionResults results, bool isMaster, GraphicsAssets* assets, sf::RenderWindow* ww);

	ActionAnimation* clone() const override { return new ActionAnimation_Attack(*this); };
	ActionAnimation* allocateNew() const override { return new ActionAnimation_Attack(); };

	bool progressAction() override;
};