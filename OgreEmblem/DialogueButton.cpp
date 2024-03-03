#include "DialogueButton.h"

DialogueButton::DialogueButton(std::string bttonText, sf::Vector2f pos, GraphicsAssets* assets)
{

	buttonText = bttonText;
	position = pos;

	textDrawer = TextDrawer(assets);
	textDrawer.setStandardFont();

	buttonSize = sf::Vector2f(110, 40);
	textOffset = sf::Vector2f(buttonSize.x / 2, buttonSize.y / 2 - textDrawer.getSize() / 2 + 3);

	setInteractionBoxPos(position);
	setInteractionBoxSize(buttonSize);
}

void DialogueButton::draw(sf::RenderWindow* window)
{
	sf::RectangleShape box = sf::RectangleShape(buttonSize);

	box.setFillColor(sf::Color::Red);
	box.setPosition(position);

	window->draw(box);

	window->draw(textDrawer.drawText(buttonText, position + textOffset, 500, true));

}