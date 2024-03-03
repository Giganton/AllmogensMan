#include "MapAnimation.h"
#include "VisualStack.h"
#include "Terrain.h"
#include "AnimationSignal.h"
#include "GraphicsAssets.h"

MapAnimation::MapAnimation(MapPackage* mapPackage, BattleAnimation bAnim, VerticalMenuPackage* menuPack, sf::RenderWindow* ww)
{
	window = ww;
	terrainTextureMap = new std::map < std::string, sf::Texture>;
	//*terrainTextureMap = mapPackage->terrainTextureMap;
	squadTextureMap = new std::map < ProfessionTag, sf::Texture>;
	*squadTextureMap = mapPackage->squadTextureMap;

	cursorTexture = new sf::Texture;
	*cursorTexture = mapPackage->cursorTexture;
	cursorSprite.setTexture(*cursorTexture);

	dotTexture = new sf::Texture;
	*dotTexture = mapPackage->dotTexture;
	dotSprite.setTexture(*dotTexture);

	xTexture = new sf::Texture;
	*xTexture = mapPackage->xTexture;
	xSprite.setTexture(*xTexture);

	menuAnim = VerticalMenuAnimation(menuPack, UTIL::ScreenCoord(0, 0), ww);
	battleAnim = bAnim;

	std::map<std::string, sf::Texture>::iterator it;
	for (it = terrainTextureMap->begin(); it != terrainTextureMap->end(); it++)
	{
		sf::Sprite temp;
		temp.setTexture(it->second);
		spriteMap.insert({ it->first, temp });
	}

	panner = CameraPanner(ww, TILE_W, TILE_H);
}

MapAnimation::MapAnimation(const MapAnimation& cpMap)
{
	terrainTextureMap = new std::map < std::string, sf::Texture>;
	*terrainTextureMap = *(cpMap.terrainTextureMap);
	squadTextureMap = new std::map < ProfessionTag, sf::Texture>;
	*squadTextureMap = *(cpMap.squadTextureMap);
	
	std::map<std::string, sf::Texture>::iterator it;
	for (it = terrainTextureMap->begin(); it != terrainTextureMap->end(); it++)
	{
		sf::Sprite temp;
		temp.setTexture(it->second);
		spriteMap.insert({ it->first, temp });
	}

	window = cpMap.window;

	cursorTexture = new sf::Texture;
	*cursorTexture = *(cpMap.cursorTexture);
	cursorSprite.setTexture(*cursorTexture);
	cursorSprite.setPosition(cpMap.cursorSprite.getPosition());

	dotTexture = new sf::Texture;
	*dotTexture = *(cpMap.dotTexture);
	dotSprite.setTexture(*dotTexture);
	dotSprite.setPosition(cpMap.dotSprite.getPosition());

	xTexture = new sf::Texture;
	*xTexture = *(cpMap.xTexture);
	xSprite.setTexture(*xTexture);
	xSprite.setPosition(cpMap.xSprite.getPosition());

	mapOffsetX = cpMap.mapOffsetX;
	mapOffsetY = cpMap.mapOffsetY;
	panner = cpMap.panner;

	menuAnim = cpMap.menuAnim;
	battleAnim = cpMap.battleAnim;
	lastDrawnBattle = cpMap.lastDrawnBattle;

	animQueue = cpMap.animQueue;
	animationRunning = cpMap.animationRunning;
	battleAnimationRunning = cpMap.battleAnimationRunning;
	movementAnimationRunning = cpMap.movementAnimationRunning;
}

