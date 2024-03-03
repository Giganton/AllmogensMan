#pragma once
#include "BattleAnimation.h"
#include "BattleStage.h"
#include "Profession.h"
#include "Unit.h"
#include "Action.h"
#include "Squad.h"
#include "FightResults.h"
#include "Formler.h"
#include "ExperienceBar.h"

BattleAnimation::BattleAnimation(sf::RenderWindow* ww, GraphicsAssets* assets)
{
    textureMap = &assets->unitTextureMap;

    backRect = sf::RectangleShape(sf::Vector2f(1000, 700));
    backRect.setPosition(backOffsetX, backOffsetY);
    backRect.setFillColor(sf::Color(220, 240, 200, 255));

    overlayBox = sf::RectangleShape(sf::Vector2f(1000, 700));
    overlayBox.setPosition(backOffsetX, backOffsetY);
    overlayBox.setFillColor(sf::Color(0, 0, 0, 0));

    graphicsAssets = assets;

    window = ww;
}


UTIL::ScreenCoord BattleAnimation::getSpritePos(FightPos mapPos)
{
    int x, y;
    if (mapPos.attackingSide)
    {
        x = backOffsetX + winOffsetX + mapPos.squadPos.getX() * lineOffsetX;
        y = backOffsetY + winOffsetY + mapPos.squadPos.getY() * lineOffsetY;
    }
    else
    {
        x = backOffsetX + winOffsetX + squadOffsetX + (TACTICAL_X - 1 - mapPos.squadPos.getX()) * lineOffsetX;
        y = backOffsetY + winOffsetY + mapPos.squadPos.getY() * lineOffsetY;
    }
    return UTIL::ScreenCoord(x, y);
}

sf::Vector2f BattleAnimation::getSpritePos(int unitID)
{
    return getSpritePtr(unitID)->getPosition();
}

void BattleAnimation::setupUnit(UnitInSquadData unitData, bool unitAttacking, int xpGained)
{
    int x = unitData.mapPos.getX();
    int y = unitData.mapPos.getY();

    sf::Sprite tempSprite = sf::Sprite();
    ProfessionTag profTag = unitData.unit.profession;
    tempSprite.setTexture(textureMap->find(profTag)->second);

    float drawPosX, drawPosY;

    if (unitAttacking)
    {
        drawPosX = backOffsetX + winOffsetX + x * lineOffsetX;
        drawPosY = backOffsetY + winOffsetY + y * lineOffsetY;
        homeEmpty[x][y] = false;
        tempSprite.setPosition(drawPosX, drawPosY);

        homeSprites[x][y] = tempSprite;
        homeID[x][y] = unitData.unit.ID;
        homeLife[x][y] = LifeBar(homeSprites[x][y], unitData.unit.statistics.HP, unitData.unit.statistics.maxHP);
    }
    else
    {
        drawPosX = backOffsetX + winOffsetX + squadOffsetX + (TACTICAL_X - 1 - x) * lineOffsetX;
        drawPosY = backOffsetY + winOffsetY + y * lineOffsetY;
        awayEmpty[x][y] = false;
        tempSprite.setTextureRect(sf::IntRect(tempSprite.getTextureRect().width, 0, -tempSprite.getTextureRect().width, tempSprite.getTextureRect().height));
        tempSprite.setPosition(drawPosX, drawPosY);

        awaySprites[x][y] = tempSprite;
        awayID[x][y] = unitData.unit.ID;
        awayLife[x][y] = LifeBar(awaySprites[x][y], unitData.unit.statistics.HP, unitData.unit.statistics.maxHP);
    }

    if (!unitData.unit.dead && ((unitAttacking && playerAttacking) || (!unitAttacking && playerDefending)))
    {
        startingXP = unitData.unit.experiencePoints;
        startingLevel = unitData.unit.level;

        xpDetails.push_back(std::make_pair(startingXP, xpGained));
        xpUnitLevels.push_back(startingLevel);
        xpUnitPos.push_back(std::make_pair(x, y));
    }
}

