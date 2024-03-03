#include "Browsable.h"

BrowsingData::BrowsingData(BrowsableIcon icn, int id)
{
	empty = icn.isEmpty();
	icon = icn;
	browserID = id;
}

void BrowsingData::setIcon(BrowsableIcon icn)
{
	empty = icn.isEmpty();
	icon = icn;
}


void BrowsableIcon::incorporateIcon(BrowsableIcon icon, std::pair<float, float> off)
{
	unsigned int i;
	std::vector<BrowsableIconTag> tagsToAdd = icon.getTags();
	std::vector<std::pair<float, float>> offsToAdd = icon.getOffsets();
	for (i = 0; i < tagsToAdd.size(); i++)
	{
		empty = false;
		icons.push_back(tagsToAdd.at(i));
		offsets.push_back(std::make_pair(offsToAdd.at(i).first + off.first, offsToAdd.at(i).second + off.second));
	}
}