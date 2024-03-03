#pragma once
#include<string>

enum class TerrainTypes { noTerrain, field };

class Terrain
{
private:
	TerrainTypes type = TerrainTypes::noTerrain;
	//std::string imagePath = "textures\\map\\field.png";
public:
	Terrain() { type = TerrainTypes::noTerrain; };
	Terrain(TerrainTypes tp) { type = tp; };
	std::string getName();
	TerrainTypes getType() { return type; };
	//std::string getImagePath() { return imagePath; };
};