#pragma once

class ExternalStateControls
{
public:
	ExternalStateControls() {};

	bool startNextBattle = false;
	bool openCampScreen = false;

	void reset() { startNextBattle = false; openCampScreen = false; };
};

ExternalStateControls compoundControls(ExternalStateControls c1, ExternalStateControls c2);