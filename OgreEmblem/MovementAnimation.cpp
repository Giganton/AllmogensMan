#include "MovementAnimation.h"
#include "SquadRepresentation.h"
#include "CameraController.h"

MovementAnimation::MovementAnimation(std::map < ProfessionTag, sf::Texture>* sqdTextureMap, SquadRepresentation mvSquad, std::vector<MapCoord> mList, float tWidth, float tHeight, CameraController* dBucket)
{
	squadTextureMap = sqdTextureMap;

	movementList = mList;
	movingSquad = mvSquad;
	drawBucket = dBucket;

	tileWidth = tWidth;
	tileHeight = tHeight;

	active = true;

	currIndex = 0;

	if (mvSquad.frontRowUnits.size())
	{
		currentPos = mvSquad.frontRowUnits.at(0).position;
	}
	else if (mvSquad.backRowUnits.size())
	{
		currentPos = mvSquad.backRowUnits.at(0).position;
	}
	else
	{
		throw new std::exception();
	}
	
	unitSpriteSize = mvSquad.squadSpriteSize;
	spriteAnim = SpriteAnimator(squadSpriteSize, spriteAnimStepTime, nrOfSpriteAnimSteps);
}

bool MovementAnimation::progressAction()
{
	if (startTime == 0)
	{
		startTime = std::clock();
		animationFinished = false;
	}
	else
	{
		MapCoord destination = movementList.at(currIndex + 1);

		//float destX = xCoordToScreen(destination.getX());
		//float destY = yCoordToScreen(destination.getY());
		UTIL::ScreenCoord squadOffset = UTIL::ScreenCoord(TILE_W / 2 - unitSpriteSize.x / 2, TILE_H / 2 - unitSpriteSize.y / 2);
		UTIL::ScreenCoord screenDest = UTIL::mapCoordToScreenCoord(destination.getX(), destination.getY()) + squadOffset;

		UTIL::ScreenCoord dist = (/*screenDest - */currentPos);
		float distX = dist.x;
		float distY = dist.y;
		float movedDist;
		UTIL::ScreenCoord moveVector;

		std::clock_t startTime = std::clock();
		double timePassed = ((double)startTime - (double)startTime) / (double)CLOCKS_PER_SEC;
		startTime = startTime;

		bool tileDone = true;

		if (dist.abs() > moveSpeed * (float)timePassed)
		{
			moveVector = dist / dist.abs() * moveSpeed * (float)timePassed;
			currentPos = currentPos + moveVector;
		}
		else
		{
			currIndex = currIndex + 1;
			if (currIndex >= movementList.size() - 1)
			{
				animationFinished = true;
				startTime = 0;
			}
		}
	}
	movingSquad.frontRowUnits.at(0).position = UTIL::ScreenCoord(currentPos.x, currentPos.y);
	
	return animationFinished;
}

void MovementAnimation::initializeMovement()
{
	//hitta utgångspunkten i startrutan
	UTIL::ScreenCoord midPoint = getEdgeBetweenCoords(movementList.at(0), movementList.at(1));

	int i;
	std::vector<float> frontLineTimes = { 0 , 0 , 0 };
	std::vector<float> backLineTimes = { 0 , 0 , 0 };
	float bufferSize = 55;
	float cumulTime = 0;
	float prevPathLength = 0; 
	float pathLength;
	float buffer;
	float time;

	//ge alla units en vänteklocka
	for (i = 0; i < movingSquad.frontRowUnits.size(); i++)
	{
		UTIL::ScreenCoord mapPos = movingSquad.frontRowUnits.at(i).position;
		pathLength = (midPoint - mapPos).abs();
		if (i > 0)
		{
			buffer = bufferSize + (prevPathLength - pathLength);

			time = buffer / moveSpeed + cumulTime;
			cumulTime = time;
		}
		else
		{
			time = 0;
		}
		CaravanUnit cUnit = CaravanUnit(movingSquad.frontRowUnits.at(i), movementList.at(0), midPoint, time);
		prevPathLength = pathLength;
		caravan.push_back(cUnit);
	}
	for (i = 0; i < movingSquad.backRowUnits.size(); i++)
	{
		UTIL::ScreenCoord mapPos = movingSquad.backRowUnits.at(i).position;
		pathLength = (midPoint - mapPos).abs();
		buffer = bufferSize + (prevPathLength - pathLength);

		time = buffer / moveSpeed + cumulTime;
		cumulTime = time;
		CaravanUnit cUnit = CaravanUnit(movingSquad.backRowUnits.at(i), movementList.at(0), midPoint, time);
		prevPathLength = pathLength;
		caravan.push_back(cUnit);
	}
}

