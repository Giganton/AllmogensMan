#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "LifeBar.h"

class FighterAnimation
{
private:
	sf::Sprite fighterSprite;
	LifeBar lifebar;

public:
	FighterAnimation() {};

	void draw(sf::RenderWindow* window);
	void progress();
};