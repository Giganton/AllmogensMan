#pragma once
#include "Cursor.h"
#include "Direction.h"


enum class CursorEdgeType { stop, periodic, controlled };

class CursorHandler
{
protected:
	Cursor cursor;
	CursorEdgeType edgeType = CursorEdgeType::stop;
public:
	CursorPos getCursorPos();
	Cursor getCursor() { return cursor; };
	void setCursorPos(CursorPos mapPos);
	void setCursor(Cursor crsor) { cursor = crsor; };

	virtual void moveCursorUp() = 0;
	virtual void moveCursorDown() = 0;
	virtual void moveCursorLeft() = 0;
	virtual void moveCursorRight() = 0;

	void setEdgeType(CursorEdgeType type) { edgeType = type; };
};

class GridCursorHandler : public CursorHandler
{
private:
	int xBoundary = -1;
	int yBoundary = -1;
public:
	GridCursorHandler() {};
	GridCursorHandler(int xBound, int yBound, CursorEdgeType edgeT);

	void moveCursorUp() override;
	void moveCursorDown() override;
	void moveCursorLeft() override;
	void moveCursorRight() override;
};

class ListCursorHandler : public CursorHandler
{
private:
	int quantity = -1;
	int maxColumns = -1;
	int nrOfRows = -1;
	int lastRowLength = -1;
	bool isPassing = false;
	Direction passingDirection = Direction::up;

	void goToBottom();
	void goToLeftEdge();
	void goToTop();
	void goToRightEdge();
public:
	ListCursorHandler() {};
	ListCursorHandler(int nrOfThings, int maxCols, CursorEdgeType edgeT);

	void moveCursorUp() override;
	void moveCursorDown() override;
	void moveCursorLeft() override;
	void moveCursorRight() override;

	bool isPassingEdge() { return isPassing; };
	Direction getPassingDir() { if (!isPassing) { throw new std::exception(); } return passingDirection; };
	void pass();
	void stopPassing();
};