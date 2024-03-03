#include "TestButton.h"

TestButton::TestButton(sf::Vector2f size, sf::Vector2f mapPos) : MouseInteractionObject(size, mapPos)
{
	visualBox = sf::RectangleShape(size);
	visualBox.setPosition(mapPos);
	visualBox.setFillColor(sf::Color::Magenta);
}

void TestButton::draw(sf::RenderWindow* window)
{
	window->draw(visualBox);
}

void TestButton::mousePosUpdate(sf::Vector2i currentMousePos)
{
	sf::Vector2f posTransform = sf::Vector2f((float)currentMousePos.x, (float)currentMousePos.y);
	if (interactionRectangle.getGlobalBounds().contains(posTransform))
	{
		if (!hovered)
		{
			hovered = true;
			visualBox.setFillColor(sf::Color::Yellow);
		}
	}
	else
	{
		if (hovered)
		{
			hovered = false;
			visualBox.setFillColor(sf::Color::Magenta);
		}
	}
}