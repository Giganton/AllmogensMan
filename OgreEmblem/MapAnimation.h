#pragma once
#include<map>
#include<string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "BattleMap.h"
#include "VerticalMenuAnimation.h"
#include "BattleAnimation.h"
#include "MovementAnimation.h"
#include "CameraPanner.h"
#include "AnimationQueue.h"


/*#define TILE_W 50
#define TILE_H 50*/

class BattleMap;
class AnimationSignal;
class MapManagerVisualData;
class MapPackage;

class MapAnimation
{
private:
    VerticalMenuAnimation menuAnim;
    BattleAnimation battleAnim;
    long int lastDrawnBattle = -1;

    std::vector<sf::Sprite> drawBucket = {};

    float mapOffsetX = 0;
    float mapOffsetY = 0;

    CameraPanner panner;

    std::map < std::string, sf::Texture>* terrainTextureMap = nullptr;
    std::map < ProfessionTag, sf::Texture>* squadTextureMap = nullptr;
    std::map < std::string, sf::Sprite> spriteMap;
    sf::RenderWindow* window = nullptr;

    std::map <long int, std::pair<MovementAnimation, bool>> squadMovementMap; //bool för att se om den har startat ännu

    AnimationQueue animQueue;

    bool animationRunning = false;
    bool battleAnimationRunning = false;
    bool movementAnimationRunning = false;

    sf::Texture* cursorTexture = nullptr;
    sf::Sprite cursorSprite;

    sf::Texture* dotTexture = nullptr;
    sf::Sprite dotSprite;

    sf::Texture* xTexture = nullptr;
    sf::Sprite xSprite;

    sf::Sprite squadSprite;

    void moveCursorSprite(int x, int y);
    float xCoordToScreen(int x) { return float(x * TILE_W); };
    float yCoordToScreen(int y) { return float(y * TILE_H); };
    void drawDots(std::vector<MapCoord> path);
    void drawCross(MapCoord mapPos);
    void drawGrid(BattleMapVisualData mapData);
    std::vector<AnimationSignal> drawSquads(std::vector<SquadData> sData, tagID currentTurn, int signalAddress);
    //void drawOnMap(sf::Sprite sprite);
    void drawOnMap();
    void panMap(float targetX, float targetY);

public:
    MapAnimation() {};
    MapAnimation(MapPackage* mapPackage, BattleAnimation bAnim, VerticalMenuPackage* menuPackage, sf::RenderWindow* ww);
    MapAnimation(const MapAnimation& cpMap);
    MapAnimation& operator = (const MapAnimation asMap);
    std::vector<AnimationSignal> drawMap(MapManagerVisualData map);
    ~MapAnimation();
};