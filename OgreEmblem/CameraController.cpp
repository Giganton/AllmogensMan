#include "CameraController.h"
#include "Spline.h"


CameraController::CameraController(sf::RenderWindow* ww)
{
	window = ww;
	//cameraTarget = UTIL::ScreenCoord(0, 0);
	panner = CameraPanner(window, TILE_W, TILE_H);
}

CameraController::CameraController(sf::RenderWindow* ww, UTIL::ScreenCoord offset) : CameraController(ww)
{
	cameraOffset = offset;
	cameraTarget = offset;
}

void CameraController::addToBucket(sf::Sprite sprite)
{
	addToBucket(sprite, 5);
}

void CameraController::addToBucket(sf::Sprite sprite, int layer)
{
	std::map < int, std::queue<sf::Sprite>> ::iterator it = spriteBucket.find(layer);
	if (it == spriteBucket.end())
	{
		std::queue<sf::Sprite> temp;
		temp.push(sprite);
		spriteBucket.insert({ layer, temp });
	}
	else
	{
		spriteBucket.find(layer)->second.push(sprite);
	}
}

void CameraController::addToBucket(sf::VertexArray vArray, sf::Texture* txt, int layer)
{
	std::map<int, std::map<sf::Texture*, std::queue<sf::VertexArray>>>::iterator it = vertexBucket.find(layer);
	if (it == vertexBucket.end())
	{

		std::map<sf::Texture*, std::queue<sf::VertexArray>> temp;
		std::queue<sf::VertexArray> temp2;
		temp2.push(vArray);
		temp.insert({ txt , temp2 });
		vertexBucket.insert({ layer, temp });
	}
	else
	{
		std::map<sf::Texture*, std::queue<sf::VertexArray> >::iterator it = vertexBucket.find(layer)->second.find(txt);
		if (it == vertexBucket.find(layer)->second.end())
		{
			std::queue<sf::VertexArray> temp;
			temp.push(vArray);
			vertexBucket.find(layer)->second.insert({ txt , temp });
		}
		else
		{
			vertexBucket.find(layer)->second.find(txt)->second.push(vArray);
		}
	}
}

void CameraController::drawGridVertices()
{

	sf::VertexArray quads = sf::VertexArray(sf::Quads, tilePositions.size() * 4);
	int i;
	for (i = 0; i < tilePositions.size(); i++)
	{
		UTIL::ScreenCoord mapPos = tilePositions.at(i);
		quads[i * 4].position = sf::Vector2f(mapPos.x + cameraOffset.x, mapPos.y + cameraOffset.y);
		quads[i * 4 + 1].position = sf::Vector2f(mapPos.x + cameraOffset.x + TILE_W, mapPos.y + cameraOffset.y);
		quads[i * 4 + 2].position = sf::Vector2f(mapPos.x + cameraOffset.x + TILE_W, mapPos.y + cameraOffset.y + TILE_H);
		quads[i * 4 + 3].position = sf::Vector2f(mapPos.x + cameraOffset.x, mapPos.y + cameraOffset.y + TILE_H);

		quads[i * 4].texCoords = sf::Vector2f(0, 0);
		quads[i * 4 + 1].texCoords = sf::Vector2f(TILE_W, 0);
		quads[i * 4 + 2].texCoords = sf::Vector2f(TILE_W, TILE_H);
		quads[i * 4 + 3].texCoords = sf::Vector2f(0, TILE_H);
	}

	window->draw(quads, gridTexture);
}

