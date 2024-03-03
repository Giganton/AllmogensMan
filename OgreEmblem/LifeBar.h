#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

class LifeBar
{
private:
    sf::RectangleShape red;
    sf::RectangleShape green;

    int HP = -1;
    int maxHP = -1;
public:
    LifeBar(sf::Sprite sprite, int hp, int maxHp);
    LifeBar();
    sf::RectangleShape getRed() { return red; };
    sf::RectangleShape getGreen() { return green; };

    void setGreenLength(float length) { green.setSize(sf::Vector2f(length, 10)); };
    float getGreenLength() { return green.getSize().x; };
    float getRedLength() { return red.getSize().x; };

    void setHP(int newHP);
    void dealDamage(int incomingDamage);
    int getHP() { return HP; };
    int getMaxHP() { return maxHP; };
};