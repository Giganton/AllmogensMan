#include "StateHandler.h"

StateHandler::StateHandler(int initState)
{
	stateQueue.push_back(initState);
}

int StateHandler::getState()
{
	return stateQueue.at(stateQueue.size() - 1);
}

void StateHandler::backOneStep()
{
	if (stateQueue.size() < 1)
	{
		throw new std::exception();
	}
	stateQueue.erase(stateQueue.end() - 1);
}

void StateHandler::addState(int state)
{
	stateQueue.push_back(state);
}

void StateHandler::setState(int state)
{
	stateQueue.clear();
	stateQueue.push_back(state);
}