void CameraController::drawTileVertices()
{
	std::map<sf::Texture*, std::vector<std::pair<sf::IntRect, sf::IntRect>> >::iterator it;

	for (it = tileVertexMap.begin(); it != tileVertexMap.end(); it++)
	{
		std::vector<std::pair<sf::IntRect, sf::IntRect>> vector = it->second;
		sf::VertexArray quads = sf::VertexArray(sf::Quads, vector.size() * 4);
		int i;

		for (i = 0; i < vector.size(); i++)
		{
			sf::IntRect position = sf::IntRect(vector.at(i).first.left + cameraOffset.x, vector.at(i).first.top + cameraOffset.y, vector.at(i).first.width, vector.at(i).first.height);
			sf::IntRect texture = vector.at(i).second;
			quads[i * 4].position = sf::Vector2f(position.left, position.top);
			quads[i * 4 + 1].position = sf::Vector2f(position.left + position.width, position.top);
			quads[i * 4 + 2].position = sf::Vector2f(position.left + position.width, position.top + position.height);
			quads[i * 4 + 3].position = sf::Vector2f(position.left, position.top + position.height);

			quads[i * 4].texCoords = sf::Vector2f(texture.left, texture.top);
			quads[i * 4 + 1].texCoords = sf::Vector2f(texture.left + texture.width, texture.top);
			quads[i * 4 + 2].texCoords = sf::Vector2f(texture.left + texture.width, texture.top + texture.height);
			quads[i * 4 + 3].texCoords = sf::Vector2f(texture.left, texture.top + texture.height);
		}
	}
}

void CameraController::drawDecorVertices()
{

	std::map<sf::Texture*, std::vector<std::pair<sf::IntRect, sf::IntRect>> >::iterator it;

	for (it = decorVertexMap.begin(); it != decorVertexMap.end(); it++)
	{
		std::vector<std::pair<sf::IntRect, sf::IntRect>> vector = it->second;
		sf::VertexArray quads = sf::VertexArray(sf::Quads, vector.size() * 4);
		int i;

		for (i = 0; i < vector.size(); i++)
		{
			sf::IntRect position = sf::IntRect(vector.at(i).first.left + cameraOffset.x, vector.at(i).first.top + cameraOffset.y, vector.at(i).first.width, vector.at(i).first.height);
			sf::IntRect texture = vector.at(i).second;
			quads[i * 4].position = sf::Vector2f(position.left, position.top);
			quads[i * 4 + 1].position = sf::Vector2f(position.left + position.width, position.top);
			quads[i * 4 + 2].position = sf::Vector2f(position.left + position.width, position.top + position.height);
			quads[i * 4 + 3].position = sf::Vector2f(position.left, position.top + position.height);

			quads[i * 4].texCoords = sf::Vector2f(texture.left, texture.top);
			quads[i * 4 + 1].texCoords = sf::Vector2f(texture.left + texture.width, texture.top);
			quads[i * 4 + 2].texCoords = sf::Vector2f(texture.left + texture.width, texture.top + texture.height);
			quads[i * 4 + 3].texCoords = sf::Vector2f(texture.left, texture.top + texture.height);
			/*quads[i*4].color = sf::Color::Red;
			quads[i*4+1].color = sf::Color::Green;
			quads[i*4+2].color = sf::Color::Green;
			quads[i*4+3].color = sf::Color::Red;*/
		}
		window->draw(quads, it->first);
	}
}

void CameraController::addTileVertices(sf::Texture* texture, UTIL::ScreenCoord position, sf::IntRect textRectangle)
{
	sf::IntRect posRect = sf::IntRect(position.x, position.y, textRectangle.width, textRectangle.height);
	std::pair<sf::IntRect, sf::IntRect> addedPair = std::make_pair(posRect, textRectangle);
	std::map<sf::Texture*, std::vector<std::pair<sf::IntRect, sf::IntRect> >>::iterator it = tileVertexMap.find(texture);
	if (it == tileVertexMap.end())
	{
		std::vector<std::pair< sf::IntRect, sf::IntRect>> temp;
		temp.push_back(addedPair);
		tileVertexMap.insert({ texture , temp });
	}
	else
	{
		tileVertexMap.find(texture)->second.push_back(addedPair);
	}
}

void CameraController::addGridVertices(UTIL::ScreenCoord position)
{
	tilePositions.push_back(position);
}