void BattleAnimation::setup(BattleVisualData stageData)
{
    animationDone = false;
    std::vector<UnitInSquadData> atkList = stageData.getAtkers();
    std::vector<UnitInSquadData> defList = stageData.getDefers();
    float drawPosX, drawPosY;
    int i, j, x, y;
    playerDefending = stageData.isPlayerDefending();
    playerAttacking = stageData.isPlayerAttacking();

    for (i = 0; i < TACTICAL_X; i++)
    {
        for (j = 0; j < TACTICAL_Y; j++)
        {
            homeEmpty[i][j] = true;
            awayEmpty[i][j] = true;
        }
    }

    while (!atkList.empty())
    {
        UnitInSquadData atker = atkList.at(atkList.size() - 1);
        atkList.pop_back();
        setupUnit(atker, true, stageData.getXP());
    }

    while (!defList.empty())
    {
        UnitInSquadData defer = defList.at(defList.size() - 1);
        defList.pop_back();
        setupUnit(defer, false, stageData.getXP());
    }

    if (xpDetails.size() > 0)
    {
        xpAnimation = ExperienceGainAnimation(xpDetails, xpUnitLevels, xpUnitPos, playerAttacking);
    }
    animationQueue = stageData.getResults();
    initialized = true;
}

bool BattleAnimation::progress()
{
    double time;

    if (!initialized)
    {
        throw new std::exception();
    }
    bool actionDone = false;
    if (!animationQueue.empty())
    {
        unsigned int i;
        ActionResults animInfo = animationQueue.front();

        sf::Sprite* aSprite;
        std::vector<sf::Sprite*> dSprite;

        switch (animationStep)
        {
        case 0:
            //currentAnimation = actionMap->find(animInfo.getAction())->second;
            delete currentAnimation;
            currentAnimation = createActionAnimation(animInfo.getActionTag(), animInfo.didActionResolve(), true,  this, animInfo, graphicsAssets, window);
            
            animationStep = 1;
        case 1: //animate action
            /*aSprite = &homeSprites[animInfo.getAPos().getX()][animInfo.getAPos().getY()];
            for (i = 0; i < animInfo.getDPos().size(); i++)
            {
                dSprite.push_back(&awaySprites[animInfo.getDPos().at(i).getX()][animInfo.getDPos().at(i).getY()]);
            }*/
            currentAnimation->runAnimation();
            actionDone = currentAnimation->allAnimationsFinished();
            if (actionDone)
            {
                animationStep = 2;
                startTime = std::clock();
            }
            break;
        case 2:
            time = ((double)std::clock() - (double)startTime) / (double)CLOCKS_PER_SEC;
            if (time > 0.15)
            {
                animationStep = 3;
            }
            break;
        case 3:
            animationStep = 0;
            unitDone = true;
            animationQueue.pop_front();
            break;
        }
        return false;
    }
    else
    {
        return true;
    }
}

void BattleAnimation::addOverlayColor(sf::Color color)
{
    overlayColors.push_back(color);
}

sf::Sprite* BattleAnimation::getSpritePtr(FightPos position)
{
    if (position.attackingSide)
    {
        return &homeSprites[position.squadPos.getX()][position.squadPos.getY()];
    }
    else
    {
        return &awaySprites[position.squadPos.getX()][position.squadPos.getY()];
    }
}

sf::Sprite* BattleAnimation::getSpritePtr(int unitID)
{
    unsigned int i, j;
    for (i = 0; i < TACTICAL_X; i++)
    {
        for (j = 0; j < TACTICAL_Y; j++)
        {
            if (!homeEmpty[i][j] && homeID[i][j] == unitID)
            {
                return &homeSprites[i][j];
            }
            if (!awayEmpty[i][j] && awayID[i][j] == unitID)
            {
                return &awaySprites[i][j];
            }
        }
    }
    throw new std::exception();
    return nullptr;
}

bool BattleAnimation::isSpriteAttacking(int id)
{
    unsigned int i, j;
    for (i = 0; i < TACTICAL_X; i++)
    {
        for (j = 0; j < TACTICAL_Y; j++)
        {
            if (!homeEmpty[i][j] && homeID[i][j] == id)
            {
                return true;
            }
            if (!awayEmpty[i][j] && awayID[i][j] == id)
            {
                return false;
            }
        }
    }
    throw new std::exception();
    return false;
}

std::vector<int> BattleAnimation::getAllIDs()
{
    unsigned int i, j;
    std::vector<int> retVal;

    for (i = 0; i < TACTICAL_X; i++)
    {
        for (j = 0; j < TACTICAL_Y; j++)
        {
            if (!homeEmpty[i][j])
            {
                retVal.push_back(homeID[i][j]);
            }
            if (!awayEmpty[i][j])
            {
                retVal.push_back(awayID[i][j]);
            }
        }
    }

    return retVal;
}

