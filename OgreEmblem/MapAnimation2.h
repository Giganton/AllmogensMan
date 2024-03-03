#pragma once
#include<vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "VerticalMenuAnimation.h"
#include "BattleAnimation.h"
#include "MovementAnimation2.h"
#include "BattleMapVisualData.h"
#include "GraphicsUtils.h"
#include "SquadRepresentation.h"
#include "MenuVisualData.h"
#include "CameraPanner.h"
#include "MapManagerVisualEventData.h"
#include "CameraController.h"
#include "RiverAnimation.h"


class VerticalMenuPackage;
class MapPackage;
class AnimationSignal;
struct MoveData;

class MapAnimation2
{
private:
	std::vector<std::vector<sf::Sprite>> tileSprites;

    std::vector<std::pair<sf::Texture*, sf::VertexArray>> tileVertices;
    std::vector<std::pair<sf::Texture*, sf::VertexArray>> decorVertices;

    std::vector<std::vector<std::pair<MapCoord, MapCoord>>> rivers;

	std::map < TerrainTypes, sf::Texture>* terrainTextureMap = nullptr;
    //std::map < Direction, sf::Texture >* riverTextureMap = nullptr;
    sf::Texture* gridTexture = nullptr;
    std::vector<sf::Texture>* grassTextureSmall = nullptr;
    std::vector<sf::Texture>* grassTextureMid1 = nullptr;
    std::vector<sf::Texture>* grassTextureMid2 = nullptr;
    std::vector<sf::Texture>* grassTextureBig = nullptr;
    //sf::Texture* riverTexture = nullptr;
	//sf::RenderWindow* window = nullptr;
    CameraController* drawBucket = nullptr;


    VerticalMenuAnimation menuAnimation;

    RiverAnimation riverAnim;

    //metoder
    void createTileVertices(std::vector<std::vector<MapTileVisualData>> tileData);
    void drawTiles();
    void createGrassDecor(std::vector<MapCoord> grid);
    //void drawRiver(std::vector<Direction> riverSides, MapCoord coord, int tileIndex);
    void createRivers();
    std::pair<UTIL::ScreenCoord, UTIL::ScreenCoord> getRiverStretch(std::pair<MapCoord, MapCoord> river);

    //void drawTileVertices();

public:
    MapAnimation2() {};
    MapAnimation2(MapPackage* mapPackage, VerticalMenuPackage* menuPackage, CameraController* dBucket);
    void initMapAnimation(BattleMapVisualData mapVis);
    std::vector<AnimationSignal> drawMap(MapManagerVisualEventData mapData);

    void draw();
    void setBucket(CameraController* dBucket) { drawBucket = dBucket; riverAnim.setBucket(dBucket); };

    sf::VertexArray createTileVertexArray(std::vector<UTIL::ScreenCoord> coords);
    sf::VertexArray createTileVertexArrayV2(std::vector<UTIL::ScreenCoord> coords);
    sf::VertexArray createTileVertexArray(std::vector<MapCoord> coords);
};