#pragma once
#include "CursorAnimation.h"

class PointerAnimation : public CursorAnimation
{
private:
	UTIL::ScreenCoord iconSize;
	std::map < CursorPos, UTIL::ScreenCoord > spriteSize;

public:
	PointerAnimation() {};
	PointerAnimation(UTIL::ScreenCoord offset, UTIL::ScreenCoord spacing, UTIL::ScreenCoord icnSize, CursorPos startingPos, sf::Texture* texture, sf::RenderWindow* ww);

	void moveCursor(CursorPos newPos) override;
	void draw() { CursorAnimation::draw(); };
	void draw(sf::Sprite holdingSprite); 
	void setSpriteSize(CursorPos mapPos, UTIL::ScreenCoord size);
	void resetSpritemap();
	CursorPos getCursorPosition() { return currentPos; };
};