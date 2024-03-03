#pragma once
#include<vector>

class MouseSignal
{
private:
	int hoveredObjectId = -1;
	int targetLevel = -1;

	std::vector<int> payload;
public:
	MouseSignal() {};
	MouseSignal(int level, int id) { hoveredObjectId = id; targetLevel = level; };

	bool objectIsHovered() { return hoveredObjectId != -1; };
	int getHoveredId() { return hoveredObjectId; };
	int getTargetLevel() { return targetLevel; };
	std::vector<int> getPayload() { return payload; };

	void addPayload(int data) { payload.push_back(data); };
};