void CameraController::addDecorVertices(sf::Texture* texture, UTIL::ScreenCoord position, sf::IntRect textRectangle)
{
	sf::IntRect posRect = sf::IntRect(position.x, position.y, textRectangle.width, textRectangle.height);
	std::pair<sf::IntRect, sf::IntRect> addedPair = std::make_pair(posRect, textRectangle);
	std::map<sf::Texture*, std::vector<std::pair<sf::IntRect, sf::IntRect> >>::iterator it = decorVertexMap.find(texture);
	if (it == decorVertexMap.end())
	{
		std::vector<std::pair< sf::IntRect, sf::IntRect>> temp;
		temp.push_back(addedPair);
		decorVertexMap.insert({ texture , temp });
	}
	else
	{
		decorVertexMap.find(texture)->second.push_back(addedPair);
	}
}
/*
UTIL::ScreenCoord CameraController::findWidthVecForRiverEndPoints(UTIL::ScreenCoord dirVector)
{
	if (UTIL::areVectorsParallel(dirVector, UTIL::ScreenCoord(TILE_W, TILE_H), 0.001))
	{
		return dirVector.mirrorX()/dirVector.abs();
	}
	else if (UTIL::areVectorsParallel(dirVector, UTIL::ScreenCoord(TILE_W, -TILE_H), 0.001))
	{
		return dirVector.mirrorY()/dirVector.abs();
	}
	else
	{
		throw new std::exception();
		return UTIL::ScreenCoord();
	}
}

void CameraController::drawRivers2()
{
	unsigned int i, j;
	unsigned int curveDisc = 40;
	CubicSpline spline;
	std::vector<CubicPolynomial> xPoly;
	std::vector<CubicPolynomial> yPoly;
	std::vector<float> h;

	for (i = 0; i < rivers.size(); i++)
	{
		std::vector<UTIL::ScreenCoord> riverPoints;
		std::vector<std::pair<UTIL::ScreenCoord, UTIL::ScreenCoord>> river = rivers.at(i);
		riverPoints.push_back(river.at(0).first);
		for (j = 0; j < river.size(); j++)
		{
			riverPoints.push_back(river.at(j).second);
		}
		//sf::VertexArray riverShape = sf::VertexArray(sf::TriangleStrip, riverPoints.size() * 2);
		sf::VertexArray riverShape = sf::VertexArray(sf::TriangleStrip, 2 * ((riverPoints.size() - 1) * curveDisc + 1));
		sf::VertexArray riverEdgeShape = sf::VertexArray(sf::TriangleStrip, 2 * ((riverPoints.size() - 1) * curveDisc + 1));
		sf::VertexArray skyMirror = sf::VertexArray(sf::TriangleStrip, 2 * ((riverPoints.size() - 1) * curveDisc + 1));

		spline = CubicSpline(riverPoints);
		xPoly = spline.getPolynomials().first;
		yPoly = spline.getPolynomials().second;
		h = spline.getStepVector();

		UTIL::ScreenCoord widthVector;
		float width = 15;
		UTIL::ScreenCoord edge1;
		UTIL::ScreenCoord edge2;
		std::vector<UTIL::ScreenCoord> curveCoords;

		for (j = 0; j < riverPoints.size() - 1; j++)
		{
			CubicPolynomial xCurve = spline.getPolynomials().first.at(j);
			CubicPolynomial yCurve = spline.getPolynomials().second.at(j);

			if (j == 0)
			{
				sf::Vector2u riverTextSize = riverTexture->getSize();
				sf::Vector2u skyTextSize = skyTexture->getSize();
				widthVector = findWidthVecForRiverEndPoints(riverPoints.at(1) - riverPoints.at(0));
				sf::Vector2f pos2 = sf::Vector2f(riverPoints.at(0).x + cameraOffset.x, riverPoints.at(0).y + cameraOffset.y + width);
				sf::Vector2f pos1 = sf::Vector2f(riverPoints.at(0).x + cameraOffset.x, riverPoints.at(0).y + cameraOffset.y - width);
				riverShape[0].position = pos1;
				riverShape[1].position = pos2;
				riverEdgeShape[0].position = pos1;
				riverEdgeShape[1].position = pos2;
				skyMirror[0].position = pos1;
				skyMirror[1].position = pos2;
				riverShape[0].texCoords = sf::Vector2f(riverTextSize.x / 2 + width, 0);
				riverShape[1].texCoords = sf::Vector2f(riverTextSize.x / 2 - width, 0);
				riverEdgeShape[0].texCoords = sf::Vector2f(0, 0);
				riverEdgeShape[1].texCoords = sf::Vector2f(0, width*2);
				skyMirror[0].texCoords = sf::Vector2f((int)(pos1.x - cameraOffset.x*3/4) % skyTextSize.x, (int)(pos1.y - cameraOffset.y*3/4) % skyTextSize.y);
				skyMirror[1].texCoords = sf::Vector2f((int)(pos2.x - cameraOffset.x*3/4) % skyTextSize.x, (int)(pos2.y - cameraOffset.y*3/4) % skyTextSize.y);

				riverShape[0].color = sf::Color(100, 100, 100, 255);
				riverShape[1].color = sf::Color(100, 100, 100, 255);
				skyMirror[0].color = sf::Color(255, 255, 255, 145);
				skyMirror[1].color = sf::Color(255, 255, 255, 145);
				//riverShape[0].color = sf::Color::Green;
				//riverShape[1].color = sf::Color::Blue;
				curveCoords.push_back(riverPoints.at(0));
			}

			float h1 = h.at(j);
			float h2 = h.at(j + 1);
			float d = h2 - h1;
			unsigned int k;
			for (k = 1; k < (curveDisc + 1); k++)
			{
				float hk = h1 + k * d / curveDisc;
				float x = xCurve.evaluate(hk - h1);
				float y = yCurve.evaluate(hk - h1); 

				curveCoords.push_back(UTIL::ScreenCoord(x, y));
			}

		}
		unsigned int k;
		unsigned int travelLength = 0;
		for (k = 1; k < curveCoords.size(); k++)
		{
			//int index = j * 2 * curveDisc + 2 * (k - 1) + 2;
			if (k == curveCoords.size() - 1)
			{
				widthVector = normalize(UTIL::turnByAngle((curveCoords.at(k) - curveCoords.at(k - 1)), atan(1) * 2));
			}
			else
			{
				widthVector = normalize(UTIL::turnByAngle((curveCoords.at(k + 1) - curveCoords.at(k - 1)), atan(1) * 2));
			}
			srand(curveCoords.at(k).x + curveCoords.at(k).y);
			int offset1 = rand() % 16 - 8;
			int offset2 = rand() % 16 - 8;
			offset1 = 0;
			sf::Vector2f pos1 = sf::Vector2f((curveCoords.at(k) + cameraOffset + widthVector * (offset1 + width)).x, (curveCoords.at(k) + cameraOffset + widthVector * (offset1 + width)).y);
			sf::Vector2f pos2 = sf::Vector2f((curveCoords.at(k) + cameraOffset + widthVector * (offset1 - width)).x, (curveCoords.at(k) + cameraOffset + widthVector * (offset1 - width)).y);
			riverShape[2 * k].position = pos1;
			riverShape[2 * k + 1].position = pos2;
			riverEdgeShape[2 * k].position = pos1;
			riverEdgeShape[2 * k + 1].position = pos2;
			skyMirror[2 * k].position = pos1;
			skyMirror[2 * k + 1].position = pos2;

			//riverShape[2*k].color = sf::Color::Green;//sf::Color(49, 46, 90);
			//riverShape[2*k + 1].color = sf::Color::Blue;//sf::Color(49, 46, 90);

			sf::Vector2u riverTextSize = riverTexture->getSize();
			sf::Vector2u riverEdgeTextSize = riverEdgeTexture->getSize();
			sf::Vector2u skyTextSize = skyTexture->getSize();
			travelLength = (unsigned int)(curveCoords.at(k) - curveCoords.at(k - 1)).abs() + travelLength;
			riverShape[2 * k].texCoords = sf::Vector2f(riverTextSize.x / 2 + width, travelLength % riverTextSize.y);
			riverShape[2 * k + 1].texCoords = sf::Vector2f(riverTextSize.x / 2 - width, travelLength % riverTextSize.y);

			sf::Vector2f topVec = sf::Vector2f(travelLength % riverEdgeTextSize.x, 0);
			sf::Vector2f botVec = sf::Vector2f(travelLength % riverEdgeTextSize.x, width * 2);
			if (pos1.y < pos2.y)
			{
				riverEdgeShape[2 * k].texCoords = topVec;
				riverEdgeShape[2 * k + 1].texCoords = botVec;
			}
			else
			{
				riverEdgeShape[2 * k].texCoords = botVec;
				riverEdgeShape[2 * k + 1].texCoords = topVec;
			}

			skyMirror[2 * k].texCoords = sf::Vector2f((int)(pos1.x - cameraOffset.x*3/4) % skyTextSize.x, (int)(pos1.y - cameraOffset.y*3/4) % skyTextSize.y);
			skyMirror[2 * k + 1].texCoords = sf::Vector2f((int)(pos2.x - cameraOffset.x*3/4) % skyTextSize.x, (int)(pos2.y - cameraOffset.y*3/4) % skyTextSize.y);

			riverShape[2 * k].color = sf::Color(100, 100, 100, 255);
			riverShape[2 * k + 1].color = sf::Color(100, 100, 100, 255);
			skyMirror[2 * k].color = sf::Color(255, 255, 255, 145);
			skyMirror[2 * k + 1].color = sf::Color(255, 255, 255, 145);
		}



		window->draw(riverShape, riverTexture);
		window->draw(skyMirror, skyTexture);
		window->draw(riverEdgeShape, riverEdgeTexture);
	}
}
*/
Direction CameraController::findNextRiverDir(UTIL::ScreenCoord startingPos, UTIL::ScreenCoord endingPos)
{
	UTIL::ScreenCoord normVec = (endingPos - startingPos) / (endingPos - startingPos).abs();
	if (normVec == UTIL::upVec())
	{
		return Direction::up;
	}
	else if (normVec == UTIL::rightVec())
	{
		return Direction::right;
	}
	else if (normVec == UTIL::downVec())
	{
		return Direction::down;
	}
	else if (normVec == UTIL::leftVec())
	{
		return Direction::left;
	}
	else
	{
		throw new std::exception();
		return Direction::up;
	}
}

