#include "SquadPos.h"
#include<stdexcept>

SquadPos::SquadPos(int index)
{
	switch (index)
	{
	case 0:
		x = SquadColCoord::back;
		y = SquadRowCoord::top;
		break;
	case 1:
		x = SquadColCoord::back;
		y = SquadRowCoord::mid;
		break;
	case 2:
		x = SquadColCoord::back;
		y = SquadRowCoord::bot;
		break;
	case 3:
		x = SquadColCoord::front;
		y = SquadRowCoord::top;
		break;
	case 4:
		x = SquadColCoord::front;
		y = SquadRowCoord::mid;
		break;
	case 5:
		x = SquadColCoord::front;
		y = SquadRowCoord::bot;
		break;
	default:
		throw new std::exception();
	}
}

int SquadPos::getIndexRepresentation() const
{
	int a, b;
	switch (y)
	{
	case SquadRowCoord::top:
		a = 0;
		break;
	case SquadRowCoord::mid:
		a = 1;
		break;
	case SquadRowCoord::bot:
		a = 2;
		break;
	default:
		throw new std::exception();
	}
	if (x == SquadColCoord::back)
	{
		b = 0;
	}
	else
	{
		b = 3;
	}

	return a + b;
}

SquadRowCoord getOpposite(int coord)
{
	switch (coord)
	{
	case SquadRowCoord::top:
		return SquadRowCoord::bot;
		break;
	case SquadRowCoord::mid:
		return SquadRowCoord::mid;
		break;
	case SquadRowCoord::bot:
		return SquadRowCoord::top;
		break;
	default:
		throw new std::exception();
		return SquadRowCoord::top;
	}
}

SquadColCoord getOtherColumn(int coord)
{
	switch (coord)
	{
	case SquadColCoord::back:
		return SquadColCoord::front;
		break;
	case SquadColCoord::front:
		return SquadColCoord::back;
		break;
	default:
		throw new std::exception();
		return SquadColCoord::front;
	}
}

std::vector<SquadPos> getNeighbours(SquadPos mapPos)
{
	std::vector<SquadPos> retVal;
	int x = mapPos.getX();
	int y = mapPos.getY();
	retVal.push_back(SquadPos(getOtherColumn(x), y));
	if (getOpposite(y) == y) //if on middle row
	{
		retVal.push_back(SquadPos(x, SquadRowCoord::top));
		retVal.push_back(SquadPos(x, SquadRowCoord::bot));
	}
	else
	{
		retVal.push_back(SquadPos(x, SquadRowCoord::mid));
	}
	return retVal;
}