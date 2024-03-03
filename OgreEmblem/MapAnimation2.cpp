#include "MapAnimation2.h"
#include "AnimationSignal.h"
#include "MovementStage.h"
#include "GraphicsAssets.h"
#include <stdlib.h>

MapAnimation2::MapAnimation2(MapPackage* mapPackage, VerticalMenuPackage* menuPackage, CameraController* dBucket)
{
	terrainTextureMap = &mapPackage->terrainTextureMap;
	gridTexture = &mapPackage->gridTexture;
	grassTextureSmall = &mapPackage->grassTextureSmall;
	grassTextureMid1 = &mapPackage->grassTextureMid1;
	grassTextureMid2 = &mapPackage->grassTextureMid2;
	grassTextureBig = &mapPackage->grassTextureBig;

	//riverTextureMap = &mapPackage->riverTextureMap;
	//riverTexture = &mapPackage->riverTexture;
	drawBucket = dBucket;
	riverAnim = RiverAnimation(&mapPackage->riverTexture, &mapPackage->riverEdgeTexture, &mapPackage->skyTexture, drawBucket);


	/*drawBucket->setRiverTexture(riverTexture);
	drawBucket->setRiverEdgeTexture(&mapPackage->riverEdgeTexture);
	drawBucket->setSkyTexture(&mapPackage->skyTexture);*/
	drawBucket->setGridTexture(&mapPackage->gridTexture);

	
}

void MapAnimation2::initMapAnimation(BattleMapVisualData mapVis)
{
	tileSprites.clear();
	drawBucket->clearVertices();

	std::vector<std::vector<MapTileVisualData>> grid = mapVis.getGrid();
	createTileVertices(grid);
	rivers = mapVis.getRivers();

	/*for (i = 0; i < mapVis.getMapWidth(); i++)
	{
		std::vector<sf::Sprite> temp;
		tileSprites.push_back(temp);
		for (j = 0; j < mapVis.getMapHeight(); j++)
		{
			sf::Sprite tempSprite;
			Terrain terr = grid.at(i).at(j).terrain;
			if (terr.getType() == TerrainTypes::noTerrain)
			{

			}
			else
			{
				UTIL::ScreenCoord pos = UTIL::mapCoordToScreenCoord(i, j);
				sf::IntRect textRect = sf::IntRect(0, 0, TILE_W, TILE_H);
				drawBucket->addTileVertices(&terrainTextureMap->find(terr.getType())->second, pos, textRect);
				//drawBucket->addTileVertices(gridTexture, pos, textRect);
				drawBucket->addGridVertices(pos);

				drawGrassDecor(MapCoord(i, j), i);
			}
			if (!grid.at(i).at(j).riverSides.empty())
			{
				//drawRiver(grid.at(i).at(j).riverSides, MapCoord(i, j), i);
			}
		}
	}*/
	createRivers();
}

/*void MapAnimation2::drawRiver(std::vector<Direction> riverSides, MapCoord coord, int tileIndex)
{
	int i;
	sf::Sprite riverSprite;
	UTIL::ScreenCoord screenPos = UTIL::mapCoordToScreenCoord(coord);
	riverSprite.setPosition(screenPos.x, screenPos.y);
	for (i = 0; i < riverSides.size(); i++)
	{
		riverSprite.setTexture(riverTextureMap->find(riverSides.at(i))->second);
		tileSprites.at(tileIndex).push_back(riverSprite);
	}
}*/
void MapAnimation2::createTileVertices(std::vector<std::vector<MapTileVisualData>> tileData)
{
	tileVertices.clear();
	std::map< TerrainTypes, std::vector<MapCoord>> terrainCoordMap;
	unsigned int i, j;
	for (i = 0; i < tileData.size(); i++)
	{
		for (j = 0; j < tileData.at(i).size(); j++)
		{
			TerrainTypes terrain = tileData.at(i).at(j).terrain.getType();
			std::map< TerrainTypes, std::vector<MapCoord>>::iterator it = terrainCoordMap.find(terrain);
			if (it != terrainCoordMap.end())
			{
				terrainCoordMap.find(terrain)->second.push_back(MapCoord(i, j));
			}
			else if ( terrain != TerrainTypes::noTerrain)
			{
				std::vector<MapCoord> temp = { MapCoord(i,j) };
				terrainCoordMap.insert({ terrain , temp });
			}
		}
	}
	createGrassDecor(terrainCoordMap.find(TerrainTypes::field)->second);

	std::map< TerrainTypes, std::vector<MapCoord>>::iterator it;

	for (it = terrainCoordMap.begin(); it != terrainCoordMap.end(); it++)
	{
		std::vector<MapCoord> coords = it->second;
		sf::Texture* texture = &terrainTextureMap->find(it->first)->second;
		tileVertices.push_back(std::make_pair(texture, createTileVertexArray(coords)));
	}
}