void CameraController::drawRivers()
{
	unsigned int i, j;

	int strips = 0;
	std::vector<sf::VertexArray> riverVertexArrays;

	for (i = 0; i < rivers.size(); i++)
	{
		std::vector<std::pair<UTIL::ScreenCoord, UTIL::ScreenCoord>> river = rivers.at(i);
		sf::VertexArray riverShape = sf::VertexArray(sf::TriangleStrip, river.size() * 4);
		UTIL::ScreenCoord edge1;
		UTIL::ScreenCoord edge2;
		UTIL::ScreenCoord lastEdge;
		for (j = 0; j < river.size(); j++)
		{
			std::pair<UTIL::ScreenCoord, UTIL::ScreenCoord> currentStretch = river.at(j);
			edge1 = currentStretch.first;
			edge2 = currentStretch.second;
			UTIL::ScreenCoord widthVector;
			if (edge1.y > edge2.y)
			{
				widthVector = ((edge2 - edge1).mirrorX() / (edge2 - edge1).abs());
			}
			else
			{
				widthVector = ((edge2 - edge1).mirrorY() / (edge2 - edge1).abs());
			}
			float width = 15;

			riverShape[j * 4].position = sf::Vector2f((edge1 + cameraOffset + widthVector * width).x, (edge1 + cameraOffset + widthVector * width).y);
			riverShape[j * 4 + 1].position = sf::Vector2f((edge1 + cameraOffset - widthVector * width).x, (edge1 + cameraOffset - widthVector * width).y);
			riverShape[j * 4 + 2].position = sf::Vector2f((edge2 + cameraOffset + widthVector * width).x, (edge2 + cameraOffset + widthVector * width).y);
			riverShape[j * 4 + 3].position = sf::Vector2f((edge2 + cameraOffset - widthVector * width).x, (edge2 + cameraOffset - widthVector * width).y);

			riverShape[j * 4].color = sf::Color(49, 46, 90);
			riverShape[j * 4 + 1].color = sf::Color(49, 46, 90);
			riverShape[j * 4 + 2].color = sf::Color(49, 46, 90);
			riverShape[j * 4 + 3].color = sf::Color(49, 46, 90);
			/*
			riverShape[j * 4].color = sf::Color::Green;
			riverShape[j * 4 + 1].color = sf::Color::Blue;
			riverShape[j * 4 + 2].color = sf::Color::Red;
			riverShape[j * 4 + 3].color = sf::Color::Yellow;*/

			lastEdge = edge2;
		}
		riverVertexArrays.push_back(riverShape);


		sf::VertexArray riverShape2 = sf::VertexArray(sf::TriangleStrip, 8);
		riverShape2[0].position = sf::Vector2f(30, 30);
		riverShape2[1].position = sf::Vector2f(10, 200);
		riverShape2[2].position = sf::Vector2f(200, 60);
		riverShape2[3].position = sf::Vector2f(200, 250);
		riverShape2[4].position = sf::Vector2f(430, 30);
		riverShape2[5].position = sf::Vector2f(10, 100);
		riverShape2[6].position = sf::Vector2f(600, 60);
		riverShape2[7].position = sf::Vector2f(600, 250);

		riverShape2[0].color = sf::Color::Blue;
		riverShape2[1].color = sf::Color::Blue;
		riverShape2[2].color = sf::Color::Blue;
		riverShape2[3].color = sf::Color::Blue;
		riverShape2[4].color = sf::Color::Blue;
		riverShape2[5].color = sf::Color::Green;
		riverShape2[6].color = sf::Color::Blue;
		riverShape2[7].color = sf::Color::Blue;

		window->draw(riverShape);
	}
}

