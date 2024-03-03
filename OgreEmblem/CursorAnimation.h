#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "GraphicsUtils.h"
#include "Cursor.h"

class CursorAnimation
{
protected:
	sf::RenderWindow* window = nullptr;
	sf::Sprite sprite;

	UTIL::ScreenCoord gridSpacing;
	UTIL::ScreenCoord gridOffset;
	//UTIL::ScreenCoord iconSize;

	//std::map < CursorPos, UTIL::ScreenCoord > spriteSize;

	CursorPos currentPos;

	bool active = false;
	bool visible = true;
public:
	CursorAnimation() {};
	CursorAnimation(UTIL::ScreenCoord offset, UTIL::ScreenCoord spacing, sf::Texture* texture, sf::RenderWindow* ww);
	CursorAnimation(UTIL::ScreenCoord offset, UTIL::ScreenCoord spacing, sf::Texture* texture);

	void activate() { active = true; };
	void deactivate() { active = false; };
	CursorPos getPosition() { return currentPos; };

	virtual void moveCursor(CursorPos newPos) = 0;
	void initiateMove(CursorPos start, CursorPos goal);
	virtual void draw();
	//void draw(sf::Sprite holdingSprite);
	//void setSpriteSize(CursorPos pos, UTIL::ScreenCoord size);
	//void resetSpritemap();
	void reInitialize() { moveCursor(currentPos); };


};