sf::VertexArray MapAnimation2::createTileVertexArray(std::vector<UTIL::ScreenCoord> coords)
{
	sf::VertexArray quads = sf::VertexArray(sf::Quads, coords.size() * 4);
	unsigned int i;
	for (i = 0; i < coords.size(); i++)
	{
		UTIL::ScreenCoord mapPos = coords.at(i);
		quads[i * 4].position = sf::Vector2f(mapPos.x, mapPos.y);
		quads[i * 4 + 1].position = sf::Vector2f(mapPos.x + TILE_W, mapPos.y);
		quads[i * 4 + 2].position = sf::Vector2f(mapPos.x + TILE_W, mapPos.y + TILE_H);
		quads[i * 4 + 3].position = sf::Vector2f(mapPos.x, mapPos.y + TILE_H);

		quads[i * 4].texCoords = sf::Vector2f(0, 0);
		quads[i * 4 + 1].texCoords = sf::Vector2f(TILE_W, 0);
		quads[i * 4 + 2].texCoords = sf::Vector2f(TILE_W, TILE_H);
		quads[i * 4 + 3].texCoords = sf::Vector2f(0, TILE_H);
	}
	return quads;
}

sf::VertexArray MapAnimation2::createTileVertexArrayV2(std::vector<UTIL::ScreenCoord> coords)
{
	sf::VertexArray quads = sf::VertexArray(sf::Quads, coords.size() * 4);
	unsigned int i;
	for (i = 0; i < coords.size(); i++)
	{
		UTIL::ScreenCoord mapPos = coords.at(i);
		quads[i * 4].position = sf::Vector2f(mapPos.x + TILE_W / 2, mapPos.y);
		quads[i * 4 + 1].position = sf::Vector2f(mapPos.x + TILE_W, mapPos.y + TILE_H / 2);
		quads[i * 4 + 2].position = sf::Vector2f(mapPos.x + TILE_W / 2, mapPos.y + TILE_H);
		quads[i * 4 + 3].position = sf::Vector2f(mapPos.x, mapPos.y + TILE_H / 2);

		quads[i * 4].texCoords = sf::Vector2f(0, 0);
		quads[i * 4 + 1].texCoords = sf::Vector2f(TILE_W, 0);
		quads[i * 4 + 2].texCoords = sf::Vector2f(TILE_W, TILE_H);
		quads[i * 4 + 3].texCoords = sf::Vector2f(0, TILE_H);
	}
	return quads;
}

sf::VertexArray MapAnimation2::createTileVertexArray(std::vector<MapCoord> coords)
{
	std::vector<UTIL::ScreenCoord> screenCoords;
	unsigned int i;
	for (i = 0; i < coords.size(); i++)
	{
		screenCoords.push_back(UTIL::mapCoordToScreenCoord(coords.at(i)));
	}
	return createTileVertexArray(screenCoords);
}

void MapAnimation2::createRivers()
{
	unsigned int i, j;
	std::vector<std::vector<std::pair<UTIL::ScreenCoord, UTIL::ScreenCoord>>> riverCoord;
	UTIL::ScreenCoord edge1;
	UTIL::ScreenCoord edge2;
	UTIL::ScreenCoord lastEdge;
	for (i = 0; i < rivers.size(); i++)
	{
		std::vector<std::pair<UTIL::ScreenCoord, UTIL::ScreenCoord>> temp1;
		riverCoord.push_back(temp1);
		for (j = 0; j < rivers.at(i).size(); j++)
		{
			std::pair<UTIL::ScreenCoord, UTIL::ScreenCoord> currentStretch = getRiverStretch(rivers.at(i).at(j));
			if (j == 0 && rivers.at(i).size() > 1)
			{
				std::pair<UTIL::ScreenCoord, UTIL::ScreenCoord> nextStretch = getRiverStretch(rivers.at(i).at(j + 1));
				if ((currentStretch.first == nextStretch.first) || (currentStretch.first == nextStretch.second))
				{
					edge1 = currentStretch.second;
					edge2 = currentStretch.first;
				}
				else if ((currentStretch.second == nextStretch.first) || (currentStretch.second == nextStretch.second))
				{
					edge1 = currentStretch.first;
					edge2 = currentStretch.second;
				}
				else
				{
					throw new std::exception();
				}
			}
			else if (j == 0)
			{
				edge1 = currentStretch.first;
				edge2 = currentStretch.second;
			}
			else
			{
				std::pair<UTIL::ScreenCoord, UTIL::ScreenCoord> prevStretch = getRiverStretch(rivers.at(i).at(j - 1));
				if (currentStretch.first == lastEdge)
				{
					edge1 = currentStretch.first;
					edge2 = currentStretch.second;
				}
				else if (currentStretch.second == lastEdge)
				{
					edge1 = currentStretch.second;
					edge2 = currentStretch.first;
				}
				else
				{
					throw new std::exception();
				}
			}
			lastEdge = edge2;
			riverCoord.at(i).push_back(std::make_pair(edge1, edge2));
		}
	}
	riverAnim.initRivers(riverCoord);
}

