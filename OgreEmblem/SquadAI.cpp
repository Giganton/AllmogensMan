#include "SquadAI.h"
#include "Squad.h"
#include "BattleMap.h"
#include "BattleStage.h"
#include "MovementStage.h"
#include "MapManagerVisualEventData.h"
#include "tagID.h"
#include "BattleEvent.h"
#include "SquadMovedEvent.h"
#include "UnitKilledEvent.h"

class Node
{
public:
	Node() {};
	Node(MapCoord crd) { coord = crd; };
	Node(MapCoord crd, int newG, int newH) { coord = crd; g = newG; h = newH; f = g + h; };

	MapCoord coord;
	int parent = -1;
	int g = -1;
	int h = -1;
	int f = -1;
};

std::vector<MapCoord> SquadAI::findPath(Squad squad)
{
	tagID ownFlag = squad.getFlagTag();
	MapCoord sqdPos = bField->findSquadPos(squad);
	MovePath pathToWalk;

	//std::vector<Squad*> sortedSquads = bMap->getSquadsByProximity(sqdPos);
	std::vector<SquadData> squadList = bField->getSquadData();
	int shortestPathLength = 9999999;
	//hitta närmsta gäng som inte är i samma lag
	MovePath fullPath;
	unsigned int i;
	for (i = 0; i < squadList.size(); i++)
	{
		SquadData sData = squadList.at(i);
		if (isAttackTargetViable(squad, sData.squad))
		{
			std::vector<MapCoord> viableNborTiles = standableTilesInRange(sData.mapPos, squad);
			if (!viableNborTiles.empty())
			{
				//MapCoord goalPos = closestCoordInList(sqdPos, viableNborTiles);

				MovePath tempPath = aStar(sqdPos, sData.mapPos, viableNborTiles, squad);
				if (tempPath.getTotalCost() < shortestPathLength)
				{
					fullPath = tempPath;
					shortestPathLength = tempPath.getTotalCost();
				}
			}
		}
	}

	if (fullPath.getTotalCost() > 0)
	{
		/*int nrOfSteps = fullPath.stepsFromMoveRange(squad.getMovesLeft());


		if (fullPath.getTotalCost() < (unsigned int)squad.getMovesLeft()) //minus ett för att få startrutan ur vägen
		{
			nrOfSteps = fullPath.getTotalCost();
		}
		else
		{
			nrOfSteps = squad.getMovesLeft();
		}

		std::vector<MapCoord>::const_iterator first = fullPath.begin();
		std::vector<MapCoord>::const_iterator last = fullPath.begin() + nrOfSteps + 1; //plus ett för att få med startrutan i vägen
		pathToWalk = std::vector<MapCoord>(first, last);*/

		pathToWalk = fullPath.walkPath(squad.getMovesLeft());
		//aStar har problem med att man får gå igenom sina kompisar
		//men inte kan landa på en, så vi måste kontrollera slutdestinationen
		while (!bField->canIStandHere(pathToWalk.getPath().at(pathToWalk.getPath().size() - 1), squad))
		{
			MapCoord start = pathToWalk.getPath().at(0);
			MapCoord goal = pathToWalk.getPath().at(pathToWalk.getPath().size() - 1);
			int range = squad.getMovesLeft();
			//hitta den landningsbara ruta som är närmst målet
			MapCoord newGoal = findClosestLandableTileWithinRange(squad, start, range, goal);
			//hitta vägen till den rutan
			if (newGoal.equals(start))
			{
				pathToWalk = MovePath({ start }, { 0 });
			}
			else
			{
				fullPath = aStar(start, newGoal, std::vector<MapCoord> {newGoal}, squad);

				/*if (fullPath.size() <= (unsigned int)squad.getMovesLeft())
				{
					nrOfSteps = fullPath.size() - 1;
				}
				else
				{
					nrOfSteps = squad.getMovesLeft();
				}

				std::vector<MapCoord>::const_iterator first = fullPath.begin();
				std::vector<MapCoord>::const_iterator last = fullPath.begin() + nrOfSteps + 1;
				pathToWalk = std::vector<MapCoord>(first, last);*/
				pathToWalk = fullPath.walkPath(squad.getMovesLeft());
			}
		}
	}
	return pathToWalk.getPath();
	//std::vector<Squad*> targetsInRange = bMap->allSquadsInRange(sqdPos.getX(), sqdPos.getY(), squad->getMoveRange() + 1);
}

