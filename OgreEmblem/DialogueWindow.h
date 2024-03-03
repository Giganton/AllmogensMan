#pragma once
#include <SFML/Graphics.hpp>

class DialogueWindow
{
private:
	sf::Vector2f size;
	sf::Vector2f position;

	sf::VertexArray boxVertices;
	sf::VertexArray frameVertices;

public:
	DialogueWindow() {};
	DialogueWindow(sf::Vector2f size, sf::Vector2f pos);

	sf::Vector2f getSize() { return size; };
	sf::Vector2f getPos() { return position; };
	

	void draw(sf::RenderWindow* window);
};