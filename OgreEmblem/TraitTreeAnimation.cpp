#include "TraitTreeAnimation.h"

void TraitTreeAnimation::drawTree(sf::RenderWindow* window)
{
	/*switch (careerToDraw.type)
	{
	case TraitTreeType::triangle:
		drawTriangleTree(window);
		break;
	}*/
}
	
void TraitTreeAnimation::draw(sf::RenderWindow* window)
{
	drawTree(window);
}

void TraitTreeAnimation::mousePosUpdate(sf::Vector2i currentMousePos)
{
	sf::Vector2f mousePosTx(sf::Vector2f(currentMousePos.x, currentMousePos.y));
	isThisHoveredBy(mousePosTx);
}

bool TraitTreeAnimation::traitIsHovered()
{
	return imageIsHovered; 
}

void TraitTreeAnimation::drawTriangleTree(sf::RenderWindow* window)
{
	/*sf::VertexArray quads = sf::VertexArray(sf::Quads, 6 * 4);
	sf::Vector2f headPos, mid1Pos, mid2Pos, bot1Pos, bot2Pos, bot3Pos;
	float botY, midY, xIncrease, midXOffset;
	if (showSmall)
	{
		xIncrease = 100;
	}
	else
	{
		xIncrease = 62;
	}
	botY = xIncrease * 1.6;
	midY = botY / 2;

	bot1Pos = sf::Vector2f(0, botY);
	bot2Pos = sf::Vector2f(xIncrease, botY);
	bot3Pos = sf::Vector2f(xIncrease*2, botY);

	mid1Pos = sf::Vector2f(xIncrease / 2, midY);
	mid2Pos = sf::Vector2f(xIncrease / 2 + xIncrease, midY);

	headPos = sf::Vector2f(xIncrease, 0);

	sf::Vector2f traitSlotMid = sf::Vector2f(TRAIT_SLOT_SIZE / 2, TRAIT_SLOT_SIZE / 2);
	sf::Vector2f traitBarMid = sf::Vector2f(traitBarWidth / 2, 0);

	quads[0].position = offset + headPos + traitSlotMid - traitBarMid;
	quads[1].position = offset + headPos + traitSlotMid + traitBarMid;
	quads[2].position = offset + mid1Pos + traitSlotMid + traitBarMid;
	quads[3].position = offset + mid1Pos + traitSlotMid - traitBarMid;

	quads[4].position = offset + headPos + traitSlotMid - traitBarMid;
	quads[5].position = offset + headPos + traitSlotMid + traitBarMid;
	quads[6].position = offset + mid2Pos + traitSlotMid + traitBarMid;
	quads[7].position = offset + mid2Pos + traitSlotMid - traitBarMid;

	quads[8].position = offset + mid1Pos + traitSlotMid - traitBarMid;
	quads[9].position = offset + mid1Pos + traitSlotMid + traitBarMid;
	quads[10].position = offset + bot1Pos + traitSlotMid + traitBarMid;
	quads[11].position = offset + bot1Pos + traitSlotMid - traitBarMid;

	quads[12].position = offset + mid1Pos + traitSlotMid - traitBarMid;
	quads[13].position = offset + mid1Pos + traitSlotMid + traitBarMid;
	quads[14].position = offset + bot2Pos + traitSlotMid + traitBarMid;
	quads[15].position = offset + bot2Pos + traitSlotMid - traitBarMid;

	quads[16].position = offset + mid2Pos + traitSlotMid - traitBarMid;
	quads[17].position = offset + mid2Pos + traitSlotMid + traitBarMid;
	quads[18].position = offset + bot2Pos + traitSlotMid + traitBarMid;
	quads[19].position = offset + bot2Pos + traitSlotMid - traitBarMid;

	quads[20].position = offset + mid2Pos + traitSlotMid - traitBarMid;
	quads[21].position = offset + mid2Pos + traitSlotMid + traitBarMid;
	quads[22].position = offset + bot3Pos + traitSlotMid + traitBarMid;
	quads[23].position = offset + bot3Pos + traitSlotMid - traitBarMid;
	
	unsigned int i;
	for (i = 0; i < 6 * 4; i++)
	{
		quads[i].color = sf::Color::Red;
	}
	window->draw(quads);

	drawTraitSlot(treeToDraw.allNodes[0], headPos, window);

	drawTraitSlot(treeToDraw.allNodes[1], mid1Pos, window);

	drawTraitSlot(treeToDraw.allNodes[2], mid2Pos, window);

	drawTraitSlot(treeToDraw.allNodes[3], bot1Pos, window);

	drawTraitSlot(treeToDraw.allNodes[4], bot2Pos, window);

	drawTraitSlot(treeToDraw.allNodes[5], bot3Pos, window);
	if (!hitBoxInitiated)
	{//ordning viktig (index)
		hitBoxInitiated = true;
		addInteractionImage(&traitAssets->traitCircleHitBox, headPos + offset);
		addInteractionImage(&traitAssets->traitCircleHitBox, mid1Pos + offset);
		addInteractionImage(&traitAssets->traitCircleHitBox, mid2Pos + offset);
		addInteractionImage(&traitAssets->traitCircleHitBox, bot1Pos + offset);
		addInteractionImage(&traitAssets->traitCircleHitBox, bot2Pos + offset);
		addInteractionImage(&traitAssets->traitCircleHitBox, bot3Pos + offset);
	}*/
}

void TraitTreeAnimation::drawTraitSlot(TraitTag trait, sf::Vector2f position, sf::RenderWindow* window)
{
	sf::Sprite traitSprite, backgroundSprite;
	sf::Text traitName;

	backgroundSprite.setTexture(traitAssets->traitBackgroundTexture);
	backgroundSprite.setPosition(position + offset);
	window->draw(backgroundSprite);
	if (trait != TraitTag::enumTraitNone)
	{
		traitSprite.setTexture(traitAssets->traitTextures.find(trait)->second);
		traitSprite.setPosition(position + offset);
		window->draw(traitSprite);
	}
}

TraitTag TraitTreeAnimation::getHoveredTrait()
{
	if (!imageIsHovered)
	{
		throw new std::exception();
	}
	return TraitTag::enumDummyTrait;//treeToDraw.allNodes[hoveredImage];
}