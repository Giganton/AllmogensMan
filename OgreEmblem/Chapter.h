#pragma once
#include "Battle.h"
#include<vector>

class Chapter
{
private:
	std::vector<std::pair<Battle , bool>> battleList;

public:
	Chapter() {};
	Chapter(std::vector<Battle> battles);

	Battle getNextBattle();
	void battleWon();
};