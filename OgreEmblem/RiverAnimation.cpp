#include "RiverAnimation.h"
#include "CameraController.h"

RiverAnimation::RiverAnimation(sf::Texture* riverT, sf::Texture* edgeT, sf::Texture* skyT, CameraController* dBucket)
{
	riverTexture = riverT;
	skyTexture = skyT;
	edgeTexture = edgeT;

	drawBucket = dBucket;
	curveDisc = 12;
}

void RiverAnimation::initRivers(std::vector<std::vector<std::pair<UTIL::ScreenCoord, UTIL::ScreenCoord>>> riversToDraw)
{
	unsigned int i;
	rivers.clear();
	initialized = true;
	for (i = 0; i < riversToDraw.size(); i++)
	{
		std::pair<RiverRepresentation, CubicSpline > temp = createRiverRepresentation(riversToDraw.at(i));
		splines.push_back(temp.second);
		rivers.push_back(temp.first);
	}
}

void RiverAnimation::draw()
{
	unsigned int i;
	for (i = 0; i < rivers.size(); i++)
	{
		rivers.at(i) = updateRep(rivers.at(i));
		RiverRepresentation rep = rivers.at(i);
		drawBucket->addToBucket(rep.riverShape, riverTexture, 2);
		drawBucket->addToBucket(rep.skyMirror, skyTexture, 3);
		drawBucket->addToBucket(rep.riverEdgeRightShape, edgeTexture, 4);
		drawBucket->addToBucket(rep.riverEdgeLeftShape, edgeTexture, 4);
	}
}

RiverRepresentation RiverAnimation::updateRep(RiverRepresentation riverRep)
{
	riverRep.skyMirror = updateSkyTexture(riverRep.skyMirror);
	return riverRep;
}

sf::VertexArray RiverAnimation::updateSkyTexture(sf::VertexArray skyShape)
{
	unsigned int k;
	sf::Vector2u skyTextSize = skyTexture->getSize();
	UTIL::ScreenCoord cameraOffset = drawBucket->getOffset();
	for (k = 0; k < skyShape.getVertexCount() / 2; k++)
	{
		sf::Vector2f pos1 = skyShape[2 * k].position;
		sf::Vector2f pos2 = skyShape[2 * k + 1].position;
		skyShape[2 * k].texCoords = getSkyCoord(pos1);
		skyShape[2 * k + 1].texCoords = getSkyCoord(pos2);
	}
	return skyShape;
}

std::pair<RiverRepresentation, CubicSpline > RiverAnimation::createRiverRepresentation(std::vector<std::pair<UTIL::ScreenCoord, UTIL::ScreenCoord >> riverToDraw)
{
	std::vector<UTIL::ScreenCoord> riverPoints;
	riverPoints.push_back(riverToDraw.at(0).first);
	unsigned int i;

	for (i = 0; i < riverToDraw.size(); i++)
	{
		riverPoints.push_back(riverToDraw.at(i).second);
	}

	CubicSpline spline = CubicSpline(riverPoints);
	std::pair<std::vector<sf::VertexArray>, std::vector<UTIL::ScreenCoord>> shape = createRiverShapes(spline);

	sf::VertexArray riverArray = texturizeRiver(shape.first.at(0), shape.second);
	sf::VertexArray skyMirror = texturizeSky(shape.first.at(0), shape.second);
	std::pair<sf::VertexArray, sf::VertexArray> edgeArrays = texturizeEdges(std::make_pair(shape.first.at(1), shape.first.at(2)), shape.second);

	return std::make_pair(RiverRepresentation(riverArray, edgeArrays.first, edgeArrays.second, skyMirror), spline);
}


