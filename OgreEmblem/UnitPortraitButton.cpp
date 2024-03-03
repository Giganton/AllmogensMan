#include "UnitPortraitButton.h"
#include "GraphicsAssets.h"
#include "GraphicsUtils.h"

UnitPortraitButton::UnitPortraitButton(UnitData unitData, sf::Vector2f pos, GraphicsAssets* assets)
{
	portrait = assets->unitPackage.getProfessionPortrait(unitData.profession);
	portraitSize = assets->unitPackage.getPortraitSize();

	setInteractionBoxPos(pos);
	setInteractionBoxSize(getSize());

	name = unitData.name;
	level = std::to_string(unitData.level);

	position = pos;
	textDrawer = TextDrawer(assets);
	empty = false;
}


UnitPortraitButton::UnitPortraitButton(sf::Vector2f pos, GraphicsAssets* assets)
{
	portraitSize = assets->unitPackage.getPortraitSize();

	setInteractionBoxPos(pos);
	setInteractionBoxSize(getSize());

	position = pos;
	textDrawer = TextDrawer(assets);
	empty = true;
}

void UnitPortraitButton::mousePosUpdate(sf::Vector2i currentMousePos)
{
	sf::Vector2f posTransform = sf::Vector2f((float)currentMousePos.x, (float)currentMousePos.y);
	if (isThisHoveredBy(posTransform))
	{
		hovered = true;
	}
	else
	{
		hovered = false;
	}
}

void UnitPortraitButton::setPosition(sf::Vector2f pos)
{ 
	setInteractionBoxPos(pos);
	position = pos; 
}


sf::Vector2f UnitPortraitButton::getSize()
{
	return portraitSize + sf::Vector2f(2.0f * frameWidth, 2.0f * frameWidth);
}

void UnitPortraitButton::draw(sf::RenderWindow* window)
{
	if (!soldOut)
	{
		sf::Color frameColor;
		if (selected)
		{
			frameColor = sf::Color(0xb9, 0x81, 0x53);

		}
		else
		{
			frameColor = sf::Color(0x95, 0x88, 0x83);
		}
		sf::VertexArray frame = UTIL::buildFadedBox(position, portraitSize + sf::Vector2f(2.0f * frameWidth, 2.0f * frameWidth), frameColor);
		window->draw(frame);
		sf::Vector2f porPos = position + sf::Vector2f(frameWidth, frameWidth);

		if (empty)
		{
			sf::VertexArray visualQuads = sf::VertexArray(sf::Quads, 4);

			visualQuads[0].position = sf::Vector2f(porPos.x, porPos.y);
			visualQuads[1].position = sf::Vector2f(porPos.x + portraitSize.x, porPos.y);
			visualQuads[2].position = sf::Vector2f(porPos.x + portraitSize.x, porPos.y + portraitSize.y);
			visualQuads[3].position = sf::Vector2f(porPos.x, porPos.y + portraitSize.y);

			visualQuads[0].color = sf::Color(0x33, 0x21, 0x1b);
			visualQuads[1].color = sf::Color(0x33, 0x21, 0x1b);//#698287
			visualQuads[2].color = sf::Color(0x1d, 0x0f, 0x0b);//#1d2b2c
			visualQuads[3].color = sf::Color(0x19, 0x0e, 0x0b);//#394a54

			//frame.setTexture(unitAssets->portraitFrame);
			//frame.setPosition(portraitPos);

			window->draw(visualQuads);
		}
		else
		{
			sf::Sprite portraitSprite;
			portraitSprite.setTexture(*portrait);
			sf::Vector2f selectionOffset(0.0f, 0.0f);
			if (selected)
			{
				sf::IntRect port = portraitSprite.getTextureRect();
				portraitSprite.setTextureRect(sf::IntRect(port.left + 2, port.top + 2, port.width - 4, port.height - 4));
				selectionOffset = sf::Vector2f(2.0f, 2.0f);
			}
			portraitSprite.setPosition(porPos + selectionOffset);
			window->draw(portraitSprite);

			textDrawer.setNameFont();
			textDrawer.setSize(24);
			textDrawer.setColor(sf::Color(0xd2, 0xcc, 0xb6));

			window->draw(textDrawer.drawText(name, porPos + sf::Vector2f(2.0f, 0.0f), 600));
		}
	}
}