void CameraController::draw()
{
	updateCameraMovement();
	drawBuckets();
	//drawTileVertices();
	//drawDecorVertices();
	//drawRivers2();
	drawGridVertices();
}

void CameraController::drawBuckets()
{
	std::vector<int> spriteLayers;
	std::vector<int> vertexLayers;
	for (std::map < int, std::queue<sf::Sprite>>::iterator it = spriteBucket.begin(); it != spriteBucket.end(); ++it)
	{
		spriteLayers.push_back(it->first);
	}
	for (std::map<int, std::map<sf::Texture*, std::queue<sf::VertexArray>>>::iterator it = vertexBucket.begin(); it != vertexBucket.end(); ++it)
	{
		vertexLayers.push_back(it->first);
	}
	std::sort(spriteLayers.begin(), spriteLayers.end());
	std::sort(vertexLayers.begin(), vertexLayers.end());

	while (!vertexLayers.empty() || !spriteLayers.empty())
	{
		if (spriteLayers.empty())
		{
			drawVertexQueue(vertexBucket.find(vertexLayers.at(0))->second);
			vertexLayers.erase(vertexLayers.begin());
		}
		else if (vertexLayers.empty())
		{
			drawSpriteQueue(spriteBucket.find(spriteLayers.at(0))->second);
			spriteLayers.erase(spriteLayers.begin());
		}
		else
		{
			if (spriteLayers.at(0) < vertexLayers.at(0))
			{
				drawSpriteQueue(spriteBucket.find(spriteLayers.at(0))->second);
				spriteLayers.erase(spriteLayers.begin());
			}
			else
			{
				drawVertexQueue(vertexBucket.find(vertexLayers.at(0))->second);
				vertexLayers.erase(vertexLayers.begin());
			}
		}
	}
	vertexBucket.clear();
	spriteBucket.clear();
}

