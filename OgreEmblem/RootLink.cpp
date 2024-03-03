#include "RootLink.h"


RootLink::RootLink(ExternalStateControls* extCtrl)
{
	level = 0;
	externalControls = extCtrl;
}

void RootLink::preSubLevelClosing()
{
	ExternalStateControls controls;
	if (middleMan)
	{
		controls = nextLevel->collectExternalControls(controls);
	}
	*externalControls = controls;
}