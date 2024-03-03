#pragma once

class DisbandSquadCommand
{
public:
	DisbandSquadCommand() {};
	DisbandSquadCommand(int id) { squadID = id; };

	int squadID = -1;
};