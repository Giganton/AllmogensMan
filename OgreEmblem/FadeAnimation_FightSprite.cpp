#include "FadeAnimation_FightSprite.h"


FadeAnimation_FightSprite::FadeAnimation_FightSprite(sf::Sprite* spritePtr, int tagNumber, bool fadingOut, double fadeTimeS) : FightSpriteAnimation(spritePtr, tagNumber)
{
	fadeOut = fadingOut;
	fadeTime = fadeTimeS;

	if (fadingOut)
	{
		startAlpha = 255;
		goalAlpha = 0;
	}
	else
	{
		startAlpha = 0;
		goalAlpha = 255;
	}
}

void FadeAnimation_FightSprite::setupStart()
{
	sf::Color currCol = animatedSprite->getColor();
	currCol.a = startAlpha;
	animatedSprite->setColor(currCol);
}


void FadeAnimation_FightSprite::progressInternal()
{
	double percentage;
	sf::Color currCol;

	switch (step)
	{
	case 0:
		if (currentTime < fadeTime)
		{
			percentage = currentTime / fadeTime;
			currCol = animatedSprite->getColor();
			if (fadeOut)
			{
				currCol.a = 255 - percentage * 255;
			}
			else
			{
				currCol.a = percentage * 255;
			}
			animatedSprite->setColor(currCol);
		}
		else
		{
			currCol = animatedSprite->getColor();
			currCol.a = goalAlpha;
			animatedSprite->setColor(currCol);
			step = 1;
		}
		break;
	case 1:
		finished = true;
		break;
	}
}