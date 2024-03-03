#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "MapCoord.h"

class CameraController;

class MapPackage;

class MovementDotAnimation
{
private:
    sf::Sprite dotSprite;
    sf::Sprite xSprite;

    sf::Texture* dotTexture = nullptr;
    sf::Texture* xTexture = nullptr;

    CameraController* drawBucket = nullptr;

    std::vector<MapCoord> dotPath;
    MapCoord crossPos;
    bool crossVisible = false;

    void drawDots();
    void drawCross();

public:
    MovementDotAnimation() {};
    MovementDotAnimation(MapPackage* mapPackage, CameraController* dBucket);

    void draw();

    void startDotAnimation(std::vector<MapCoord> path);
    void setDotPath(std::vector<MapCoord> path);
    void removeDots() { dotPath = {}; };
    void setMovementCross(MapCoord coorD);
    void startMovementCrossAnimation(MapCoord coord);
    void startMovementCrossRemovalAnimation();
    unsigned int getPathSize() { return dotPath.size(); };

    void eatOffTile();
};
