#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Squad.h"
#include "ActionAnimation.h"
#include<list>
#include "BattleStage.h"
#include "FightResults.h"
#include "ExperienceGainAnimation.h"
#include "ProfessionID.h"
#include "ActionTag.h"
#include "LifeBar.h"

#define SPRITE_H 76
#define SPRITE_W 74

class BattleAnimation
{
private:
    float winOffsetX = 50;
    float winOffsetY = 100;
    float squadOffsetX = 600;
    float lineOffsetX = 130;
    float lineOffsetY = 120;

    std::list<ActionResults> animationQueue;

    std::vector<sf::Sprite> underUnitsAdditionals;

    sf::Sprite homeSprites[TACTICAL_X][TACTICAL_Y];
    sf::Sprite awaySprites[TACTICAL_X][TACTICAL_Y];

    int homeID[TACTICAL_X][TACTICAL_Y];
    int awayID[TACTICAL_X][TACTICAL_Y];

    std::vector<sf::Sprite> overUnitsAdditionals;
    std::vector<sf::Sprite> overOverlayAdditionals;

    int startingXP = -1;
    int finalXP = -1;
    int startingLevel = -1;

    bool playerDefending = false;
    bool playerAttacking = false;

    float backOffsetX = 100;
    float backOffsetY = 100;

    sf::RectangleShape backRect;
    sf::RectangleShape overlayBox;
    std::vector<sf::Color> overlayColors;


    LifeBar homeLife[TACTICAL_X][TACTICAL_Y];
    LifeBar awayLife[TACTICAL_X][TACTICAL_Y];

    bool homeEmpty[TACTICAL_X][TACTICAL_Y] = { false };
    bool awayEmpty[TACTICAL_X][TACTICAL_Y] = { false };

    sf::RenderWindow* window = nullptr;

    std::map < ProfessionTag, sf::Texture>* textureMap;
    //std::map < ActionTag, ActionAnimation>* actionMap;
    GraphicsAssets* graphicsAssets = nullptr;

    ActionAnimation* currentAnimation = nullptr;

    //vektorer till att initiera xp-animering
    std::vector<std::pair<int, int>> xpDetails;
    std::vector<int> xpUnitLevels;
    std::vector<std::pair<int, int>> xpUnitPos;
    ExperienceGainAnimation xpAnimation;


    std::clock_t startTime = 0;

    bool unitDone = false;
    int animationStep = 0;
    bool initialized = false;

    bool animationDone = false;

    void setupUnit(UnitInSquadData unitData, bool unitAttacking, int xpGained);

public: 
    BattleAnimation() {};
    BattleAnimation(sf::RenderWindow* window, GraphicsAssets* assets);


    /*BattleAnimation(const BattleAnimation& cpEQ);
    BattleAnimation& operator=(const BattleAnimation asEQ);
    ~BattleAnimation() { };*/

    void setup(BattleVisualData stageData);
    void draw();
    bool isInitialized() { return initialized; };
    bool progress();

    void animateXPBars(sf::RenderWindow* ww);

    void resetAnimation() { initialized = false; animationDone = false; };
    bool isAnimationDone() { return animationDone; };

    UTIL::ScreenCoord getSpritePos(FightPos mapPos);
    sf::Vector2f getSpritePos(int unitID);

    sf::Sprite* getSpritePtr(FightPos position);
    sf::Sprite* getSpritePtr(int unitID);
    bool isSpriteAttacking(int id);
    LifeBar* getLifeBarPtr(FightPos position);
    LifeBar* getLifeBarPtr(int unitID);

    std::vector<int> getAllIDs();

    UTIL::ScreenCoord getBoxPos() { return UTIL::ScreenCoord(winOffsetX, winOffsetY); };
    UTIL::ScreenCoord getBoxSize() { return UTIL::ScreenCoord(backRect.getSize().x, backRect.getSize().y); };

    void addSpriteOverUnits(sf::Sprite sprite) { overUnitsAdditionals.push_back(sprite); };
    void addSpriteUnderUnits(sf::Sprite sprite) { underUnitsAdditionals.push_back(sprite); };
    void addSpriteOverOverlay(sf::Sprite sprite) { overOverlayAdditionals.push_back(sprite); };
    void setOverLayShade(double percent) { overlayBox.setFillColor(sf::Color(0, 0, 0, percent*255)); };
    void addOverlayColor(sf::Color color);

    sf::Vector2f getPosCoord(FightPos pos);
};