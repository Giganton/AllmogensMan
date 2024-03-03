#pragma once
#include<vector>

enum class BrowsableIconTag { squadKnight , unitKnight, unitKnightRed, squadWizard, unitWizard, emptyUnit, plusSign};
enum class BrowserTag { none, red, blue, green};

class BrowsableIcon
{
private:
	std::vector<BrowsableIconTag> icons;
	std::vector<std::pair<float, float>> offsets;
	bool empty = true;


public:
	BrowsableIcon() {};
	BrowsableIcon(BrowsableIconTag icn) { icons.push_back(icn); offsets.push_back(std::make_pair(float(0), float(0))); empty = false; };
	BrowsableIcon(std::vector<BrowsableIconTag> icns, std::vector<std::pair<float, float>> offs) { icons = icns; offsets = offs; empty = false; };

	std::vector<BrowsableIconTag> getTags() { return icons; };
	std::vector<std::pair<float, float>> getOffsets() { return offsets; };

	bool isEmpty() { return empty; };
	void incorporateIcon(BrowsableIcon icon, std::pair<float, float> off);
};

class BrowsingData
{
private:
	bool empty = false;
	BrowsableIcon icon;
	int browserID = -1;
	BrowserTag tag = BrowserTag::none;
	
public:
	BrowsingData() {};
	BrowsingData(BrowsableIcon icon, int id);

	void setIcon(BrowsableIcon icon);
	BrowsableIcon getIcon() { return icon; };

	BrowserTag getBrowserTag() { return tag; };
	void setBrowserTag(BrowserTag bTag) { tag = bTag; };

	void setID(int id) { browserID = id; };
	int getID() { return browserID; };

	bool isEmpty() { return empty; };
};

class Browsable
{
protected:
	BrowsingData bData;
public:
	Browsable() {};
	BrowsableIcon getIcon() { return bData.getIcon(); };
	void setBrowserIcon(BrowsableIcon icon) { bData.setIcon(icon); };
	void setBrowserID(int id) { bData.setID(id); };
	int getBrowserID() { return bData.getID(); };

	virtual BrowsingData getBrowserData() { return bData; };
};