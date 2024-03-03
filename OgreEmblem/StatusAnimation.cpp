#include "StatusAnimation.h"
#include "Unit.h"
#include "Squad.h"
#include "GraphicsAssets.h"
#include<vector>
#include<string>
#include "Action.h"

StatusAnimation::StatusAnimation(std::map < ProfessionTag, sf::Texture>* tMap, ScreenPackage* sPack, VerticalMenuPackage* menuPack, sf::RenderWindow* ww)
{
	profTextureMap = tMap;
	font = sPack->font;
	cursorSprite.setTexture(sPack->cursor);

	menuAnim = VerticalMenuAnimation(menuPack, UTIL::ScreenCoord(0,0), ww);

	window = ww;
}

void StatusAnimation::draw(ScreenVisualData toDraw)
{
	float posX, posY;
	std::vector<UnitInSquadData> units = toDraw.getUnitList();
	sf::Sprite unitSprite;

	window->clear(sf::Color::White);

	drawText(toDraw.getHoveredUnit());

	while (units.size() > 0)
	{
		UnitData unit = units.at(units.size() - 1).unit;
		SquadPos mapPos = units.at(units.size() - 1).mapPos;
		units.pop_back();
		
		unitSprite.setTexture(profTextureMap->find(unit.profession)->second);

		posX = getSpritePosX(float(mapPos.getX()));
		posY = getSpritePosY(float(mapPos.getY()));

		unitSprite.setPosition(posX, posY);

		window->draw(unitSprite);
	}

	//draw cursor
	posX = getSpritePosX(float(toDraw.getCursorPos().x)) + 20;
	posY = getSpritePosY(float(toDraw.getCursorPos().y)) - float(cursorSprite.getTextureRect().height) - 10;
	cursorSprite.setPosition(posX, posY);
	window->draw(cursorSprite);
	//draw menu
	if (toDraw.isMenuActive())
	{
		menuAnim.draw(toDraw.getActiveMenu());
	}
}

float StatusAnimation::getSpritePosX(float posX)
{
	return squadWindowPosX + squadOffsetX + posX * unitSpacingX;
}

float StatusAnimation::getSpritePosY(float posY)
{
	return squadWindowPosY + squadOffsetY + posY * unitSpacingY;
}

void StatusAnimation::drawText(Unit* hoveredUnit)
{
	float posX, posY;
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(fontSize);
	text.setFillColor(sf::Color::Black);

	text.setString("Name: " + hoveredUnit->getName());
	posX = textWindowPosX + textOffsetX;
	posY = textWindowPosY + textOffsetY;
	text.setPosition(posX, posY);
	window->draw(text);

	text.setString("HP: " + std::to_string(hoveredUnit->getStatistics().HP) + "/" + std::to_string(hoveredUnit->getStatistics().maxHP));
	posY = posY + fontSize + textSpacing;
	text.setPosition(posX, posY);
	window->draw(text);

	text.setString("Attack power: " + std::to_string(hoveredUnit->getStatistics().attack));
	posY = posY + fontSize + textSpacing;
	text.setPosition(posX, posY);
	window->draw(text);

	text.setString("Defense: " + std::to_string(hoveredUnit->getStatistics().defense));
	posY = posY + fontSize + textSpacing;
	text.setPosition(posX, posY);
	window->draw(text);

	/*text.setString("Profession: " + hoveredUnit->getData().profession->getName());
	posY = posY + fontSize + textSpacing;
	text.setPosition(posX, posY);
	window->draw(text);*/

	//text.setString("Action: " + hoveredUnit->getData().action.getName());
	posY = posY + fontSize + textSpacing;
	text.setPosition(posX, posY);
	window->draw(text);
}