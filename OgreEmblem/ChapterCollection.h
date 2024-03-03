#pragma once
#include "Battle.h"
#include "Chapter.h"

class IdCreator;

class ChapterCollection
{
private:
	std::map<std::string, TerrainTypes> terrainMap;
	IdCreator* idCreator = nullptr;
	std::map<ProfessionTag, Profession> profMap;

	std::vector<Chapter> chapterList;

	void initFirstChapter();
	Battle initC1B1();
	Battle initC1B2();
	Battle initLevelupBattle();
public: 
	ChapterCollection() {};
	ChapterCollection(IdCreator* idManager, std::map<ProfessionTag, Profession> pMap);
	std::vector<Chapter> getAllChapters() { return chapterList; };
};