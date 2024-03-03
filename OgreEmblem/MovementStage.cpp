#include "MovementStage.h"
#include "BattleMap.h"
#include "mStageVisualData.h"
#include "MovementTargetCrossEvent.h"
#include "MovementDotsEvent.h"

MovementStage::MovementStage(Squad mvSquad, MapCoord startPos)//, BattleMap* map)
{
    movingSquad = mvSquad;
    moveRange = mvSquad.getMovesLeft();
    addCoord(startPos, true, 0);
    //bMap = map;
}

MovementStage::MovementStage(Squad mvSquad, MapCoord startPos, std::vector<MapCoord> mvPath)//, BattleMap* map)
{
    movingSquad = mvSquad;
    moveRange = mvSquad.getMovesLeft();
    //movementList.push_back(startPos);
    addCoord(startPos, true, 0);

    //bMap = map;
}

/*void MovementStage::tryCoord(MapCoord coord)
{
    int size = movementList.size();
    int i;
    MapCoord lastCoord;
    bool retraced = false;

    for (i = 0; i < size; i++)
    {
        if (movementList.at(i).equals(coord))
        {
            std::vector<MapCoord>::const_iterator first = movementList.begin();
            std::vector<MapCoord>::const_iterator last = movementList.begin() + i + 1;

            movementList = std::vector<MapCoord>(first, last);
            retraced = true;
            disconnected = false;
            break;
        }
    }

    if (!disconnected && !retraced) //if map cursor is still drawing the path
    {
        if (bMap->isCoordPassable(coord, movingSquad->getFlagTag()) /*&& bMap->isCoordEmpty(coord)*/ /*&& (int)movementList.size() < movingSquad->getMovesLeft() + 1) //+1 är för att startrutan är med i movelist
        {
            addCoord(coord);
        }
        else
        {
            disconnected = true;
        }
    }
}*/


void MovementStage::tryCoord(MapCoord coord, bool coordPassable, bool coordStandable, int stepCost)
{
    int size = movementList.size();
    int i;
    MapCoord lastCoord;
    bool retraced = false;

    for (i = 0; i < size; i++)
    {
        if (movementList.at(i).equals(coord))
        {
            std::vector<MapCoord>::const_iterator first = movementList.begin();
            std::vector<MapCoord>::const_iterator last = movementList.begin() + i + 1;
            std::vector<bool>::const_iterator sFirst = standableList.begin();
            std::vector<bool>::const_iterator sLast = standableList.begin() + i + 1;
            std::vector<int>::const_iterator cFirst = costList.begin();
            std::vector<int>::const_iterator cLast = costList.begin() + i + 1;

            movementList = std::vector<MapCoord>(first, last);
            standableList = std::vector<bool>(sFirst, sLast);
            costList = std::vector<int>(cFirst, cLast);

            MovementDotsEvent temp = MovementDotsEvent(movementList);
            eventQueue.addEvent(&temp);
            retraced = true;
            if (disconnected)
            {
                MovementTargetCrossEvent temp = MovementTargetCrossEvent();
                eventQueue.addEvent(&temp);
            }
            sumCost();
            disconnected = false;
            break;
        }
    }
    if (!retraced && !disconnected)
    {
        if (coordPassable && moveCostTot + stepCost < movingSquad.getMovesLeft() + 1)
        {
            addCoord(coord, coordStandable, stepCost);
            MovementDotsEvent temp = MovementDotsEvent(movementList);
            eventQueue.addEvent(&temp);
        }
        else
        {
            if (!disconnected && standableList.at(standableList.size() - 1))
            {
                MovementTargetCrossEvent temp = MovementTargetCrossEvent(movementList.at(movementList.size() - 1));
                eventQueue.addEvent(&temp);
            }
            disconnected = true;
        }
    }
}

void MovementStage::sumCost()
{
    int i;
    moveCostTot = 0;
    for (i = 0; i < costList.size(); i++)
    {
        moveCostTot = moveCostTot + costList.at(i);
    }
}

void MovementStage::addCoord(MapCoord coord, bool standable, int stepCost)
{
    movementList.push_back(coord);
    standableList.push_back(standable);
    costList.push_back(stepCost);
    sumCost();
}

MapCoord MovementStage::getLastStep()
{
    return movementList.at(movementList.size() - 1);
}

void MovementStage::backOneStep()
{
    if (movementList.empty())
    {
        throw new std::exception();
    }
    movementList.pop_back();
}

bool MovementStage::pathAtLimit()
{
    return ((movementList.size() - 1) == moveRange);
}

/*void MovementStage::performMove()
{
    if (movementList.size() < 2)
    {
        throw new std::exception();
    }
    MapCoord target = movementList.at(movementList.size() - 1);
    bMap->moveSquad(movingSquad, target.getX(), target.getY());
    movingSquad->subtractMoves(movementList.size() - 1);
    moveDone = true;
}*/

mStageVisualData MovementStage::getVisuals()
{
    long int id = movingSquad.getID();
    return mStageVisualData(movementList, movingSquad.getID(), true, disconnected);
}

bool MovementStage::isExecutable()
{
    return ((standableList.size() > 0) && standableList.at(standableList.size() - 1));
}


MovePath::MovePath(std::vector<MapCoord> coordPath, std::vector<int> moveCost)
{
    path = coordPath;
    cost = moveCost;
}


int MovePath::getTotalCost()
{
    int i;
    int retVal = 0;
    /*for (i = 0; i < cost.size(); i++)
    {
        retVal = cost.at(i) + retVal;
    }*/
    if (cost.size() > 0)
    {
        return cost.at(cost.size() - 1);
    }
    else
    {
        return 0;
    }
}

int MovePath::stepsFromMoveRange(int range)
{
    int sum = 0;
    int i = 0;
    while (sum + cost.at(i) < range)
    {
        sum = sum + cost.at(i);
        i = i + 1;
    }
    return i;
}

MovePath MovePath::walkPath(int range)
{
    unsigned int i = 1;
    int movesLeft = range;

    std::vector<MapCoord> newPath{ path.at(0) };
    std::vector<int> newCost{ 0 };

    while (i < cost.size() && cost.at(i) <= range)
    {
        newPath.push_back(path.at(i));
        newCost.push_back(cost.at(i));
        i = i + 1;
    }
    return MovePath(newPath, newCost);
}