std::pair<UTIL::ScreenCoord, UTIL::ScreenCoord> MapAnimation2::getRiverStretch(std::pair<MapCoord, MapCoord> river)
{
	UTIL::ScreenCoord coord1 = UTIL::mapCoordToScreenCoordCenter(river.first);
	UTIL::ScreenCoord coord2 = UTIL::mapCoordToScreenCoordCenter(river.second);
	UTIL::ScreenCoord middle = (coord2 - coord1) / 2;
	UTIL::ScreenCoord normalizedEdgeVector = middle.mirrorY()/middle.abs();
	float edgeLength = sqrt(TILE_W / 2 * TILE_W / 2 + TILE_H / 2 * TILE_H / 2);
	UTIL::ScreenCoord edge1 = coord1 + middle + normalizedEdgeVector *edgeLength / 2;
	UTIL::ScreenCoord edge2 = coord1 + middle - normalizedEdgeVector * edgeLength / 2;

	return std::make_pair(edge1, edge2);
}

void MapAnimation2::createGrassDecor(std::vector<MapCoord> grassGrid)
{
	decorVertices.clear();
	float doubleProc = 0.5;
	std::vector<std::vector<MapCoord>> smallVectors = { {} ,{}, {} };
	std::vector<std::vector<MapCoord>> mid1Vectors = { {} ,{}, {} };
	std::vector<std::vector<MapCoord>> mid2Vectors = { {} ,{}, {} };
	std::vector<std::vector<MapCoord>> bigVectors = { {} ,{}, {} };
	unsigned int i;
	double randProc;
	int randNum;
	int randInd;
	int randInd2;

	for (i = 0; i < grassGrid.size(); i++)
	{
		MapCoord tileCoord = grassGrid.at(i);
		srand(tileCoord.getX()*1000 + tileCoord.getY());
		//small
		randNum = rand();
		randInd = randNum % 3;
		randProc = ((double)randNum / RAND_MAX);

		smallVectors.at(randInd).push_back(grassGrid.at(i));

		if (randProc > doubleProc)
		{
			randInd2 = (rand() % 2) + 1;
			randInd = (randInd + randInd2) % 3;
			smallVectors.at(randInd).push_back(grassGrid.at(i));
		}
		//mid1
		randNum = rand();
		randInd = randNum % 3;
		randProc = ((double)randNum / RAND_MAX);

		mid1Vectors.at(randInd).push_back(grassGrid.at(i));

		if (randProc > doubleProc)
		{
			randInd2 = (rand() % 2) + 1;
			randInd = (randInd + randInd2) % 3;
			mid1Vectors.at(randInd).push_back(grassGrid.at(i));
		}
		//mid2
		randNum = rand();
		randInd = randNum % 3;
		randProc = ((double)randNum / RAND_MAX);

		mid2Vectors.at(randInd).push_back(grassGrid.at(i));

		if (randProc > doubleProc)
		{
			randInd2 = (rand() % 2) + 1;
			randInd = (randInd + randInd2) % 3;
			mid2Vectors.at(randInd).push_back(grassGrid.at(i));
		}
		//big
		randNum = rand();
		randInd = randNum % 3;
		randProc = ((double)randNum / RAND_MAX);

		bigVectors.at(randInd).push_back(grassGrid.at(i));

		if (randProc > doubleProc)
		{
			randInd2 = (rand() % 2) + 1;
			randInd = (randInd + randInd2) % 3;
			bigVectors.at(randInd).push_back(grassGrid.at(i));
		}
	}
	for (i = 0; i < 3; i++)
	{
		decorVertices.push_back(std::make_pair(&grassTextureSmall->at(i), createTileVertexArray(smallVectors.at(i))));
		decorVertices.push_back(std::make_pair(&grassTextureMid1->at(i), createTileVertexArray(mid1Vectors.at(i))));
		decorVertices.push_back(std::make_pair(&grassTextureMid2->at(i), createTileVertexArray(mid2Vectors.at(i))));
		decorVertices.push_back(std::make_pair(&grassTextureBig->at(i), createTileVertexArray(bigVectors.at(i))));
	}
	/*UTIL::ScreenCoord pos = UTIL::mapCoordToScreenCoord(coord);
	sf::IntRect textRect = sf::IntRect(0, 0, TILE_W, TILE_H);
	sf::Sprite sprite;
	double randProc;
	int randNum;
	int randInd;
	int randInd2;
	sprite.setPosition(pos.x, pos.y);

	randNum = rand();
	randInd = randNum % 3;
	randProc = ((double)randNum / RAND_MAX);
	//sprite.setTexture(grassTextureSmall->at(randInd));
	//tileSprites.at(tileIndex).push_back(sprite);
	drawBucket->addDecorVertices(&grassTextureSmall->at(randInd), pos, textRect);
	if (randProc > 0.8)
	{
		randInd2 = rand() % 2;
		randInd = (randInd + randInd2) % 3;
		//sprite.setTexture(grassTextureSmall->at(randInd));
		//tileSprites.at(tileIndex).push_back(sprite);
		drawBucket->addDecorVertices(&grassTextureSmall->at(randInd), pos, textRect);
	}

	randNum = rand();
	randInd = randNum % 3;
	randProc = ((double)randNum / RAND_MAX);
	//sprite.setTexture(grassTextureMid1->at(randInd));
	//tileSprites.at(tileIndex).push_back(sprite);
	drawBucket->addDecorVertices(&grassTextureMid1->at(randInd), pos, textRect);
	if (randProc > 0.8)
	{
		randInd2 = rand() % 2;
		randInd = (randInd + randInd2) % 3;
		//sprite.setTexture(grassTextureMid1->at(randInd));
		//tileSprites.at(tileIndex).push_back(sprite);
		drawBucket->addDecorVertices(&grassTextureMid1->at(randInd), pos, textRect);
	}

	randNum = rand();
	randInd = randNum % 3;
	randProc = ((double)randNum / RAND_MAX);
	//sprite.setTexture(grassTextureMid2->at(randInd));
	//tileSprites.at(tileIndex).push_back(sprite);
	drawBucket->addDecorVertices(&grassTextureMid2->at(randInd), pos, textRect);
	if (randProc > 0.8)
	{
		randInd2 = rand() % 2;
		randInd = (randInd + randInd2) % 3;
		//sprite.setTexture(grassTextureMid2->at(randInd));
		//tileSprites.at(tileIndex).push_back(sprite);
		drawBucket->addDecorVertices(&grassTextureMid2->at(randInd), pos, textRect);
	}

	randNum = rand();
	randInd = randNum % 3;
	randProc = ((double)randNum / RAND_MAX);
	//sprite.setTexture(grassTextureBig->at(randInd));
	//tileSprites.at(tileIndex).push_back(sprite);
	drawBucket->addDecorVertices(&grassTextureBig->at(randInd), pos, textRect);
	if (randProc > 0.8)
	{
		randInd2 = rand() % 2;
		randInd = (randInd + randInd2) % 3;
		//sprite.setTexture(grassTextureBig->at(randInd));
		//tileSprites.at(tileIndex).push_back(sprite);
		drawBucket->addDecorVertices(&grassTextureBig->at(randInd), pos, textRect);
	}*/
}

