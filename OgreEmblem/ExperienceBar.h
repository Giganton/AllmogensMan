#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "GraphicsUtils.h"

class ExperienceBar
{
private:
    sf::RectangleShape frame;
    sf::RectangleShape background;

    sf::RectangleShape barFrame;
    sf::RectangleShape emptyBar;
    sf::RectangleShape filledBar;

    sf::Color frameColor = sf::Color(sf::Color(95, 97, 13, 255));
    sf::Color backgroundColor = sf::Color(sf::Color(248, 250, 107, 255));
    sf::Color barFrameColor = sf::Color(0xAB, 0xAD, 0x16, 0xFF);
    sf::Color emptyBarColor = sf::Color(0x63, 0x63, 0x49, 0xFF);
    sf::Color filledBarColor = sf::Color(0xDD, 0xE0, 0x1D, 0xFF);

    float barLength = 76;

    int experiencePercentage = -1;
    int unitLevel = -1;

    UTIL::ScreenCoord offset;

public:
	ExperienceBar() {};
    ExperienceBar(int startExp, UTIL::ScreenCoord barOffset);

    void draw(sf::RenderWindow* ww);
    void setXP(int xp);
    void increment();

    int getXP() { return experiencePercentage; };
};