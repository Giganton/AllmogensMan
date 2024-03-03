#pragma once
#define TILE_W 250
#define TILE_H 146

#define MAP_SPRITE_W 40
#define MAP_SPRITE_H 47
#define SPRITE_ANIM_STEP_TIME 0.5f
#define SPRITE_ANIM_STEP_NR 2
#define JOB_WIDTH 347
#define JOB_HEIGHT 163
#define LESSER_TRAIT_WIDTH 50
#define LESSER_TRAIT_HEIGHT 50
#include <math.h>
#include <SFML/Graphics.hpp>

class MapCoord;
class Vector2f;

namespace UTIL {
	// extern:
	//float xCoordToScreen(int x);
	//float yCoordToScreen(int y);

	class ScreenCoord
	{
	public:
		ScreenCoord() {};
		ScreenCoord(float xPos, float yPos) { x = xPos; y = yPos; };
		ScreenCoord operator-(const ScreenCoord& in) const { return ScreenCoord(x - in.x, y - in.y); };
		ScreenCoord operator+(const ScreenCoord& in) const { return ScreenCoord(x + in.x, y + in.y); };
		ScreenCoord operator/(const float in) const { return ScreenCoord(x / in, y / in); };
		ScreenCoord operator*(const float in) const { return ScreenCoord(x * in, y * in); };
		bool operator==(const ScreenCoord& in) const { return (x == in.x && y == in.y); };
		float dotProduct(ScreenCoord vector);
		float getAngle();

		ScreenCoord mirrorY() { return ScreenCoord(x, -y); };
		ScreenCoord mirrorX() { return ScreenCoord(-x, y); };

		float abs() { return (sqrt(x * x + y * y)); };

		float x = -1;
		float y = -1;
	};
	ScreenCoord vector2ScreenCoord(sf::Vector2f vec);
	ScreenCoord mapCoordToScreenCoord(int x, int y);
	ScreenCoord mapCoordToScreenCoord(MapCoord mapPos);
	ScreenCoord mapCoordToScreenCoordCenter(int x, int y);
	ScreenCoord mapCoordToScreenCoordCenter(MapCoord mapPos);
	ScreenCoord getPerpendicular(ScreenCoord vector);
	ScreenCoord turnByAngle(ScreenCoord vector, float angle);
	ScreenCoord normalize(ScreenCoord vector);
	float getAngle(ScreenCoord vector1, ScreenCoord vector2);
	ScreenCoord closestCoord(ScreenCoord contender1, ScreenCoord contender2, ScreenCoord target);
	ScreenCoord upVec();
	ScreenCoord downVec();
	ScreenCoord leftVec();
	ScreenCoord rightVec();
	sf::VertexArray buildFadedBox(sf::Vector2f pos, sf::Vector2f size, sf::Color color);

	bool areVectorsParallel(UTIL::ScreenCoord vector1, UTIL::ScreenCoord vector2);
	bool areVectorsParallel(UTIL::ScreenCoord vector1, UTIL::ScreenCoord vector2, float tol);
} // << MON