MapAnimation& MapAnimation::operator=(MapAnimation asMap)
{
	terrainTextureMap = new std::map < std::string, sf::Texture>;
	*terrainTextureMap = *(asMap.terrainTextureMap);
	squadTextureMap = new std::map < ProfessionTag, sf::Texture>;
	*squadTextureMap = *(asMap.squadTextureMap);
	
	std::map<std::string, sf::Texture>::iterator it;
	for (it = terrainTextureMap->begin(); it != terrainTextureMap->end(); it++)
	{
		sf::Sprite temp;
		temp.setTexture(it->second);
		spriteMap.insert({ it->first, temp });
	}

	window = asMap.window;

	cursorTexture = new sf::Texture;
	*cursorTexture = *(asMap.cursorTexture);
	cursorSprite.setTexture(*cursorTexture);
	cursorSprite.setPosition(asMap.cursorSprite.getPosition());

	dotTexture = new sf::Texture;
	*dotTexture = *(asMap.dotTexture);
	dotSprite.setTexture(*dotTexture);
	dotSprite.setPosition(asMap.dotSprite.getPosition());

	xTexture = new sf::Texture;
	*xTexture = *(asMap.xTexture);
	xSprite.setTexture(*xTexture);
	xSprite.setPosition(asMap.xSprite.getPosition());

	mapOffsetX = asMap.mapOffsetX;
	mapOffsetY = asMap.mapOffsetY;
	panner = asMap.panner;

	menuAnim = asMap.menuAnim;
	battleAnim = asMap.battleAnim;
	lastDrawnBattle = asMap.lastDrawnBattle;

	animQueue = asMap.animQueue;
	animationRunning = asMap.animationRunning;
	battleAnimationRunning = asMap.battleAnimationRunning;
	movementAnimationRunning = asMap.movementAnimationRunning;

	return *this;
}

std::vector<AnimationSignal> MapAnimation::drawMap(MapManagerVisualData mapManVis)
{
	std::vector<AnimationSignal> retVal = {};

	BattleMapVisualData mapData = mapManVis.getMapData();
	if (squadMovementMap.empty())
	{
		//float cursorScreenPosX = xCoordToScreen(mapData.getCursorPos().x);
		//float cursorScreenPosY = yCoordToScreen(mapData.getCursorPos().y);

		//panner.panCamera(cursorScreenPosX, cursorScreenPosY);
		UTIL::ScreenCoord offset = panner.getOffset();
		mapOffsetX = offset.x;
		mapOffsetY = offset.y;
	}

	drawGrid(mapData);

	if (mapManVis.isMoving())
	{
		mStageVisualData mvData = mapManVis.getOngoingMoveData();
		std::vector<MapCoord> moveList = mvData.getMoveList();

		drawDots(moveList);
		if (mvData.isDisconnected())
		{
			drawCross(moveList.at(moveList.size() - 1));
		}
	}
	if (!mapManVis.animQueue.isEmpty())
	{
		animQueue.addQueue(mapManVis.animQueue);
		std::list<mStageVisualData> moveList = mapManVis.animQueue.getMovementList();
		//lägg till alla köande flyttanimationer till kartan
		if (moveList.size() > 0)
		{
			while (moveList.size() > 0)
			{
				mStageVisualData currentData = moveList.front();
				moveList.pop_front();
				//std::pair<MovementAnimation, bool> temp(MovementAnimation(currentData.getMoveList(), TILE_W, TILE_H), false);
				retVal.push_back(AnimationSignal(mapManVis.getID(), SignalType::animationStarted, SignalSubType::Movement));
				//squadMovementMap.insert({ currentData.getSquadID(), temp });
			}
		}
		mapManVis.animQueue.clear();
	}
	
	if (!animationRunning && !animQueue.isEmpty())
	{
		AnimationType nextAnim = animQueue.pullLatestAnimationType();
		switch (nextAnim)
		{
		case AnimationType::battle:
			battleAnim.setup(animQueue.pullBattle());
			battleAnimationRunning = true;
			retVal.push_back(AnimationSignal(mapManVis.getID(), SignalType::animationStarted, SignalSubType::Battle));
			break;
		case AnimationType::movement:
			mStageVisualData mvData = animQueue.pullMovement();
			//add squad to movement animation map
			squadMovementMap.find(mvData.getSquadID())->second.second = true;
			movementAnimationRunning = true;
			//send signal to game that move animation has started
			//retVal.push_back(AnimationSignal(mapManVis.getID(), SignalType::animationStarted, SignalSubType::Movement));
			break;
		}
	}

	//std::vector<SquadData> sData = mapData.getSquadList(); 
	std::vector<AnimationSignal> squadSignals;// = drawSquads(sData, mapManVis.getCurrentTurnID(), mapManVis.getID());

	retVal.insert(retVal.end(), squadSignals.begin(), squadSignals.end());

	if (mapManVis.isCursorVisible())
	{
		//moveCursorSprite(mapData.getCursorPos().x, mapData.getCursorPos().y);
		drawBucket.push_back(cursorSprite);
		//drawOnMap(cursorSprite);
	}

	drawOnMap();

	if (mapManVis.isMenuActive())
	{
		menuAnim.draw(mapManVis.getActiveMenu());
	}
	if (battleAnimationRunning && battleAnim.progress())
	{
		battleAnimationRunning = false;
		retVal.push_back(AnimationSignal(mapManVis.getID(), SignalType::animationDone, SignalSubType::Battle));
		//lastDrawnBattle = mapManVis.getStageID();
	}

	animationRunning = battleAnimationRunning || movementAnimationRunning;

	return retVal;
}

