#include "SquadWindowButton.h"
#include "SquadDrawer.h"
#include "GraphicsAssets.h"

SquadWindowButton::SquadWindowButton(Squad squad, sf::Vector2f pos, GraphicsAssets* assts)
{
	position = pos;
	assets = assts;

	setInteractionBoxPos(pos);
	setInteractionBoxSize(squadBoxSize);

	//visualBox = sf::RectangleShape(squadBoxSize);
	//visualBox.setPosition(pos);

	UTIL::ScreenCoord spriteSize(MAP_SPRITE_W, MAP_SPRITE_H);
	UTIL::ScreenCoord scPos(pos.x - 61, pos.y - 33);
	//squadRep = SquadRepresentation(squad, spriteSize, squad.getFlagTag(), scPos);
	squadName = squad.getName();
	squadID = squad.getID();

	empty = false;

	setupSquad(squad);

	textDrawer = TextDrawer(assts);
}

SquadWindowButton::SquadWindowButton(sf::Vector2f pos, GraphicsAssets* assts)
{
	position = pos;
	assets = assts;

	setInteractionBoxPos(pos);
	setInteractionBoxSize(squadBoxSize);

	textDrawer = TextDrawer(assts);

	UTIL::ScreenCoord spriteSize(MAP_SPRITE_W, MAP_SPRITE_H);
	UTIL::ScreenCoord scPos(pos.x - 61, pos.y - 33);

	empty = true;

	unsigned int i;
	for (i = 0; i < (TACTICAL_Y * 2); i++)
	{
		unitGrid.push_back(std::make_pair(false, UnitData()));
	}
	setupPortraits();
}

void SquadWindowButton::insertSquad(Squad squad)
{
	squadName = squad.getName();
	squadID = squad.getID();
	empty = false;

	setupSquad(squad);
}

void SquadWindowButton::insertSquad(Squad sqd, bool emptySquad)
{
	if (emptySquad)
	{
		newSquad = true;
	}
	insertSquad(sqd);
}

void SquadWindowButton::removeSquad()
{
	squadID = -1;
	squadName = "";
	empty = true;

	unsigned int i;
	unitGrid.clear();
	for (i = 0; i < (TACTICAL_Y * 2); i++)
	{
		unitGrid.push_back(std::make_pair(false, UnitData()));
	}
	setupPortraits();
}

void SquadWindowButton::drawName(sf::RenderWindow* window)
{
	textDrawer.setSize(24);
	textDrawer.setColor(sf::Color(0xd2, 0xcc, 0xb6));//#d2ccb6
	textDrawer.setNameFont();

	sf::Vector2f midP = position + sf::Vector2f(squadBoxSize.x / 2, -14.0f);
	sf::Text name = textDrawer.drawText(squadName, midP, 2000, true);

	sf::Vector2f fSize(name.getLocalBounds().width + 17, name.getLocalBounds().height + 10);
	sf::VertexArray textFrame = UTIL::buildFadedBox(name.getPosition() + sf::Vector2f(-7, 0), fSize, sf::Color(0x32, 0x45, 0x75));
	sf::VertexArray textFrameFrame = UTIL::buildFadedBox(name.getPosition() + sf::Vector2f(-9, -2), fSize + sf::Vector2f(4.0f, 4.0f), sf::Color(0x95, 0x88, 0x83));
	//textFrame.setFillColor(sf::Color::Magenta);
	//textFrame.setPosition(name.getPosition() + sf::Vector2f(-7, 0));

	window->draw(textFrameFrame);
	window->draw(textFrame);
	window->draw(name);
}

void SquadWindowButton::drawBox(sf::RenderWindow* window)
{
	float frameThickness = 2;
	//sf::VertexArray visualQuads = sf::VertexArray(sf::Quads, 4);
	sf::VertexArray visualQuads = UTIL::buildFadedBox(position, squadBoxSize, sf::Color(0x0e, 0x07, 0x05));

	/*visualQuads[0].position = sf::Vector2f(position.x, position.y);
	visualQuads[1].position = sf::Vector2f(position.x + squadBoxSize.x, position.y);
	visualQuads[2].position = sf::Vector2f(position.x + squadBoxSize.x, position.y + squadBoxSize.y);
	visualQuads[3].position = sf::Vector2f(position.x, position.y + squadBoxSize.y);

	visualQuads[0].color = sf::Color(0x0e, 0x07, 0x05);
	visualQuads[1].color = sf::Color(0x0e, 0x07, 0x05);//#698287
	visualQuads[2].color = sf::Color(0x06, 0x01, 0x00);//#1d2b2c
	visualQuads[3].color = sf::Color(0x06, 0x01, 0x00);//#394a54*/

	sf::VertexArray visualFrame = sf::VertexArray(sf::Quads, 4);
	sf::Vector2f frameOffset(-frameThickness, -frameThickness);
	sf::Vector2f frameSize = squadBoxSize + sf::Vector2f(frameThickness * 2, frameThickness * 2);

	sf::Vector2f framePos = position + frameOffset;

	visualFrame[0].position = sf::Vector2f(framePos.x, framePos.y);
	visualFrame[1].position = sf::Vector2f(framePos.x + frameSize.x, framePos.y);
	visualFrame[2].position = sf::Vector2f(framePos.x + frameSize.x, framePos.y + frameSize.y);
	visualFrame[3].position = sf::Vector2f(framePos.x, framePos.y + frameSize.y);

	visualFrame[0].color = sf::Color(0x95, 0x88, 0x83);
	visualFrame[1].color = sf::Color(0x85, 0x78, 0x73);//#698287
	visualFrame[2].color = sf::Color(0x95, 0x88, 0x83);//#1d2b2c
	visualFrame[3].color = sf::Color(0xa5, 0x98, 0x93);//#394a54

	window->draw(visualFrame);
	window->draw(visualQuads);

}

