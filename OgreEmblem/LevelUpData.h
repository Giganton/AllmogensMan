#pragma once

struct LevelUpData
{
	int squadID = -1;
	int unitID = -1;
	int newLevel = -1;

	LevelUpData() {};
	LevelUpData(int sID, int uID, int level) { squadID = sID; unitID = uID; newLevel = level; };
};