std::pair<sf::VertexArray, sf::VertexArray> RiverAnimation::texturizeEdges(std::pair<sf::VertexArray, sf::VertexArray> shapes, std::vector<UTIL::ScreenCoord> curve)
{
	unsigned int k;
	float travelLength = 0;
	float rTravelLength = 0;
	float lTravelLength = 0;
	sf::Vector2u riverEdgeTextSize = edgeTexture->getSize();
	sf::VertexArray right = shapes.first;
	sf::VertexArray left = shapes.second;
	UTIL::ScreenCoord lDerivativeVector;
	UTIL::ScreenCoord rDerivativeVector;

	for (k = 0; k < curve.size(); k++)
	{
		if (k > 0)
		{
			travelLength = (curve.at(k) - curve.at(k - 1)).abs() + travelLength;
			UTIL::ScreenCoord r2 = UTIL::ScreenCoord(right[2 * k + 1].position.x, right[2 * k + 1].position.y);
			UTIL::ScreenCoord r1 = UTIL::ScreenCoord(right[2 * (k - 1) + 1].position.x, right[2 * (k - 1) + 1].position.y);
			UTIL::ScreenCoord l2 = UTIL::ScreenCoord(left[2 * k].position.x, left[2 * k].position.y);
			UTIL::ScreenCoord l1 = UTIL::ScreenCoord(left[2 * (k - 1)].position.x, left[2 * (k - 1)].position.y);
			rTravelLength = (r2 - r1).abs() + rTravelLength;
			lTravelLength = (l2 - l1).abs() + lTravelLength;
		}
		if (k < curve.size() - 1)
		{
			rDerivativeVector = UTIL::ScreenCoord(left[2 * (k + 1)].position.x, left[2 * (k + 1)].position.y) - UTIL::ScreenCoord(left[2 * k].position.x, left[2 * k].position.y);
			lDerivativeVector = UTIL::ScreenCoord(right[2 * (k + 1) + 1].position.x, right[2 * (k + 1) + 1].position.y) - UTIL::ScreenCoord(right[2 * k + 1].position.x, right[2 * k + 1].position.y);
		}
		unsigned int rIntLength = (unsigned int)rTravelLength;
		float rRest = rTravelLength - rIntLength;
		unsigned int lIntLength = (unsigned int)lTravelLength;
		float lRest = lTravelLength - lIntLength;

		sf::Vector2f pos1 = right[2 * k + 1].position;
		sf::Vector2f pos2 = left[2 * k].position;

		/*sf::Vector2f frontVecTop = sf::Vector2f((intLength % riverEdgeTextSize.x / 2) + rest, 0);
		sf::Vector2f frontVecBot = sf::Vector2f((intLength % riverEdgeTextSize.x / 2) + rest, riverEdgeTextSize.y);
		sf::Vector2f backVecTop = sf::Vector2f((riverEdgeTextSize.x / 2 + intLength % riverEdgeTextSize.x / 2) + rest, 0);
		sf::Vector2f backVecBot = sf::Vector2f((riverEdgeTextSize.x / 2 + intLength % riverEdgeTextSize.x / 2) + rest, riverEdgeTextSize.y);*/
		if (pos1.y < pos2.y)
		{
			right[2 * k + 1].texCoords = sf::Vector2f((rIntLength % riverEdgeTextSize.x / 3) + rRest, 0);
			right[2 * k].texCoords = sf::Vector2f((rIntLength % riverEdgeTextSize.x / 3) + rRest, riverEdgeTextSize.y);
			left[2 * k].texCoords = sf::Vector2f((2 * riverEdgeTextSize.x / 3 + (lIntLength % riverEdgeTextSize.x / 3)) + lRest, 0);
			left[2 * k + 1].texCoords = sf::Vector2f((2 * riverEdgeTextSize.x / 3 + (lIntLength % riverEdgeTextSize.x / 3)) + lRest, riverEdgeTextSize.y);
		}
		else
		{
			right[2 * k + 1].texCoords = sf::Vector2f((2 *riverEdgeTextSize.x / 3 + (rIntLength % riverEdgeTextSize.x / 3)) + rRest, 0);
			right[2 * k].texCoords = sf::Vector2f((2 *riverEdgeTextSize.x / 3 + (rIntLength % riverEdgeTextSize.x / 3)) + rRest, riverEdgeTextSize.y);
			left[2 * k].texCoords = sf::Vector2f((lIntLength % riverEdgeTextSize.x / 3) + lRest, 0);
			left[2 * k + 1].texCoords = sf::Vector2f((lIntLength % riverEdgeTextSize.x / 3) + lRest, riverEdgeTextSize.y);
		}
	}
	return std::make_pair(right, left);
}

sf::VertexArray RiverAnimation::texturizeSky(sf::VertexArray shape, std::vector<UTIL::ScreenCoord> curve)
{
	unsigned int k;
	sf::Vector2u skyTextSize = skyTexture->getSize();
	for (k = 0; k < curve.size(); k++)
	{
		sf::Vector2f pos1 = shape[2 * k].position;
		sf::Vector2f pos2 = shape[2 * k + 1].position;

		shape[2 * k].texCoords = getSkyCoord(pos1);
		shape[2 * k + 1].texCoords = getSkyCoord(pos2);

		shape[2 * k].color = sf::Color(255, 255, 255, 145);
		shape[2 * k + 1].color = sf::Color(255, 255, 255, 145);
	}
	return shape;
}

sf::Vector2f RiverAnimation::getSkyCoord(sf::Vector2f riverPos)
{
	sf::Vector2u skyTextSize = skyTexture->getSize();
	return sf::Vector2f((int)(riverPos.x + drawBucket->getOffset().x * 1 / 8) % skyTextSize.x, (int)(riverPos.y + drawBucket->getOffset().y * 1 / 8) % skyTextSize.y);
}

