#include "TextDrawer.h"


TextDrawer::TextDrawer(GraphicsAssets* assts)
{
	fontPack = &assts->fontPackage;
	//font = &fontPack->standardFont;
	font = &fontPack->standardFont;
}

TextDrawer::TextDrawer(const TextDrawer& cpEQ)
{
	fontPack = cpEQ.fontPack;

	font = cpEQ.font;
	charSize = cpEQ.charSize;
	charColor = cpEQ.charColor;
}

TextDrawer& TextDrawer::operator=(const TextDrawer cpEQ)
{
	fontPack = cpEQ.fontPack;

	font = cpEQ.font;
	charSize = cpEQ.charSize;
	charColor = cpEQ.charColor;

	return *this;
}

sf::Text TextDrawer::drawText(std::string string, sf::Vector2f pos, int lineWidth)
{
	return drawText(string, pos, lineWidth, false, false);
}

sf::Text TextDrawer::drawText(std::string string, sf::Vector2f pos, int lineWidth, bool Center)
{
	return drawText(string, pos, lineWidth, true, true);
}

sf::Text TextDrawer::drawText(std::string string, sf::Vector2f pos, int lineWidth, bool horCenter, bool vertCenter)
{
	sf::Text text;
	std::string lineStr;

	text.setString(converter.from_bytes(string));
	text.setFont(*font);
	text.setCharacterSize(charSize);
	text.setFillColor(charColor);

	int testt = text.getLocalBounds().width;
	if (text.getLocalBounds().width > lineWidth)
	{
		std::string restStr = string;
		int startPos = 0;
		int spacePos;
		bool done = false;

		while (!done)
		{
			if (restStr.find(" ") != std::string::npos)
			{
				spacePos = restStr.find(" ") + 1;
			}
			else
			{
				done = true;
				spacePos = restStr.length()-1;
			}

			std::string wordStr = restStr.substr(startPos, spacePos);
			int test = restStr.length();
			if (!done)
			{
				restStr = restStr.substr(spacePos, restStr.length() - 1);
			}

			//lineStr = lineStr + wordStr;
			text.setString(converter.from_bytes(lineStr + wordStr));
			if (text.getLocalBounds().width > lineWidth)
			{
				lineStr = lineStr + "\n" + wordStr;
			}
			else
			{
				lineStr = lineStr + wordStr;
			}
		}
		text.setString(converter.from_bytes(lineStr));
	}

	sf::Vector2f hVec(text.getLocalBounds().width / 2, 0);
	sf::Vector2f vVec(0, text.getLocalBounds().height / 2);

	if (vertCenter)
	{
		pos = pos - hVec;
	}
	if (horCenter)
	{
		pos = pos - vVec;
	}

	text.setPosition(pos);

	return text;
}