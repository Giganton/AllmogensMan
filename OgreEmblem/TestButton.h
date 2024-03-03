#pragma once
#include "MouseInteractionObject.h"

class TestButton : public MouseInteractionObject
{
private:
	sf::RectangleShape visualBox;

public:
	TestButton() {};
	TestButton(sf::Vector2f size, sf::Vector2f mapPos);

	void draw(sf::RenderWindow* window) override;
	void mousePosUpdate(sf::Vector2i currentMousePos) override;
};