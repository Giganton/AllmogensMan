#pragma once
#include<list>
#include "Profession.h"
#include "Terrain.h"
#include<map>

std::list<Profession> createProfList();
std::map<ProfessionTag, Profession> createProfMap();

std::map<std::string, TerrainTypes> createTerrainMap();