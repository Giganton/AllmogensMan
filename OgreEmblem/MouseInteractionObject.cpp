#include "MouseInteractionObject.h"
#include "GraphicsUtils.h"

MouseInteractionObject::MouseInteractionObject(sf::Vector2f size, sf::Vector2f mapPos)
{
	interactionRectangle = sf::RectangleShape(size);
	interactionRectangle.setPosition(mapPos);
}

void MouseInteractionObject::addInteractionImage(sf::Image* image, sf::Vector2f pos)
{
	sf::Vector2u size = image->getSize();
	sf::RectangleShape frame(sf::Vector2f(size.x, size.y));
	frame.setPosition(pos);
	interactionImages.push_back(std::make_pair(image, frame));
}

void MouseInteractionObject::addInteractionTile(sf::Vector2f position)
{
	sf::ConvexShape shape;
	shape.setPointCount(4);

	shape.setPoint(0, sf::Vector2f(position.x + TILE_W / 2, position.y));
	shape.setPoint(1, sf::Vector2f(position.x + TILE_W, position.y + TILE_H / 2));
	shape.setPoint(2, sf::Vector2f(position.x + TILE_W / 2, position.y + TILE_H));
	shape.setPoint(3, sf::Vector2f(position.x, position.y + TILE_H / 2));

	interactionTiles.push_back(shape);
}

void MouseInteractionObject::setInteractionBoxSize(sf::Vector2f size)
{
	interactionRectangle.setSize(size);
}

void MouseInteractionObject::setInteractionBoxPos(sf::Vector2f pos)
{
	interactionRectangle.setPosition(pos);
}

bool MouseInteractionObject::isPosInTile(sf::Vector2f pos)
{
	unsigned int i;
	
	for (i = 0; i < interactionTiles.size(); i++)
	{
		sf::ConvexShape tile = interactionTiles.at(i);

		if (tile.getGlobalBounds().contains(pos))
		{
			int hej = 0;
			sf::Vector2f p1, p2;
			sf::Vector2f origin((tile.getPoint(3).x + tile.getPoint(1).x) / 2, tile.getPoint(3).y);
			sf::Vector2f pos_t = pos - origin;
			if (pos.y <= tile.getPoint(1).y && pos.x >= tile.getPoint(0).x)
			{
				p2 = tile.getPoint(1) - origin;
				p1 = tile.getPoint(0) - origin;
				hej = hej + 1;
			}
			else if (pos.y >= tile.getPoint(1).y && pos.x >= tile.getPoint(0).x)
			{
				p2 = tile.getPoint(2) - origin;
				p1 = tile.getPoint(1) - origin;
				hej = hej + 2;
			}
			else if (pos.y >= tile.getPoint(1).y && pos.x <= tile.getPoint(0).x)
			{
				p2 = tile.getPoint(3) - origin;
				p1 = tile.getPoint(2) - origin;
				hej = hej + 3;
			}
			else if (pos.y <= tile.getPoint(1).y && pos.x <= tile.getPoint(0).x)
			{
				p2 = tile.getPoint(0) - origin;
				p1 = tile.getPoint(3) - origin;
				hej = hej + 4;
			}
			else
			{
				throw new std::exception();
			}
			float k = (p2.y - p1.y) / (p2.x - p1.x);
			float m = p1.y - k * p1.x;

			float p = m / (pos_t.y - k * pos_t.x);
			if (p > 1)
			{
				return true;
			}
		}
	}
	return false;
}

bool MouseInteractionObject::isThisHoveredBy(sf::Vector2f mousePos)
{
	sf::FloatRect rect = interactionRectangle.getGlobalBounds();
	bool rectangleHit = rect.contains(mousePos);
	bool imageHit = false;
	bool tileHit = false;
	unsigned int i;
	for (i = 0; i < interactionImages.size(); i++)
	{
		if (interactionImages.at(i).second.getGlobalBounds().contains(mousePos))
		{
			sf::Vector2f boxPos = interactionImages.at(i).second.getPosition();
			sf::Vector2f pixelPos = mousePos - boxPos;
			sf::Uint8 alpha = interactionImages.at(i).first->getPixel(pixelPos.x, pixelPos.y).a;
			if (alpha > 0)
			{
				imageHit = true;

				imageIsHovered = true;
				hoveredImage = i;
			}
		}
	}

	tileHit = isPosInTile(mousePos);

	if (!imageHit)
	{
		imageIsHovered = false;
		hoveredImage = -1;
	}
	return (rectangleHit || imageHit || tileHit);
}
void MouseInteractionObject::mousePosUpdate(sf::Vector2i currentMousePos)
{
	sf::Vector2f posTransform = sf::Vector2f((float)currentMousePos.x, (float)currentMousePos.y);

	hovered = isThisHoveredBy(posTransform);
}