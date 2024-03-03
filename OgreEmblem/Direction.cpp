#include "Direction.h"

Direction DIR::oppositeDirection(Direction dir)
{
	switch (dir)
	{
	case Direction::up:
		return Direction::down;
		break;
	case Direction::right:
		return Direction::left;
		break;
	case Direction::left:
		return Direction::right;
		break;
	case Direction::down:
		return Direction::up;
		break;
	default:
		return Direction::up;
	}
}