void SquadWindowButton::setupSquad(Squad squad)
{
	unitGrid.clear();
	unsigned int i, j;
	for (i = 0; i < TACTICAL_X; i++)
	{
		for (j = 0; j < TACTICAL_Y; j++)
		{
			if (squad.getTile(i, j)->isEmpty())
			{
				unitGrid.push_back(std::make_pair(false, UnitData()));
			}
			else
			{
				unitGrid.push_back(std::make_pair(true, squad.getUnitPtr(i, j)->getData()));
			}
		}
	}
	setupPortraits();
}

void SquadWindowButton::setupPortraits()
{
	unsigned int i;
	sf::Vector2f allOffset(22, 22);
	float portraitXOffset = 18.0f;
	float portraitYOffset = 30.0f;
	sf::Vector2f thisPosition = position + allOffset;
	sf::Vector2f portraitSize = assets->unitPackage.getPortraitSize();

	unitButtons.clear();
	for (i = 0; i < 6; i++)
	{
		if (unitGrid.at(i).first)
		{
			UnitPortraitButton portrait = UnitPortraitButton(unitGrid.at(i).second, thisPosition, assets);
			unitButtons.push_back(portrait);
		}
		else
		{
			UnitPortraitButton portrait = UnitPortraitButton(thisPosition, assets);
			unitButtons.push_back(portrait);
		}

		if (i == 2)
		{
			thisPosition = position + allOffset + sf::Vector2f(0.0f, portraitSize.y + portraitYOffset);
		}
		else
		{
			thisPosition = thisPosition + sf::Vector2f(portraitSize.x + portraitXOffset, 0.0f);
		}
	}
}

void SquadWindowButton::drawAllPortraits(sf::RenderWindow* window)
{
	unsigned int i;
	sf::Vector2f allOffset(22, 22);
	float portraitXOffset = 18.0f;
	float portraitYOffset = 30.0f;
	sf::Vector2f thisPosition = position + allOffset;
	sf::Vector2f portraitSize = assets->unitPackage.getPortraitSize();

	for (i = 0; i < 6; i++)
	{
		if (unitGrid.at(i).first)
		{
			drawPortrait(unitGrid.at(i).second, thisPosition, window);
		}
		else
		{
			drawPortrait(thisPosition, window);
		}

		if (i == 2)
		{
			thisPosition = position + allOffset + sf::Vector2f(0.0f, portraitSize.y + portraitYOffset);
		}
		else
		{
			thisPosition = thisPosition + sf::Vector2f(portraitSize.x + portraitXOffset, 0.0f);
		}
	}
}

void SquadWindowButton::drawPortrait(sf::Vector2f portraitPos, sf::RenderWindow* window)
{
	UnitPortraitButton portrait = UnitPortraitButton(portraitPos, assets);
	portrait.draw(window);
}

void SquadWindowButton::drawPortrait(UnitData uData, sf::Vector2f pos, sf::RenderWindow* window)
{
	UnitPortraitButton portrait = UnitPortraitButton(uData, pos, assets);
	portrait.draw(window);
}

void SquadWindowButton::draw(sf::RenderWindow* window)
{
	drawBox(window);
	//drawAllPortraits(window);
	unsigned int i;
	for (i = 0; i < unitButtons.size(); i++)
	{
		unitButtons.at(i).draw(window);
		//window->draw(squadSprites.at(i));
	}
	if (!empty)
	{
		drawName(window);
	}
}

int SquadWindowButton::getHoveredPortraitSpot()
{
	if (!portraitIsHovered)
	{
		throw new std::exception();
	}

	return hoveredPortraitSpot;
}

SquadPos SquadWindowButton::getHoveredSquadPos()
{
	int index = getHoveredPortraitSpot();
	return SquadPos(index);
}

int SquadWindowButton::isHoveredPortraitEmpty()
{
	if (!portraitIsHovered)
	{
		throw new std::exception();
	}
	return !unitGrid.at(hoveredPortraitSpot).first;

}

void SquadWindowButton::mousePosUpdate(sf::Vector2i currentMousePos)
{
	sf::Vector2f posTransform = sf::Vector2f((float)currentMousePos.x, (float)currentMousePos.y);
	portraitIsHovered = false;
	if (isThisHoveredBy(posTransform))
	{
		if (!hovered)
		{
			hovered = true;
		}
		unsigned int i;
		for (i = 0; i < unitButtons.size(); i++)
		{
			unitButtons.at(i).mousePosUpdate(currentMousePos);
			if (unitButtons.at(i).isHovered())// && unitGrid.at(i).first)
			{
				hoveredPortraitSpot = i;
				portraitIsHovered = true;
			}
		}
	}
	else
	{
		if (hovered)
		{
			hovered = false;
		}
	}
}

void SquadWindowButton::selectPortrait(SquadPos pos)
{
	int index = getUnitIndex(pos);
	unitButtons.at(index).setSelected(true); 
}

void SquadWindowButton::deselectPortraits()
{
	unsigned int i;
	for (i = 0; i < unitButtons.size(); i++)
	{
		unitButtons.at(i).setSelected(false);
	}
}

UnitData SquadWindowButton::getUnitData(SquadPos pos)
{ 
	int index = getUnitIndex(pos);
	if (!unitGrid.at(index).first)
	{
		throw new std::exception();
	}
	return unitGrid.at(index).second; 
}

int SquadWindowButton::getUnitIndex(SquadPos pos)
{
	return pos.getIndexRepresentation();
}