#include "Chapter.h"


Chapter::Chapter(std::vector<Battle> battles)
{ 
	unsigned int i;
	for (i = 0; i < battles.size(); i++)
	{
		battleList.push_back(std::make_pair(battles.at(i), false));
	}
}

Battle Chapter::getNextBattle()
{
	unsigned int i;
	for (i = 0; i < battleList.size(); i++)
	{
		if (!battleList.at(i).second)
		{
			return battleList.at(i).first;
		}
	}
	throw new std::exception();
	return Battle();
}

void Chapter::battleWon()
{
	unsigned int i;
	for (i = 0; i < battleList.size(); i++)
	{
		if (!battleList.at(i).second)
		{
			battleList.at(i).second = true;
			break;
		}
	}
}