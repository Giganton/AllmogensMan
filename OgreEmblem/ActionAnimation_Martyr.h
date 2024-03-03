#pragma once
#include "ActionAnimation.h"

class ActionAnimation_Martyr : public ActionAnimation
{
private:
	std::clock_t startTime = 0;
	std::vector<double> times;
	std::vector<double> times2;

	bool jumpingHome = false;
	bool martyrDied = false;

	bool progressAction_jumpingTo();
	bool progressAction_jumpingHome();
public:
	ActionAnimation_Martyr() {};
	ActionAnimation_Martyr(BattleAnimation* battleAnim, ActionResults results, bool isMaster, GraphicsAssets* assets, sf::RenderWindow* ww);

	ActionAnimation* clone() const override { return new ActionAnimation_Martyr(*this); };
	ActionAnimation* allocateNew() const override { return new ActionAnimation_Martyr(); };

	bool progressAction() override;
};
