#include "PointerAnimation.h"

PointerAnimation::PointerAnimation(UTIL::ScreenCoord offset, UTIL::ScreenCoord spacing, UTIL::ScreenCoord icnSize, CursorPos startingPos, sf::Texture* texture, sf::RenderWindow* ww) : CursorAnimation(offset, spacing, texture, ww)
{
	iconSize = icnSize;
	moveCursor(startingPos);
}

void PointerAnimation::moveCursor(CursorPos newPos)
{
	float xPos;
	currentPos = newPos;
	float yPos;
	if (spriteSize.find(newPos) == spriteSize.end())
	{
		xPos = gridOffset.x + gridSpacing.x * newPos.x + iconSize.x / 2 - sprite.getTextureRect().width / 2;
		yPos = gridOffset.y + gridSpacing.y * newPos.y + iconSize.y + 5;
	}
	else
	{
		xPos = gridOffset.x + gridSpacing.x * newPos.x + spriteSize.find(newPos)->second.x / 2 - sprite.getTextureRect().width / 2;
		yPos = gridOffset.y + gridSpacing.y * newPos.y + spriteSize.find(newPos)->second.y + 5;
	}

	sprite.setPosition(xPos, yPos);
}

void PointerAnimation::draw(sf::Sprite holdingSprite)
{
	window->draw(sprite);
	holdingSprite.setPosition(sprite.getPosition());
	window->draw(holdingSprite);
}

void PointerAnimation::setSpriteSize(CursorPos mapPos, UTIL::ScreenCoord size)
{
	spriteSize.insert({ mapPos, size });
}

void PointerAnimation::resetSpritemap()
{
	spriteSize.clear();
}