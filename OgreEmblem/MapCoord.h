#pragma once
#include<cmath>
#include<vector>

class MapCoord
{
private:
	int xCoord = -1;
	int yCoord = -1;
public:
	MapCoord() {};
	MapCoord(int x, int y) { xCoord = x; yCoord = y; };
	int getX() { return xCoord; };
	int getY() { return yCoord; };
	void set(int x, int y) { xCoord = x; yCoord = y; };
	bool equals(MapCoord cd) { return (xCoord == cd.getX() && yCoord == cd.getY()); };
	bool isInList(std::vector<MapCoord> vec) { unsigned int i; for (i = 0; i < vec.size(); i++) { if (equals(vec.at(i))) { return true; } } return false; };
	bool operator <(const MapCoord& R) const
	{
		if (yCoord > R.yCoord) 
		{
			return false; 
		}
		else if (yCoord == R.yCoord)
		{
			return (xCoord < R.xCoord);
		}
		else 
		{ 
			return true; 
		}
	}

	int distanceTo(MapCoord coord) { return (std::abs(coord.getX() - xCoord) + std::abs(coord.getY() - yCoord)); };
	MapCoord operator+(const MapCoord& in) const { return MapCoord(xCoord + in.xCoord, yCoord + in.yCoord); };
	MapCoord operator-(const MapCoord& in) const { return MapCoord(xCoord - in.xCoord, yCoord - in.yCoord); };
	bool operator==(const MapCoord& in) const { return (xCoord == in.xCoord && yCoord == in.yCoord); };
};