UTIL::ScreenCoord MovementAnimation::getEdgeBetweenCoords(MapCoord pos1, MapCoord pos2)
{
	UTIL::ScreenCoord start = UTIL::mapCoordToScreenCoordCenter(pos1) - squadSpriteSize / 2;
	UTIL::ScreenCoord next = UTIL::mapCoordToScreenCoordCenter(pos2) - squadSpriteSize / 2;
	UTIL::ScreenCoord fullDist = next - start;
	return (start + (fullDist / 2));
}

bool MovementAnimation::runAnimation2()
{
	if (!initialized)
	{
		initializeMovement();
		animationClock.restart();
		initialized = true;
		animationFinished = false;
	}
	else
	{
		int i;
		float timePassed = animationClock.getElapsedTime().asSeconds();
		animationClock.restart();
		for (i = 0; i < caravan.size(); i++)
		{
			if (!caravan.at(i).moveDone)
			{
				//vänta tills det är dags att börja gå
				if (caravan.at(i).timer - timePassed < 0)
				{
					float movementTime = timePassed - caravan.at(i).timer;
					caravan.at(i).timer = 0;

					UTIL::ScreenCoord dist = caravan.at(i).target - caravan.at(i).unit.position;
					UTIL::ScreenCoord moveVector = dist / dist.abs() * moveSpeed * timePassed;
					if (moveVector.abs() > dist.abs())
					{
						//målet nått, ge nytt mål.
						caravan.at(i).unit.position = caravan.at(i).target;

						caravan.at(i).currentIndex = caravan.at(i).currentIndex + 1;
						//om vi är mitt på vägen, gå till nästa ruta
						if (caravan.at(i).currentIndex < movementList.size() - 1)
						{
							caravan.at(i).target = UTIL::mapCoordToScreenCoordCenter(movementList.at(caravan.at(i).currentIndex)) - squadSpriteSize / 2;
						}
						//om vi nått sista rutan, gå till formation i sista rutan
						else if (caravan.at(i).currentIndex == movementList.size() - 1)
						{
							//caravan.at(i).target = getEdgeBetweenCoords(movementList.at(movementList.size() - 2), movementList.at(movementList.size() - 1));
							caravan.at(i).target = UTIL::mapCoordToScreenCoordCenter(movementList.at(movementList.size() - 1)) + caravan.at(i).startingOffset;
						}

						/*else if (caravan.at(i).currentIndex == movementList.size())
						{
							caravan.at(i).target = UTIL::mapCoordToScreenCoordCenter(movementList.at(movementList.size() - 1)) + caravan.at(i).startingOffset;
						}*/
						//???
						else
						{
							caravan.at(i).moveDone = true;
							if (i == caravan.size() - 1)
							{
								animationFinished = true;
							}
						}
					}
					else
					{
						caravan.at(i).unit.position = caravan.at(i).unit.position + moveVector;
					}
				}
				else
				{
					caravan.at(i).timer = caravan.at(i).timer - timePassed;
				}
			}
		}
		//börja gå, när en unit är framme: ge den som ny koordinat att gå mot centrum av nästa ruta i listan tills den landat i näst sista rutan, då

		//gå till kanten av sista rutan

		//gå till unitens plats på sista rutan

	}
	updateSquadRepPos(caravan);
	return animationFinished;
}

void MovementAnimation::updateSquadRepPos(std::vector<CaravanUnit> crvn)
{
	if (crvn.size() >= (TACTICAL_X + 1) * (TACTICAL_Y + 1))
	{
		throw new std::exception();
	}
	int i;
	for (i = 0; i < movingSquad.frontRowUnits.size(); i++)
	{
		movingSquad.frontRowUnits.at(i) = crvn.at(i).unit;
	}
	for (i = 0; i < movingSquad.backRowUnits.size(); i++)
	{
		movingSquad.backRowUnits.at(i) = crvn.at(i + movingSquad.frontRowUnits.size()).unit;
	}
}

void MovementAnimation::drawCaravan()
{
	int i;
	sf::IntRect textureRect = spriteAnim.getTextureRectangle();
	for (i = 0; i < caravan.size(); i++)
	{
		if (!caravan.at(i).unit.isDead)
		{
			sf::Sprite temp = sf::Sprite();
			temp.setTexture(squadTextureMap->find(caravan.at(i).unit.profession)->second);
			temp.setPosition(caravan.at(i).unit.position.x, caravan.at(i).unit.position.y);
			temp.setTextureRect(textureRect);

			drawBucket->addToBucket(temp);
		}
	}
}

void MovementAnimation::draw()
{
	active = !runAnimation2();
	drawCaravan();
}

CaravanUnit::CaravanUnit(UnitRepresentation unitRep, MapCoord startCoord, UTIL::ScreenCoord trget, float timeToWait)
{ 
	unit = unitRep; 
	target = trget; 
	timer = timeToWait; 
	startingOffset = unit.position - UTIL::mapCoordToScreenCoordCenter(startCoord);
}