MapCoord SquadAI::closestCoordInList(MapCoord sqdCoord, std::vector<MapCoord> coordList)
{
	unsigned int i;
	int closestDist = 99999;
	MapCoord closestCoord;
	for (i = 0; i < coordList.size(); i++)
	{
		int dist = sqdCoord.distanceTo(coordList.at(i));
		if (dist < closestDist)
		{
			closestDist = dist;
			closestCoord = coordList.at(i);
		}
	}
	return closestCoord;
}

std::vector<MapCoord> SquadAI::standableTilesInRange(MapCoord mapPos, Squad sqd)
{
	std::vector<MapCoord> retVec = {};
	int range = sqd.getAtkRange();
	int i, j;
	int x = mapPos.getX();
	int y = mapPos.getY();
	MapCoord testCoord;

	for (i = -range; i <= range; i++)
	{
		testCoord = MapCoord(x + i, y);
		if (i != 0 && bField->canIStandHere(testCoord, sqd))
		{
			retVec.push_back(testCoord);
		}
		for (j = 1; j <= range - abs(i); j++)
		{
			testCoord = MapCoord(x + i, y + j);
			if (bField->canIStandHere(testCoord, sqd))
			{
				retVec.push_back(testCoord);
			}
			testCoord = MapCoord(x + i, y - j);
			if (bField->canIStandHere(testCoord, sqd))
			{
				retVec.push_back(testCoord);
			}
		}
	}
	return retVec;
}
/*
Squad* SquadAI::siftThroughSquads(Squad* self, std::vector<Squad*> sortedList)
{
	tagID ownTag = self->getFlagTag();

}
*/

StructuredEventQueue SquadAI::handleBattleEvents(BattleVisualData vData)
{
	StructuredEventQueue generatedEvents;
	BattleEvent evnt = BattleEvent(-1, vData);
	generatedEvents.addEvent(&evnt); 
	std::list<ActionResults> resultsList = vData.getResults();

	unsigned int i;
	while (resultsList.size() > 0)
	{
		ActionResults results = resultsList.front();
		std::vector<std::pair<int, bool>> deathIDTeam = results.getDeathInfo();
		for (i = 0; i < deathIDTeam.size(); i++)
		{
			int squadID;
			if (deathIDTeam.at(i).second)
			{
				squadID = vData.getAtkID();
			}
			else
			{
				squadID = vData.getDefID();
			}
			UnitKilledEvent ev = UnitKilledEvent(-1, squadID, deathIDTeam.at(i).first);
			generatedEvents.addEvent(&ev);
		}
		resultsList.pop_front();
	}

	return generatedEvents;
}