LifeBar* BattleAnimation::getLifeBarPtr(FightPos position)
{
    if (position.attackingSide)
    {
        return &homeLife[position.squadPos.getX()][position.squadPos.getY()];
    }
    else
    {
        return &awayLife[position.squadPos.getX()][position.squadPos.getY()];
    }
}

LifeBar* BattleAnimation::getLifeBarPtr(int unitID)
{
    unsigned int i, j;
    for (i = 0; i < TACTICAL_X; i++)
    {
        for (j = 0; j < TACTICAL_Y; j++)
        {
            if (!homeEmpty[i][j] && homeID[i][j] == unitID)
            {
                return &homeLife[i][j];
            }
            if (!awayEmpty[i][j] && awayID[i][j] == unitID)
            {
                return &awayLife[i][j];
            }
        }
    }
    throw new std::exception();
    return nullptr;
}

void BattleAnimation::animateXPBars(sf::RenderWindow* ww)
{
    xpAnimation.progressAction(ww);
}

void BattleAnimation::draw()
{
    bool fightingDone = false;
    if (initialized)
    {
        int i, j;
        fightingDone = progress();
        window->draw(backRect);

        for (i = 0; i < underUnitsAdditionals.size(); i++)
        {
            window->draw(underUnitsAdditionals.at(i));
        }
        underUnitsAdditionals.clear();

        for (i = 0; i < TACTICAL_X; i++)
        {
            for (j = 0; j < TACTICAL_Y; j++)
            {
                if (!homeEmpty[i][j])
                {
                    window->draw(homeSprites[i][j]);
                    window->draw(homeLife[i][j].getRed());
                    window->draw(homeLife[i][j].getGreen());
                }
                if (!awayEmpty[i][j])
                {
                    window->draw(awaySprites[i][j]);
                    window->draw(awayLife[i][j].getRed());
                    window->draw(awayLife[i][j].getGreen());
                }
            }
        }

        currentAnimation->draw(window);

        for (i = 0; i < overUnitsAdditionals.size(); i++)
        {
            window->draw(overUnitsAdditionals.at(i));
        }
        overUnitsAdditionals.clear();
        for (i = 0; i < overlayColors.size(); i++)
        {
            overlayBox.setFillColor(overlayColors.at(i));
            window->draw(overlayBox);
        }
        overlayColors.clear();

        for (i = 0; i < overOverlayAdditionals.size(); i++)
        {
            window->draw(overOverlayAdditionals.at(i));
        }
        overOverlayAdditionals.clear();

    }

    if (fightingDone)
    {
        if (playerAttacking || playerDefending)
        {
            animateXPBars(window);
            animationDone = xpAnimation.animationFinished();
        }
        else
        {
            animationDone = true;
        }
    }
}

sf::Vector2f BattleAnimation::getPosCoord(FightPos pos)
{
    int x = pos.squadPos.getX();
    int y = pos.squadPos.getY();
    int xCoord = -1;
    int yCoord = -1;

    if (pos.attackingSide)
    {
        xCoord = backOffsetX + winOffsetX + x * lineOffsetX;
        yCoord = backOffsetY + winOffsetY + y * lineOffsetY;
    }
    else
    {
        xCoord = backOffsetX + winOffsetX + squadOffsetX + (TACTICAL_X - 1 - x) * lineOffsetX;
        yCoord = backOffsetY + winOffsetY + y * lineOffsetY;
    }

    return sf::Vector2f(xCoord, yCoord);

}

LifeBar::LifeBar()
{

}

LifeBar::LifeBar(sf::Sprite sprite, int hp, int maxHp)
{
    HP = hp;
    maxHP = maxHp;

    sf::Vector2f mapPos;
    mapPos = sprite.getPosition();
    float posX = mapPos.x;
    float posY = mapPos.y + SPRITE_H + 10;
    red.setSize(sf::Vector2f(SPRITE_W, 10));
    red.setFillColor(sf::Color::Red);
    red.setPosition(posX, posY);
    int greenLength = (int)(((double)HP / (double)maxHP) * SPRITE_W);

    green.setSize(sf::Vector2f(float(greenLength), 10));
    green.setFillColor(sf::Color::Green);
    green.setPosition(posX, posY);
}

void LifeBar::setHP(int newHP)
{
    HP = newHP;
    int greenLength = (int)(((double)HP / (double)maxHP) * SPRITE_W);

    green.setSize(sf::Vector2f(float(greenLength), 10));
}

void LifeBar::dealDamage(int incomingDamage)
{
    int newHP = HP - incomingDamage;
    if (newHP < 0)
    {
        newHP = 0;
    }
    setHP(newHP);
}