std::vector<AnimationSignal> MapAnimation2::drawMap(MapManagerVisualEventData mapData)
{
	std::vector<AnimationSignal> returnSignals = {};

	drawTiles();

	if (mapData.isMenuActive())
	{
		menuAnimation.draw(mapData.getActiveMenu());
	}

	return returnSignals;
}

void MapAnimation2::draw()
{
	drawTiles();
	riverAnim.draw();
	//drawSprites();
}

void MapAnimation2::drawTiles()
{
	/*unsigned int i, j;
	for (i = 0; i < tileSprites.size(); i++)
	{
		for (j = 0; j < tileSprites.at(i).size(); j++)
		{
			drawBucket->addToBucket(tileSprites.at(i).at(j));
			//window->draw(tileSprites.at(i).at(j));
		}
	}*/
	unsigned int i;
	for (i = 0; i < tileVertices.size(); i++)
	{
		drawBucket->addToBucket(tileVertices.at(i).second, tileVertices.at(i).first, 0);
	}
	for (i = 0; i < decorVertices.size(); i++)
	{
		drawBucket->addToBucket(decorVertices.at(i).second, decorVertices.at(i).first, 1);
	}
}

/*void MapAnimation2::drawSprites()
{
	unsigned int i;
	for (i = 0; i < drawBucket.size(); i++)
	{
		drawBucket.at(i).move(mapOffsetX, mapOffsetY);
		window->draw(drawBucket.at(i));
	}
	drawBucket.clear();
}*/