#include "CursorHandler.h"

void CursorHandler::setCursorPos(CursorPos mapPos)
{
	cursor.setPos(mapPos.x, mapPos.y);
}

CursorPos CursorHandler::getCursorPos()
{
	return CursorPos(cursor.getX(), cursor.getY());
}

GridCursorHandler::GridCursorHandler(int xBound, int yBound, CursorEdgeType edgeT)
{
	cursor = Cursor();
	xBoundary = xBound;
	yBoundary = yBound;
	edgeType = edgeT;
}

ListCursorHandler::ListCursorHandler(int nrOfThings, int maxCols, CursorEdgeType edgeT)
{
	cursor = Cursor();
	quantity = nrOfThings;
	maxColumns = maxCols;
	edgeType = edgeT;
	lastRowLength = ((quantity + maxColumns - 1) % maxColumns) + 1;

	nrOfRows = (int)(ceil)((double)nrOfThings / maxCols);
}

void GridCursorHandler::moveCursorUp()
{
	if (cursor.getY() == 0)
	{
		switch (edgeType)
		{
		case CursorEdgeType::stop:

			break;
		case CursorEdgeType::periodic:
			cursor.setPos(cursor.getX(), yBoundary - 1);
			break;
		case CursorEdgeType::controlled:

			break;
		}
	}
	else
	{
		cursor.setPos(cursor.getX(), cursor.getY() - 1);
	}
}

void GridCursorHandler::moveCursorDown()
{
	if (cursor.getY() == yBoundary - 1)
	{
		switch (edgeType)
		{
		case CursorEdgeType::stop:

			break;
		case CursorEdgeType::periodic:
			cursor.setPos(cursor.getX(), 0);
			break;
		case CursorEdgeType::controlled:

			break;
		}
	}
	else
	{
		cursor.setPos(cursor.getX(), cursor.getY() + 1);
	}
}

void GridCursorHandler::moveCursorLeft()
{
	if (cursor.getX() == 0)
	{
		switch (edgeType)
		{
		case CursorEdgeType::stop:

			break;
		case CursorEdgeType::periodic:
			cursor.setPos(xBoundary - 1, cursor.getY());
			break;
		case CursorEdgeType::controlled:

			break;
		}
	}
	else
	{
		cursor.setPos(cursor.getX() - 1, cursor.getY());
	}
}

void GridCursorHandler::moveCursorRight()
{
	if (cursor.getX() == xBoundary - 1)
	{
		switch (edgeType)
		{
		case CursorEdgeType::stop:

			break;
		case CursorEdgeType::periodic:
			cursor.setPos(0, cursor.getY());
			break;
		case CursorEdgeType::controlled:

			break;
		}
	}
	else
	{
		cursor.setPos(cursor.getX() + 1, cursor.getY());
	}
}

void ListCursorHandler::moveCursorUp()
{
	int currentRow = cursor.getY();

	if (currentRow == 0)
	{
		int currentCol = cursor.getX();

		switch (edgeType)
		{
		case CursorEdgeType::stop:

			break;
		case CursorEdgeType::periodic:
			goToBottom();
			break;
		case CursorEdgeType::controlled:
			isPassing = true;
			passingDirection = Direction::up;

			break;
		}
	}
	else
	{
		cursor.setPos(cursor.getX(), currentRow - 1);
	}
}

void ListCursorHandler::moveCursorDown()
{
	int currentRow = cursor.getY();
	int currentCol = cursor.getX();

	if ((currentRow == nrOfRows - 1 || (currentRow == nrOfRows - 2 && currentCol > lastRowLength - 1)))
	{
		switch (edgeType)
		{
		case CursorEdgeType::stop:

			break;
		case CursorEdgeType::periodic:
			goToTop();
			break;
		case CursorEdgeType::controlled:
			isPassing = true;
			passingDirection = Direction::down;

			break;
		}
	}
	else
	{
		cursor.setPos(currentCol, currentRow + 1);
	}
}

void ListCursorHandler::moveCursorRight()
{
	int currentRow = cursor.getY();
	int currentCol = cursor.getX();
	if ((currentCol == maxColumns - 1) || ((currentRow == nrOfRows - 1) && (currentCol == lastRowLength - 1)))
	{
		switch (edgeType)
		{
		case CursorEdgeType::stop:

			break;
		case CursorEdgeType::periodic:
			goToLeftEdge();
			break;
		case CursorEdgeType::controlled:
			isPassing = true;
			passingDirection = Direction::right;
			break;
		}
	}
	else
	{
		cursor.setPos(currentCol + 1, currentRow);
	}
}

void ListCursorHandler::moveCursorLeft()
{
	int currentCol = cursor.getX();
	int currentRow = cursor.getY();
	if (currentCol == 0)
	{
		switch (edgeType)
		{
		case CursorEdgeType::stop:

			break;
		case CursorEdgeType::periodic:
			goToRightEdge();
			break;
		case CursorEdgeType::controlled:
			isPassing = true;
			passingDirection = Direction::left;

			break;
		}
	}
	else
	{
		cursor.setPos(currentCol - 1, currentRow);
	}
}

void ListCursorHandler::pass()
{
	isPassing = false;
	switch (passingDirection)
	{
	case Direction::up:
		goToBottom();
		break;
	case Direction::right:
		goToLeftEdge();
		break;
	case Direction::left:
		goToRightEdge();
		break;
	case Direction::down:
		goToTop();
		break;
	default:
		throw new std::exception();
	}
}

void ListCursorHandler::stopPassing()
{
	isPassing = false;
}

void ListCursorHandler::goToBottom()
{
	int currentCol = cursor.getX();
	if (currentCol > lastRowLength - 1)
	{
		cursor.setPos(currentCol, nrOfRows - 2);
	}
	else
	{
		cursor.setPos(currentCol, nrOfRows - 1);
	}
}

void ListCursorHandler::goToLeftEdge()
{
	int currentRow = cursor.getY();
	cursor.setPos(0, currentRow);
}

void ListCursorHandler::goToTop()
{
	int currentCol = cursor.getX();
	cursor.setPos(currentCol, 0);
}

void ListCursorHandler::goToRightEdge()
{
	int currentRow = cursor.getY();
	int currentRowLength;
	if (currentRow == nrOfRows - 1)
	{
		currentRowLength = lastRowLength;
	}
	else
	{
		currentRowLength = maxColumns;
	}
	cursor.setPos(currentRowLength - 1, currentRow);

}