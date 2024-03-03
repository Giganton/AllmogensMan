#pragma once
#include "TraitAnimation.h"

class TraitAnimation_HugeStrength : public TraitAnimation
{
private:

public:
	TraitAnimation_HugeStrength() {};
	TraitAnimation_HugeStrength(BattleAnimation* bAnim, std::map<int, SpriteAnimation>* spriteMap, TraitTag results) : TraitAnimation(bAnim, spriteMap, results) {};
	TraitAnimation* clone() const override { return new TraitAnimation_HugeStrength(*this); };

	bool animatePostDamage() override;
};