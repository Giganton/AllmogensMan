#pragma once
#include<vector>
#include<string>
#include "Direction.h"

class CursorPos
{
public:
	CursorPos() {};
	CursorPos(int xPos, int yPos) { x = xPos; y = yPos; };
	int x = 0;
	int y = 0;
	bool operator<(CursorPos const& rhs) const { return (x + y) < (rhs.x + rhs.y); };
	bool operator==(CursorPos const& rhs) const { return ((x == rhs.x) && (y == rhs.y)); };
};

class CursorMove
{
public:
	CursorPos start;
	CursorPos end;
	bool passedEdge = false;
	Direction passDir = Direction::up;

	CursorMove() {};
	CursorMove(CursorPos st, CursorPos en) { start = st; end = en; };
	CursorMove(CursorPos st, CursorPos en, Direction pDir) { start = st; end = en; passedEdge = true; passDir = pDir; };
};

class Cursor
{
private:
	CursorPos mapPos;
	std::string imagePath;

	std::vector<CursorMove> moveHistory;
public:
	Cursor() {};
	//Cursor(std::string path) { imagePath = path; };
	int getX() { return mapPos.x; };
	int getY() { return mapPos.y; };
	CursorPos getPos() { return mapPos; };

	void setPos(int xPos, int yPos) { mapPos.x = xPos; mapPos.y = yPos; };
	void setPos(CursorPos ps) { mapPos = ps; };
	void move(CursorPos newPos) { moveHistory.push_back(CursorMove(mapPos, newPos)); setPos(newPos); };
	void move(CursorPos newPos, Direction passDir) { moveHistory.push_back(CursorMove(mapPos, newPos, passDir)); setPos(newPos); };

	std::string getImagePath() { return imagePath; };
	std::vector<CursorMove> pullHistory() { std::vector<CursorMove> temp = moveHistory; moveHistory.clear(); return temp; };
};