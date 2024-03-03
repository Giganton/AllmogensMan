#include "SquadRepButton.h"

SquadRepButton::SquadRepButton(Squad squad, sf::Vector2f pos, GraphicsAssets* assets)
{
	position = pos;
	squadName = squad.getName();
	squadID = squad.getID();

	squadRep = SquadRepresentation(squad, UTIL::ScreenCoord(MAP_SPRITE_W, MAP_SPRITE_H), squad.getFlagTag(), UTIL::vector2ScreenCoord(pos));
	squadDrawer = SquadDrawer(&assets->mapPackage.squadTextureMap);
	squadBoxSize = sf::Vector2f(MAP_SPRITE_W, MAP_SPRITE_H);

	addInteractionTile(pos);
	textDrawer = TextDrawer(assets);
}

SquadRepButton::SquadRepButton(sf::Vector2f pos, GraphicsAssets* assets)
{
	position = pos;
	squadBoxSize = sf::Vector2f(MAP_SPRITE_W, MAP_SPRITE_H);
	addInteractionTile(pos);
	textDrawer = TextDrawer(assets);
	empty = true;
}

void SquadRepButton::reInit(Squad squad)
{
	squadName = squad.getName();
	squadID = squad.getID();

	squadRep = SquadRepresentation(squad, UTIL::ScreenCoord(MAP_SPRITE_W, MAP_SPRITE_H), squad.getFlagTag(), UTIL::vector2ScreenCoord(position));
	empty = false;
}

void SquadRepButton::draw(sf::RenderWindow* window)
{
	unsigned int i;
	squadRep.animated = hovered;
	sf::Color colorA, colorB;

	
	UTIL::ScreenCoord pos = UTIL::vector2ScreenCoord(position);
	sf::VertexArray tileVertices = tileDrawer.createTileVertexArrayV2(std::vector<UTIL::ScreenCoord>{pos});

	if (selected)
	{
		colorA = sf::Color(0xa1, 0x9e, 0x30);
		colorB = sf::Color(0xc7, 0xc4, 0x5a);
	}
	else
	{
		colorA = sf::Color(0xb9, 0xb8, 0x92);
		colorB = sf::Color(0xa4, 0xa3, 0x81);
	}
	tileVertices[0].color = colorA;
	tileVertices[1].color = colorA;
	tileVertices[2].color = colorB; //(0xc7, 0xc4, 0x5a)
	tileVertices[3].color = colorB;

	window->draw(tileVertices);

	if (!empty)
	{
		std::vector<sf::Sprite> sprites = squadDrawer.drawMapSquad(squadRep);
		for (i = 0; i < sprites.size(); i++)
		{
			window->draw(sprites.at(i));
		}
		if (hovered || selected)
		{
			drawName(window);
		}
	}
}

void SquadRepButton::drawName(sf::RenderWindow* window)
{
	textDrawer.setSize(18);
	textDrawer.setColor(sf::Color(0xd2, 0xcc, 0xb6));//#d2ccb6
	textDrawer.setNameFont();

	sf::Vector2f midP = position + sf::Vector2f(TILE_W/2, TILE_H-22);
	sf::Text name = textDrawer.drawText(squadName, midP, 200, true);

	sf::Vector2f fSize(name.getLocalBounds().width + 17, name.getLocalBounds().height + 10);
	sf::VertexArray textFrame = UTIL::buildFadedBox(name.getPosition() + sf::Vector2f(-7, 0), fSize, sf::Color(0x32, 0x45, 0x75));
	sf::VertexArray textFrameFrame = UTIL::buildFadedBox(name.getPosition() + sf::Vector2f(-9, -2), fSize + sf::Vector2f(4.0f, 4.0f), sf::Color(0x95, 0x88, 0x83));
	//textFrame.setFillColor(sf::Color::Magenta);
	//textFrame.setPosition(name.getPosition() + sf::Vector2f(-7, 0));

	window->draw(textFrameFrame);
	window->draw(textFrame);
	window->draw(name);
}