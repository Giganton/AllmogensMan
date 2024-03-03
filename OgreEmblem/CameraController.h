#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "GraphicsUtils.h"
#include "CameraPanner.h"
#include "MapCoord.h"
#include<queue>
#include "Direction.h"

class CameraController
{
private:
	std::map < int, std::queue<sf::Sprite>> spriteBucket;
	std::map<int, std::map<sf::Texture*, std::queue<sf::VertexArray>>> vertexBucket;
	sf::RenderWindow* window = nullptr;
	CameraPanner panner;
	std::map<sf::Texture*, std::vector<std::pair<sf::IntRect, sf::IntRect>> > tileVertexMap;
	std::map<sf::Texture*, std::vector<std::pair<sf::IntRect, sf::IntRect>> > decorVertexMap;
	std::vector<UTIL::ScreenCoord> tilePositions;
	std::vector<std::vector<std::pair<UTIL::ScreenCoord, UTIL::ScreenCoord>>> rivers;
	sf::Texture* gridTexture = nullptr;
	/*sf::Texture* riverTexture = nullptr;
	sf::Texture* riverEdgeTexture = nullptr;
	sf::Texture* skyTexture = nullptr;*/

	UTIL::ScreenCoord cameraTarget;
	UTIL::ScreenCoord cameraOffset;
	float panningMaxSpeed = 1500;
	float panningSpeed = 0;
	float panningAccel = 30;

	std::clock_t startTime = 0;

	void updateCameraMovement();
	void drawTileVertices();
	void drawDecorVertices();
	void drawGridVertices();

	void drawSpriteQueue(std::queue<sf::Sprite> sQueue);
	void drawVertexQueue(std::map<sf::Texture*, std::queue<sf::VertexArray>> vQueue);

	UTIL::ScreenCoord findWidthVecForRiverEndPoints(UTIL::ScreenCoord dirVector);
public:
	CameraController() {};
	CameraController(sf::RenderWindow* ww);
	CameraController(sf::RenderWindow* ww, UTIL::ScreenCoord offset);

	void addToBucket(sf::Sprite sprite);
	void addToBucket(sf::Sprite sprite, int level);
	void addToBucket(sf::VertexArray vArray, sf::Texture* txt, int layer);

	bool isEmpty() { return spriteBucket.size() == 0; };
	void draw();
	void drawBuckets();


	void center(MapCoord centerOnCoord, bool blinkCamera);
	void pan(MapCoord panToCoord);
	void pan(MapCoord fromCoord, MapCoord toCoord);

	void addTileVertices(sf::Texture* texture, UTIL::ScreenCoord position, sf::IntRect textRectangle);
	void addDecorVertices(sf::Texture* texture, UTIL::ScreenCoord position, sf::IntRect textRectangle);
	void addGridVertices(UTIL::ScreenCoord position);
	void clearVertices() { tileVertexMap.clear(); decorVertexMap.clear(); };

	void drawRivers();
	//void drawRivers2();
	Direction findNextRiverDir(UTIL::ScreenCoord startingPos, UTIL::ScreenCoord endingPos);

	UTIL::ScreenCoord getOffset() { return cameraOffset; };

	/*void addRivers(std::vector<std::vector<std::pair<UTIL::ScreenCoord, UTIL::ScreenCoord>>> rvrs) { rivers = rvrs; };
	void setRiverTexture(sf::Texture* riverText) { riverTexture = riverText; };
	void setRiverEdgeTexture(sf::Texture* riverText) { riverEdgeTexture = riverText; };
	void setSkyTexture(sf::Texture* skyText) { skyTexture = skyText; };*/
	void setGridTexture(sf::Texture* gridText) { gridTexture = gridText; };
};