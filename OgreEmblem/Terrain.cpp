#include "Terrain.h"

std::string Terrain::getName()
{
	std::string retVal;
	switch (type)
	{
	case TerrainTypes::noTerrain:
		throw new std::exception();
		break;
	case TerrainTypes::field:
		retVal = "Field";
		break;
	}
	return retVal;
}