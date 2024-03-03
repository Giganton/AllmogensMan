#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "MapCoord.h"
#include "GraphicsUtils.h"

/*class ScreenCoord
{
public:
	float x;
	float y;
	ScreenCoord(float xPos, float yPos) { x = xPos; y = yPos; };
};
*/

enum class PanDirection { none, north, northeast, east, southeast, south, southwest, west, northwest};
class CameraPanner
{
private:
	float offsetX = 0;
	float offsetY = 0;
	unsigned int windowHeight = 0;
	unsigned int windowWidth = 0;

	float buffertSizeX = 0;
	float buffertSizeY = 0;
	float shiftSizeX = 0;
	float shiftSizeY = 0;

	float panStep = -1;

	UTIL::ScreenCoord findClosestBoundedCoord(UTIL::ScreenCoord coord);
public:
	CameraPanner() {};
	CameraPanner(sf::RenderWindow* window, float tile_w, float tile_h);

	UTIL::ScreenCoord centerCamera(sf::Sprite centerSprite, UTIL::ScreenCoord coord);
	UTIL::ScreenCoord centerCamera(MapCoord coord);
	void centerCameraIfOut(sf::Sprite centerSprite, UTIL::ScreenCoord coord);
	UTIL::ScreenCoord panCamera(float pixelCoordX, float pixelCoordY);
	UTIL::ScreenCoord panCamera(PanDirection dir);
	UTIL::ScreenCoord moveCamera(UTIL::ScreenCoord moveVector);
	bool coordIsWithinBounds(UTIL::ScreenCoord coord);

	UTIL::ScreenCoord getOffset() { return UTIL::ScreenCoord(offsetX, offsetY); };
};