#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "GraphicsUtils.h"
#include "Spline.h"

class RiverRepresentation
{
public:
	RiverRepresentation() {};
	RiverRepresentation(sf::VertexArray shape, sf::VertexArray rightShape, sf::VertexArray leftShape, sf::VertexArray mirror) { riverShape = shape; riverEdgeRightShape = rightShape; riverEdgeLeftShape = leftShape; skyMirror = mirror; };

	sf::VertexArray riverShape;
	sf::VertexArray riverEdgeRightShape;
	sf::VertexArray riverEdgeLeftShape;
	sf::VertexArray skyMirror;
};

class CameraController;

class RiverAnimation
{
private:
	int curveDisc = 40;
	float width = 15;
	bool initialized = false;

	std::vector<RiverRepresentation> rivers;
	std::vector<CubicSpline> splines;

	sf::Texture* skyTexture = nullptr;
	sf::Texture* riverTexture = nullptr;
	sf::Texture* edgeTexture = nullptr;

	std::pair<RiverRepresentation, CubicSpline> createRiverRepresentation(std::vector<std::pair<UTIL::ScreenCoord, UTIL::ScreenCoord >> riverToDraw);
	std::pair<std::vector<sf::VertexArray>, std::vector<UTIL::ScreenCoord>> createRiverShapes(CubicSpline shapeSpline);
	sf::VertexArray texturizeRiver(sf::VertexArray shape, std::vector<UTIL::ScreenCoord> curve);
	sf::VertexArray texturizeSky(sf::VertexArray shape, std::vector<UTIL::ScreenCoord> curve);
	std::pair<sf::VertexArray, sf::VertexArray> texturizeEdges(std::pair<sf::VertexArray, sf::VertexArray> shapes, std::vector<UTIL::ScreenCoord> curve);

	RiverRepresentation updateRep(RiverRepresentation riverRep);
	sf::VertexArray updateSkyTexture(sf::VertexArray skyShape);
	sf::Vector2f getSkyCoord(sf::Vector2f riverPos);

	CameraController* drawBucket = nullptr;

public:
	RiverAnimation() {};
	RiverAnimation(sf::Texture* riverT, sf::Texture* edgeT, sf::Texture* skyT, CameraController* dBucket);

	void initRivers(std::vector<std::vector<std::pair<UTIL::ScreenCoord, UTIL::ScreenCoord>>> riversToDraw);
	std::vector<RiverRepresentation> getRiverReps() { if (!initialized) { throw new std::exception(); } return rivers; };
	void draw();

	void setBucket(CameraController* dBucket) { drawBucket = dBucket; };
};