void CameraController::drawSpriteQueue(std::queue<sf::Sprite> sQueue)
{
	while (!sQueue.empty())
	{
		sf::Sprite temp = sQueue.front();
		temp.move(cameraOffset.x, cameraOffset.y);
		window->draw(temp);
		sQueue.pop();
	}
}

void CameraController::drawVertexQueue(std::map<sf::Texture*, std::queue<sf::VertexArray>> vQueue)
{
	std::map<sf::Texture*, std::queue<sf::VertexArray>>::iterator it;

	for (it = vQueue.begin(); it != vQueue.end(); it++)
	{
		while (!it->second.empty())
		{
			unsigned int i;
			sf::VertexArray temp = it->second.front();
			for (i = 0; i < temp.getVertexCount(); i++)
			{
				temp[i].position = temp[i].position + sf::Vector2f(cameraOffset.x, cameraOffset.y);
			}
			window->draw(temp, it->first);
			it->second.pop();
		}
	}
}

void CameraController::center(MapCoord centerOnCoord, bool blinkCamera)
{
	if (blinkCamera)
	{
		cameraOffset = panner.centerCamera(centerOnCoord);
		cameraTarget = cameraOffset;
	}
	else
	{
		cameraTarget = panner.centerCamera(centerOnCoord);

	}
}

