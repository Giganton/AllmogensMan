#pragma once
#include <SFML/Graphics.hpp>

class MouseInteractionObject
{
protected:
	sf::RectangleShape interactionRectangle;
	std::vector<std::pair<sf::Image*, sf::RectangleShape>> interactionImages;
	std::vector<sf::ConvexShape> interactionTiles;

	bool hovered = false;
	bool selected = false;

	bool imageIsHovered = false;
	int hoveredImage = -1;



	virtual void hoverThisObject() {};
	void setInteractionBoxSize(sf::Vector2f size);
	void setInteractionBoxPos(sf::Vector2f pos);
	bool isPosInTile(sf::Vector2f pos);

	bool isThisHoveredBy(sf::Vector2f mousePos);
public:
	MouseInteractionObject() {};
	MouseInteractionObject(sf::Vector2f size, sf::Vector2f mapPos);

	void addInteractionImage(sf::Image* img, sf::Vector2f pos);
	void addInteractionTile(sf::Vector2f position);

	virtual void draw(sf::RenderWindow* window) = 0;

	virtual void mousePosUpdate(sf::Vector2i currentMousePos);

	virtual void select() { selected = true; };
	virtual void unSelect() { selected = false; };

	bool isHovered() { return hovered; };
};