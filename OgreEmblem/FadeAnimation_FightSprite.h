#pragma once
#include "FightSpriteAnimation.h"

class FadeAnimation_FightSprite : public FightSpriteAnimation
{
private:
	double fadeTime = -1;
	bool fadeOut = true;

	int startAlpha = -1;
	int goalAlpha = -1;

	void progressInternal() override;
	void setupStart() override;
public:
	FadeAnimation_FightSprite() {};
	FadeAnimation_FightSprite(sf::Sprite* spritePtr, int tagNumber, bool fadingOut, double fadeTimeS);

	FightSpriteAnimation* clone() const override { return new FadeAnimation_FightSprite(*this); };
	FightSpriteAnimation* allocateNew() const override { return new FadeAnimation_FightSprite(); };
};