void CameraController::pan(MapCoord panToCoord)
{
	UTIL::ScreenCoord sCoord = UTIL::mapCoordToScreenCoord(panToCoord.getX(), panToCoord.getY());
	cameraTarget = panner.panCamera(sCoord.x, sCoord.y);
}

void CameraController::pan(MapCoord fromCoord, MapCoord toCoord)
{
	UTIL::ScreenCoord dist = UTIL::ScreenCoord(fromCoord.getX(), fromCoord.getY()) - UTIL::ScreenCoord(toCoord.getX(), toCoord.getY());
	UTIL::ScreenCoord target = UTIL::mapCoordToScreenCoord(toCoord.getX(), toCoord.getY());
	if (!panner.coordIsWithinBounds(target) && dist.abs() == 1)
	{
		PanDirection dir = PanDirection::none;
		if (dist.x == 1)
		{
			dir = PanDirection::north;
		}
		else if (dist.x == -1)
		{
			dir = PanDirection::south;
		}
		else if (dist.y == 1)
		{
			dir = PanDirection::east;
		}
		else if (dist.y == -1)
		{
			dir = PanDirection::west;
		}
		else
		{
			throw new std::exception();
		}
		cameraTarget = panner.panCamera(dir);
	}
	else
	{
		pan(toCoord);
	}
}

void CameraController::updateCameraMovement()
{
	if (startTime == 0)
	{
		startTime = std::clock();
	}
	else
	{
		std::clock_t startTime = std::clock();
		double timePassed = ((double)startTime - (double)startTime) / (double)CLOCKS_PER_SEC;
		startTime = startTime;

		UTIL::ScreenCoord fullPath = (cameraTarget - cameraOffset);
		if (fullPath.abs() > panningMaxSpeed* (float)timePassed)
		{
			panningSpeed = panningSpeed + panningAccel;
			if (panningSpeed > panningMaxSpeed)
			{
				panningSpeed = panningMaxSpeed;
			}
			UTIL::ScreenCoord direction = fullPath / fullPath.abs();
			UTIL::ScreenCoord newPos = cameraOffset + direction * panningSpeed;
			cameraOffset = cameraOffset + direction * panningSpeed*(float)timePassed;
		}
		else
		{
			cameraOffset = cameraTarget;
			panningSpeed = 0;
		}
	}
}