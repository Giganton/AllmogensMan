#include "GraphicsUtils.h"
#include "MapCoord.h"
#include <SFML/Graphics.hpp>

/*float UTIL::xCoordToScreen(int x) 
{ 
	return float(x * TILE_W); 
}

float UTIL::yCoordToScreen(int y)
{
	return float(y * TILE_H); 
}*/

UTIL::ScreenCoord UTIL::mapCoordToScreenCoord(int x, int y)
{
	return UTIL::ScreenCoord((x - y) * TILE_W / 2, (x + y) * TILE_H / 2);
}
UTIL::ScreenCoord UTIL::mapCoordToScreenCoord(MapCoord mapPos)
{
	int x = mapPos.getX();
	int y = mapPos.getY();
	return UTIL::ScreenCoord((x - y) * TILE_W / 2, (x + y) * TILE_H / 2);
}

UTIL::ScreenCoord UTIL::vector2ScreenCoord(sf::Vector2f vec)
{
	return UTIL::ScreenCoord(vec.x, vec.y); 
}

UTIL::ScreenCoord UTIL::mapCoordToScreenCoordCenter(int x, int y)
{
	return mapCoordToScreenCoord(x, y) + UTIL::ScreenCoord(TILE_W / 2, TILE_H / 2);
}

UTIL::ScreenCoord UTIL::mapCoordToScreenCoordCenter(MapCoord mapPos)
{
	return mapCoordToScreenCoord(mapPos) + UTIL::ScreenCoord(TILE_W / 2, TILE_H / 2);
}

UTIL::ScreenCoord UTIL::closestCoord(UTIL::ScreenCoord contender1, UTIL::ScreenCoord contender2, UTIL::ScreenCoord target)
{
	float dist1 = (target - contender1).abs();
	float dist2 = (target - contender2).abs();
	if (dist1 < dist2)
	{
		return contender1;
	}
	else
	{
		return contender2;
	}
}

bool UTIL::areVectorsParallel(UTIL::ScreenCoord vector1, UTIL::ScreenCoord vector2)
{
	UTIL::ScreenCoord normal1 = vector1 / vector1.abs();
	UTIL::ScreenCoord normal2 = vector2 / vector2.abs();

	if (normal1 == normal2 || normal1 == normal2*(-1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UTIL::areVectorsParallel(UTIL::ScreenCoord vector1, UTIL::ScreenCoord vector2, float tol)
{
	UTIL::ScreenCoord normal1 = vector1 / vector1.abs();
	UTIL::ScreenCoord normal2 = vector2 / vector2.abs();

	if ((normal1 - normal2).abs() < tol || (normal1 - normal2 * (-1)).abs() < tol)
	{
		return true;
	}
	else
	{
		return false;
	}

}

UTIL::ScreenCoord UTIL::upVec()
{
	UTIL::ScreenCoord temp = UTIL::ScreenCoord(TILE_W, TILE_H);
	return temp / temp.abs();
}
UTIL::ScreenCoord UTIL::downVec()
{
	UTIL::ScreenCoord temp = UTIL::ScreenCoord(-TILE_W, -TILE_H);
	return temp / temp.abs();
}
UTIL::ScreenCoord UTIL::leftVec()
{
	UTIL::ScreenCoord temp = UTIL::ScreenCoord(-TILE_W, TILE_H);
	return temp / temp.abs();
}
UTIL::ScreenCoord UTIL::rightVec()
{
	UTIL::ScreenCoord temp = UTIL::ScreenCoord(TILE_W, -TILE_H);
	return temp / temp.abs();
}

sf::VertexArray UTIL::buildFadedBox(sf::Vector2f pos, sf::Vector2f size, sf::Color color)
{
	sf::VertexArray visualQuads = sf::VertexArray(sf::Quads, 4);

	visualQuads[0].position = sf::Vector2f(pos.x, pos.y);
	visualQuads[1].position = sf::Vector2f(pos.x + size.x, pos.y);
	visualQuads[2].position = sf::Vector2f(pos.x + size.x, pos.y + size.y);
	visualQuads[3].position = sf::Vector2f(pos.x, pos.y + size.y);

	visualQuads[0].color = color;
	visualQuads[1].color = color;
	visualQuads[2].color = color - sf::Color(0x20, 0x0a, 0x0, 0x00);
	visualQuads[3].color = color - sf::Color(0x20, 0x0a, 0x0, 0x00);

	return visualQuads;
}

UTIL::ScreenCoord UTIL::getPerpendicular(UTIL::ScreenCoord vector)
{
	float nX, nY;
	if (vector.x == 0)
	{
		nX = 1;
		nY = 0;
	}
	else if (vector.y == 0)
	{
		nX = 0;
		nY = 1;
	}
	else
	{
		nX = vector.y / vector.x;
		nY = -1;
	}
	UTIL::ScreenCoord retVal = UTIL::ScreenCoord(nX, nY);
	retVal = retVal / retVal.abs();
	return retVal;
}

UTIL::ScreenCoord UTIL::turnByAngle(UTIL::ScreenCoord vector, float angle)
{
	float x, y;
	x = vector.x * cos(angle) - vector.y * sin(angle);
	y = vector.x * sin(angle) + vector.y * cos(angle);
	return (UTIL::ScreenCoord(x, y));
}

UTIL::ScreenCoord UTIL::normalize(UTIL::ScreenCoord vector)
{
	return (vector / vector.abs());
}

float UTIL::ScreenCoord::dotProduct(ScreenCoord vector)
{
	return x * vector.x + y * vector.y;
}

float UTIL::getAngle(UTIL::ScreenCoord vector1, UTIL::ScreenCoord vector2)
{
	return acos(vector1.dotProduct(vector2) / (vector1.abs() * vector2.abs()));
}

float UTIL::ScreenCoord::getAngle()
{
	return atan(y / x);
}