void MapAnimation::panMap(float targetX, float targetY)
{
	if (targetX + 3 * TILE_W >= window->getSize().x - mapOffsetX)
	{
		mapOffsetX = mapOffsetX - TILE_W;
	}
	else if (targetX - 3 * TILE_W < -mapOffsetX)
	{
		mapOffsetX = mapOffsetX + TILE_W;
	}

	if (targetY + 3 * TILE_H >= window->getSize().y - mapOffsetY)
	{
		mapOffsetY = mapOffsetY - TILE_H;
	}
	else if (targetY - 3 * TILE_H < -mapOffsetY)
	{
		mapOffsetY = mapOffsetY + TILE_H;
	}
}
/*
void MapAnimation::drawOnMap(sf::Sprite sprite)
{
	sprite.move(mapOffsetX, mapOffsetY);
	window->draw(sprite);
}*/

void MapAnimation::drawOnMap()
{
	unsigned int i;
	for (i = 0; i < drawBucket.size(); i++)
	{
		drawBucket.at(i).move(mapOffsetX, mapOffsetY);
		window->draw(drawBucket.at(i));
	}
	drawBucket.clear();
}

void MapAnimation::drawGrid(BattleMapVisualData mapData)
{
	int i, j;
	std::vector<std::vector<Terrain>> grid;// = mapData.getGrid();

	for (i = 0; i < mapData.getMapWidth(); i++)
	{
		for (j = 0; j < mapData.getMapHeight(); j++)
		{
			Terrain terr = grid.at(i).at(j);
			if (terr.getType() == TerrainTypes::noTerrain)
			{

			}
			else
			{
				float posX = xCoordToScreen(i);
				float posY = yCoordToScreen(j);

				sf::Sprite sprite = spriteMap.find(terr.getName())->second;

				sprite.setPosition(posX, posY);
				drawBucket.push_back(sprite);
				//drawOnMap(sprite);
			}
		}
	}
}

std::vector<AnimationSignal> MapAnimation::drawSquads(std::vector<SquadData> sData, tagID activeTag, int signalAddress)
{
	std::map<long int, std::pair<MovementAnimation, bool>>::iterator findIterator;
	std::vector<AnimationSignal> retVal = {};

	while (!sData.empty())
	{
		SquadData temp = sData.at(sData.size() - 1);

		//std::string leadProf = temp.squad.getLeadProfName();
		//squadSprite.setTexture(squadTextureMap->find(leadProf)->second);

		//färglägg gänget med rätt lagfärg
		tagID squadTag = temp.squad.getFlagTag();
		switch (squadTag)
		{
		case tagID::player:
			squadSprite.setColor(sf::Color(255, 255, 255));
			break;
		case tagID::redEnemy:
			squadSprite.setColor(sf::Color(255, 0, 0));
			break;
		case tagID::greenEnemy:
			squadSprite.setColor(sf::Color(0, 255, 0));
			break;
		}
		long int currentID = temp.squad.getID();

		//see if current squad is currently doing a movement animation
		findIterator = squadMovementMap.find(currentID);

		if (findIterator == squadMovementMap.end())
		{
			//if squad is not in a movement animation, just draw it on the spot
			squadSprite.setPosition(xCoordToScreen(temp.mapPos.getX()), yCoordToScreen(temp.mapPos.getY()));
		}
		else
		{
			//om animationen har startat
			if (squadMovementMap.find(currentID)->second.second)
			{
				std::vector<MapCoord> drawList = squadMovementMap.find(currentID)->second.first.getMovementList();
				int drawnIndex = squadMovementMap.find(currentID)->second.first.getCurrentIndex();

				std::vector<MapCoord>::const_iterator first = drawList.begin() + drawnIndex + 1;
				std::vector<MapCoord>::const_iterator last = drawList.end();

				if (squadTag == tagID::player)
				{
					drawDots(std::vector<MapCoord>(first, last));
					drawCross(drawList.at(drawList.size() - 1));
				}

				if (squadMovementMap.find(currentID)->second.first.progressAction())
				{
					squadMovementMap.erase(currentID);
					movementAnimationRunning = false;
					retVal.push_back(AnimationSignal(signalAddress, SignalType::animationDone, SignalSubType::Movement));
				}
				else
				{
					panner.centerCameraIfOut(squadSprite, UTIL::ScreenCoord(squadSprite.getPosition().x, squadSprite.getPosition().y));
					UTIL::ScreenCoord offset = panner.getOffset();
					mapOffsetX = offset.x;
					mapOffsetY = offset.y;
				}
			}
			else
			{
				std::vector<MapCoord> drawList = squadMovementMap.find(currentID)->second.first.getMovementList();
				int xPos = drawList.at(0).getX();
				int yPos = drawList.at(0).getY();
				squadSprite.setPosition(xCoordToScreen(xPos), yCoordToScreen(yPos));
			}
			
		}
		sData.pop_back();
		
		drawBucket.push_back(squadSprite);
		//window->draw(squadSprite);
	}
	return retVal;
}

