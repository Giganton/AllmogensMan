#pragma once
#include <SFML/Graphics.hpp>
#include "GraphicsAssets.h"
#include<string>

#include <locale>
#include <codecvt>
#include <string>

class TextDrawer
{
private:
	FontPackage* fontPack = nullptr;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	sf::Font* font = nullptr;
	unsigned int charSize = 24;
	sf::Color charColor = sf::Color::White;
public:
	TextDrawer() {};
	TextDrawer(GraphicsAssets* assts);

	TextDrawer(const TextDrawer& cpEQ);
	TextDrawer& operator=(const TextDrawer asEQ);
	~TextDrawer() { };

	void setColor(sf::Color color) { charColor = color; };
	void setSize(int size) { charSize = size; };
	void setNameFont() { font = &fontPack->nameFont; };
	void setStandardFont() { font = &fontPack->standardFont; };

	unsigned int getSize() { return charSize; };

	sf::Text drawText(std::string string, sf::Vector2f pos, int lineWidth);
	sf::Text drawText(std::string string, sf::Vector2f pos, int lineWidth, bool center);
	sf::Text drawText(std::string string, sf::Vector2f pos, int lineWidth, bool vertCenter, bool horCenter);
};
