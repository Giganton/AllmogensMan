#include "DialogueWindow.h"
#include "GraphicsUtils.h"

DialogueWindow::DialogueWindow(sf::Vector2f sz, sf::Vector2f pos)
{
	size = sz;
	position = pos;

	sf::Vector2f innerSize = sf::Vector2f(size.x - 4, size.y - 4);
	sf::Vector2f innerPos = sf::Vector2f(pos.x + 2, pos.y + 2);

	frameVertices = UTIL::buildFadedBox(position, size, sf::Color::Black);
	boxVertices = UTIL::buildFadedBox(innerPos, innerSize, sf::Color(78,76,108));
}

void DialogueWindow::draw(sf::RenderWindow* window)
{
	window->draw(frameVertices);
	window->draw(boxVertices);
}