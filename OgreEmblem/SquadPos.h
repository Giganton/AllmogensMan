#pragma once
#include<vector>

enum SquadColCoord { front = 1, back = 0 };
enum SquadRowCoord { top = 0, mid = 1, bot = 2 };

class SquadPos
{
private:
	int x = -1;
	int y = -1;
public:
	SquadPos() { };
	SquadPos(int posX, int posY) { x = posX; y = posY; }
	SquadPos(int index);
	bool operator==(const SquadPos & rhs) const { return (x == rhs.x) & (y == rhs.y); };
	int getX() { return x; };
	int getY() { return y; };
	int getIndexRepresentation() const;
};

SquadRowCoord getOpposite(int coord);
SquadColCoord getOtherColumn(int coord);
std::vector<SquadPos> getNeighbours(SquadPos mapPos);