void MapAnimation::moveCursorSprite(int x, int y)
{
	cursorSprite.setPosition(xCoordToScreen(x), yCoordToScreen(y));
}

MapAnimation::~MapAnimation()
{
	delete terrainTextureMap;
	delete cursorTexture;
	delete squadTextureMap;
	delete dotTexture;
}

void MapAnimation::drawDots(std::vector<MapCoord> path)
{
	unsigned int i;
	int j;
	float tileOffsetX = TILE_W / 2;
	float tileOffsetY = TILE_H / 2;
	float dotOffsetX = float(-dotSprite.getTextureRect().width / 2);
	float dotOffsetY = float(-dotSprite.getTextureRect().height / 2);

	int dotsPerTile = 3;
	int dotRandMax = 3;

	//float startX = xCoordToScreen(moveList.at(0).getX()) + tileOffsetX;
	//float startY = yCoordToScreen(moveList.at(0).getY()) + tileOffsetY;

	float startX, startY, endX, endY;

	if (path.size() > 1)
	{
		for (i = 0; i < path.size() - 1; i++)
		{
			MapCoord start = path.at(i);
			MapCoord stop = path.at(i + 1);
			srand(start.getX() + start.getY());

			startX = xCoordToScreen(start.getX()) + tileOffsetX;
			startY = yCoordToScreen(start.getY()) + tileOffsetY;
			endX = xCoordToScreen(stop.getX()) + tileOffsetX;
			endY = yCoordToScreen(stop.getY()) + tileOffsetY;

			float distX = endX - startX;
			float distY = endY - startY;

			for (j = 0; j < dotsPerTile; j++)
			{
				float posX = startX;
				float posY = startY;

				if (abs(distX) > 0)
				{
					posX = startX + distX * j / dotsPerTile;
				}
				if (abs(distY) > 0)
				{
					posY = startY + distY * j / dotsPerTile;
				}

				posX = posX + (rand() % dotRandMax) + dotOffsetX;
				posY = posY + (rand() % dotRandMax) + dotOffsetY;

				dotSprite.setPosition(posX, posY);
				drawBucket.push_back(dotSprite);
				//drawOnMap(dotSprite);
			}
		}
	}

	srand(time(0));
}

void MapAnimation::drawCross(MapCoord mapPos)
{
	float xOffsetX = float(-xSprite.getTextureRect().width / 2);
	float xOffsetY = float(-xSprite.getTextureRect().height / 2);
	float tileOffsetX = TILE_W / 2;
	float tileOffsetY = TILE_H / 2;
	float xPos = xCoordToScreen(mapPos.getX()) + tileOffsetX + xOffsetX;
	float yPos = yCoordToScreen(mapPos.getY()) + tileOffsetY + xOffsetY;
	xSprite.setPosition(xPos, yPos);
	drawBucket.push_back(xSprite);
	//drawOnMap(xSprite);
}