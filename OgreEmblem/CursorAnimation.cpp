#include "CursorAnimation.h"

CursorAnimation::CursorAnimation(UTIL::ScreenCoord offset, UTIL::ScreenCoord spacing, sf::Texture* texture)
{
	gridOffset = offset;
	gridSpacing = spacing;

	sprite.setTexture(*texture);
	activate();
}


CursorAnimation::CursorAnimation(UTIL::ScreenCoord offset, UTIL::ScreenCoord spacing, sf::Texture* texture, sf::RenderWindow* ww) : CursorAnimation(offset, spacing, texture)
{
	window = ww;
}

void CursorAnimation::initiateMove(CursorPos start, CursorPos goal)
{
	moveCursor(goal);
}

void CursorAnimation::draw()
{
	if (active)
	{
		window->draw(sprite);
	}
}

/*void CursorAnimation::draw(sf::Sprite holdingSprite)
{
	window->draw(sprite);
	holdingSprite.setPosition(sprite.getPosition());
	window->draw(holdingSprite);
}*/

/*void CursorAnimation::setSpriteSize(CursorPos pos, UTIL::ScreenCoord size)
{
	spriteSize.insert({ pos, size });
}

void CursorAnimation::resetSpritemap()
{
	spriteSize.clear();
}*/