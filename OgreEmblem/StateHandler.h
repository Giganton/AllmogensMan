#pragma once
#include<vector>

class StateHandler
{
private:
	std::vector<int> stateQueue;
public:
	StateHandler() {};
	StateHandler(int initState);

	int getState();
	void backOneStep();
	void addState(int state);
	void setState(int state);
};