StructuredEventQueue SquadAI::controlSquad(int squadID)
{
	StructuredEventQueue generatedEvents;
	MapCoord currPos = bField->findSquadPos(squadID);
	BattleStage bStage;
	MovementStage mStage;
	bool attackDone = false;

	Squad squad = bField->getSquadByID(squadID);

	StagePair retVal;

	int atkTarget = findAttackTarget(currPos, bField->getSquadByID(squadID), *bField);

	if (atkTarget != -1)
	{
		std::pair<BattleVisualData , std::vector<LevelUpData>> fightData = bField->doBattle(squadID, atkTarget);
		BattleVisualData vData = fightData.first;
		generatedEvents.concatenateQueues(handleBattleEvents(vData));
		attackDone = true;
	}
	else
	{
		std::vector<MapCoord> pathToWalk = findPath(squad);
		if (pathToWalk.size() > 1)
		{
			//mStage = MovementStage(squad, currPos, pathToWalk);
			
			MoveData mData = bField->moveSquad(MoveData(squadID, pathToWalk));
			SquadMovedEvent evnt = SquadMovedEvent(-1, mData);
			generatedEvents.addEvent(&evnt);
		}
		currPos = bField->findSquadPos(squad);
		int atkTarget = findAttackTarget(currPos, squad, *bField);

		if (atkTarget != -1 && !attackDone)
		{
			std::pair<BattleVisualData, std::vector<LevelUpData>> fightData = bField->doBattle(squadID, atkTarget);
			BattleVisualData vData = fightData.first;
			generatedEvents.concatenateQueues(handleBattleEvents(vData));
			attackDone = true;
		}
	}
	return generatedEvents;
}

MapCoord SquadAI::findClosestLandableTileWithinRange(Squad squad, MapCoord start, int range, MapCoord goal)
{
	MapCoord current = goal;
	bool stillLooking = true;
	unsigned int i;
	int dist = start.distanceTo(goal);

	std::vector<MapCoord> lookedAt = { };
	std::list<MapCoord> possibleTiles = { current };

	while (stillLooking)
	{
		current = possibleTiles.front();
		possibleTiles.pop_front();

		bool lookedAtAlready = false;
		unsigned int n = 0;
		while (!lookedAtAlready && n < lookedAt.size())
		{
			lookedAtAlready = current.equals(lookedAt.at(n));
			n = n + 1;
		}
		if (!lookedAtAlready)
		{
			if ((calculateH(start, current, squad) <= range && bField->canIStandHere(current, squad)) || current.equals(start))
			{
				return current;
			}
			else if (calculateH(start, current, squad) <= range && bField->canIPassHere(current, squad))
			{
				std::vector<MapCoord> neighbours = getSurroundingCoords(current);
				for (i = 0; i < neighbours.size(); i++)
				{
					possibleTiles.push_back(neighbours.at(i));
				}
			}
			lookedAt.push_back(current);
		}
	}
	return start;
}

bool SquadAI::isAttackTargetViable(Squad atker, Squad defer)
{
	return (!defer.isDefeated() && atker.getFlagTag() != defer.getFlagTag());
}

int SquadAI::findAttackTarget(MapCoord sqdPos, Squad attacker, BattleField bField)
{
	unsigned int i;
	std::vector<Squad> targetsInRange = bField.allSquadsInRange(sqdPos.getX(), sqdPos.getY(), attacker.getAtkRange());
	if (targetsInRange.size() > 0)
	{
		for (i = 0; i < targetsInRange.size(); i++)
		{
			if (isAttackTargetViable(attacker, targetsInRange.at(i)))
			{
				return targetsInRange.at(i).getID();
			}
		}
	}
	return -1;
}