sf::VertexArray RiverAnimation::texturizeRiver(sf::VertexArray shape, std::vector<UTIL::ScreenCoord> curve)
{
	unsigned int k;
	float travelLength = 0;
	sf::Vector2u riverTextSize = riverTexture->getSize();
	for (k = 0; k < curve.size(); k++)
	{
		if (k > 0)
		{
			travelLength = (curve.at(k) - curve.at(k - 1)).abs() + travelLength;
		}
		unsigned int intLength = (unsigned int)travelLength;
		float rest = travelLength - intLength;
		shape[2 * k].texCoords = sf::Vector2f(riverTextSize.x / 2 + width, (intLength % riverTextSize.y) + rest);
		shape[2 * k + 1].texCoords = sf::Vector2f(riverTextSize.x / 2 - width, (intLength % riverTextSize.y) + rest);
		shape[2 * k].color = sf::Color(100, 100, 100, 255);
		shape[2 * k + 1].color = sf::Color(100, 100, 100, 255);
	}
	return shape;
}

std::pair<std::vector<sf::VertexArray>, std::vector<UTIL::ScreenCoord>> RiverAnimation::createRiverShapes(CubicSpline shapeSpline)
{
	std::vector<CubicPolynomial> xPoly = shapeSpline.getPolynomials().first;
	std::vector<CubicPolynomial> yPoly = shapeSpline.getPolynomials().second;
	std::vector<float> h = shapeSpline.getStepVector();
	sf::VertexArray riverShape = sf::VertexArray(sf::TriangleStrip, 2 * ((xPoly.size() - 1) * (curveDisc - 1) + 1));
	sf::VertexArray leftEdgeShape = sf::VertexArray(sf::TriangleStrip, 2 * ((xPoly.size() - 1) * (curveDisc - 1) + 1));
	sf::VertexArray rightEdgeShape = sf::VertexArray(sf::TriangleStrip, 2 * ((xPoly.size() - 1) * (curveDisc - 1) + 1));

	std::vector<UTIL::ScreenCoord> curveCoords;
	UTIL::ScreenCoord widthVector;
	unsigned int i, k;
	curveCoords.push_back(UTIL::ScreenCoord(shapeSpline.getPolynomials().first.at(0).evaluate(0), shapeSpline.getPolynomials().second.at(0).evaluate(0)));
	for (i = 0; i < xPoly.size() - 1; i++)
	{
		CubicPolynomial xCurve = shapeSpline.getPolynomials().first.at(i);
		CubicPolynomial yCurve = shapeSpline.getPolynomials().second.at(i);

		float h1 = h.at(i);
		float h2 = h.at(i + 1);
		float d = h2 - h1;
		//rita kurva
		for (k = 1; k < (curveDisc); k++)
		{
			float hk = h1 + k * d / (curveDisc - 1);
			float x = xCurve.evaluate(hk - h1);
			float y = yCurve.evaluate(hk - h1);

			curveCoords.push_back(UTIL::ScreenCoord(x, y));
		}
		//rita å
	}
	for (k = 0; k < curveCoords.size(); k++)
	{
		if (k == 0)
		{
			widthVector = normalize(UTIL::turnByAngle((curveCoords.at(1) - curveCoords.at(0)), atan(1) * 2));
		}
		else if (k == curveCoords.size() - 1)
		{
			widthVector = normalize(UTIL::turnByAngle((curveCoords.at(k) - curveCoords.at(k - 1)), atan(1) * 2));
		}
		else
		{
			widthVector = normalize(UTIL::turnByAngle((curveCoords.at(k + 1) - curveCoords.at(k - 1)), atan(1) * 2));
		}

		sf::Vector2f pos1 = sf::Vector2f((curveCoords.at(k) + widthVector * width).x, (curveCoords.at(k) + widthVector * width).y);
		sf::Vector2f pos2 = sf::Vector2f((curveCoords.at(k) - widthVector * width).x, (curveCoords.at(k) - widthVector * width).y);

		riverShape[2 * k].position = pos1;
		riverShape[2 * k + 1].position = pos2;

		rightEdgeShape[2 * k].position = pos1;
		rightEdgeShape[2 * k + 1].position = sf::Vector2f(curveCoords.at(k).x, curveCoords.at(k).y);

		leftEdgeShape[2 * k].position = sf::Vector2f(curveCoords.at(k).x, curveCoords.at(k).y);
		leftEdgeShape[2 * k + 1].position = pos2;
	}
	std::vector<sf::VertexArray> retVec = { riverShape , leftEdgeShape, rightEdgeShape };
	return std::make_pair(retVec, curveCoords);
}