MovePath SquadAI::aStar(MapCoord start, MapCoord objective, std::vector<MapCoord> goalTiles, Squad squad)
{
	unsigned int i;
	bool goalOk = false;
	for (i = 0; i < goalTiles.size(); i++)
	{
		if (bField->canIStandHere(goalTiles.at(i), squad))
		{
			goalOk = true;
		}
		else
		{
			goalTiles.erase(goalTiles.begin() + i);
			i = i - 1;
		}
	}
	if (!goalOk)
	{
		throw new std::exception();
	}
	if (start.isInList(goalTiles))
	{
		std::vector<MapCoord> retVal1 = { start };
		std::vector<int> retVal2 = { 0 };
		return MovePath(retVal1, retVal2);
	}
	
	std::vector<Node> nodeList;
	std::vector<int> open; //innehåller indexar till nodelist
	std::vector<int> closed; //innehåller indexar till nodelist
	bool goalReached = false;
	
	nodeList.push_back(Node(start, 0, calculateH(start, objective, squad)));
	open.push_back(0);
	int iterations = 0;

	while (open.size() > 0 && !goalReached)
	{
		iterations++;
		int lowestOpen = findLowestF(open, nodeList);
		int currentIndex = open.at(lowestOpen);
		Node current = nodeList.at(currentIndex);
		closed.push_back(currentIndex);
		open.erase(open.begin() + lowestOpen);

		if (current.coord.isInList(goalTiles)) //är vi framme?
		{
			goalReached = true;
			return constructPath(current, nodeList);
		}
		else
		{
			std::vector<MapCoord> neighbours = getSurroundingCoords(current.coord);
			for (i = 0; i < neighbours.size(); i++)
			{
				int cost = bField->getMovementCost(current.coord, neighbours.at(i), squad);
				Node contender = Node(neighbours.at(i), current.g + cost, calculateH(neighbours.at(i), objective, squad));
				if (bField->canIPassHere(neighbours.at(i), squad) && isNodeInSubset(contender, closed, nodeList))
				{
					int openIndex = isNodeInSubset(contender, open, nodeList);
					if (openIndex == -1) //om den inte finns i open
					{
						contender.parent = currentIndex;
						nodeList.push_back(contender);
						open.push_back(nodeList.size() - 1);
					}
					else if (contender.g < nodeList.at(open.at(openIndex)).g) //om den finns i open och har lägre g
					{
						nodeList.at(open.at(openIndex)).parent = currentIndex;
						nodeList.at(open.at(openIndex)).g = contender.g;
						nodeList.at(open.at(openIndex)).f = contender.g + nodeList.at(open.at(openIndex)).h;
					}
				}
			}
		}
	}
	return {}; //ge en tom vektor om ingen väg finnes
}

std::vector<MapCoord> SquadAI::getSurroundingCoords(MapCoord coord)
{
	std::vector<MapCoord> retVal;

	retVal.push_back(MapCoord(coord.getX(), coord.getY() - 1));
	retVal.push_back(MapCoord(coord.getX() + 1, coord.getY()));
	retVal.push_back(MapCoord(coord.getX(), coord.getY() + 1));
	retVal.push_back(MapCoord(coord.getX() - 1, coord.getY()));

	return retVal;
}

int SquadAI::calculateH(MapCoord mapPos, MapCoord goal, Squad sqd)
{
	//return bField->getMovementCost(pos, goal, sqd);
	return abs(mapPos.getX() - goal.getX()) + abs(mapPos.getY() - goal.getY());
}

MovePath SquadAI::constructPath(Node goalNode, std::vector<Node> nodeList)
{
	Node currentNode = goalNode;
	std::vector<MapCoord> retVal1;
	std::vector<int> retVal2;
	while (currentNode.parent != -1)
	{
		retVal1.push_back(currentNode.coord);
		retVal2.push_back(currentNode.g);
		currentNode = nodeList.at(currentNode.parent);
	}
	retVal1.push_back(currentNode.coord); //lägg till startrutan
	retVal2.push_back(0);
	std::reverse(retVal1.begin(), retVal1.end());
	std::reverse(retVal2.begin(), retVal2.end());
	return MovePath(retVal1, retVal2);
}

int SquadAI::findLowestF(std::vector<int> subset, std::vector<Node> nodeList)
{
	unsigned int i;
	int lowestF = 999999;
	int lowestSubsetIndex = -1;
	for (i = 0; i < subset.size(); i++)
	{
		if (nodeList.at(subset.at(i)).f < lowestF)
		{
			lowestF = nodeList.at(subset.at(i)).f;
			lowestSubsetIndex = i;
		}
	}
	return lowestSubsetIndex;
}

int SquadAI::isNodeInSubset(Node node, std::vector<int> subset, std::vector<Node> nodeList)
{
	unsigned int i;
	for (i = 0; i < subset.size(); i++)
	{
		if (node.coord.equals(nodeList.at(subset.at(i)).coord))
		{
			return i;
		}
	}
	return -1;
}