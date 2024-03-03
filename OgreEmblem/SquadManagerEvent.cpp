#include "SquadManagerEvent.h"
#include "SquadManagerAnimation.h"
#include "SquadManagerLayer.h"

/*void SquadManagerEvent::actUponAnimationLayer(AnimationLayer* layer)
{
	layer->applySquadManagerEvent(this);
}*/

BrowsingSquadsEvent::~BrowsingSquadsEvent()
{
	delete browserEvent;
}

BrowsingSquadsEvent::BrowsingSquadsEvent(const BrowsingSquadsEvent& cpEQ)
{
	layer = cpEQ.layer;
	browserEvent = cpEQ.browserEvent->cloneAsBrowser();
}

BrowsingSquadsEvent& BrowsingSquadsEvent::operator=(const BrowsingSquadsEvent asEQ)
{
	layer = asEQ.layer;
	browserEvent = asEQ.browserEvent->cloneAsBrowser();

	return *this;
}

/*void BrowsingSquadsEvent::openNewAnimationLayer(AnimationLayer* currLayer)
{
	currLayer->openBrowserLayer();
}*/
/*
void SquadManagerEvent::actUponSquadManagerAnim(SquadManagerAnimation* anim)
{
	anim->applySquadManagerEvent(this);
}*/

/*void SquadManagerEvent::actUponSquadManagerLayer(SquadManagerLayer* layer)
{
	layer->applySquadManagerEvent(this);
}
void BrowsingSquadsEvent::actUponSquadManagerLayer(SquadManagerLayer* layer)
{
	layer->applyBrowsingSquadsEvent(this);
}

void BrowsingSquadsEvent::actUponSquadBrowserLayer(SquadBrowserLayer* layer)
{
	layer->applyBrowserEvent(browserEvent);
}*/

void BrowsingSquadsEvent::applyToSquadBrowserLayer(SquadBrowserLayer* layer)
{
	layer->applyBrowserEvent(browserEvent);
}

/*void SquadManagerMenuEvent::actUponSquadManagerLayer(SquadManagerLayer* layer)
{
	layer->applySquadManagerMenuEvent(this);
}

void SquadManagerMenuEvent::actUponSquadMenuLayer(SquadMenuLayer* layer)
{
	layer->applyMenuEvent(menuEvent);
}

void SquadManagerMenuEvent::actUponSquadBrowserLayer(SquadBrowserLayer* layer)
{
	layer->openSquadMenuLayer();
}*/

void SquadManagerMenuEvent::applyToSquadMenuLayer(SquadMenuLayer* layer)
{
	layer->applyMenuEvent(menuEvent);
}

void SquadManagerMenuEvent::applyToSquadBrowserLayer(SquadBrowserLayer* layer)
{
	layer->openSquadMenuLayer();
}

/*void SquadManagerMenuEvent::openNewAnimationLayer(SquadManagerLayer* currLayer) 
{ 
	currLayer->openSquadMenuLayer(); 
};*/

/*void CloseSubLayerEvent::actUponSquadManagerLayer(SquadManagerLayer* layer)
{
	layer->closeSubLayer();
}*/

/*void EditStateBrowserEvent::actUponSquadManagerLayer(SquadManagerLayer* layer)
{
	layer->applyEditStateBrowserEvent(this);
}*/

/*void EditStateBrowserEvent::actUponEditSquadLayer(EditSquadLayer* layer)
{
	if (squadSide)
	{
		layer->applySquadBrowserEvent(browserEvent);
	}
	else
	{
		layer->applyUnitBrowserEvent(browserEvent);
	}
}*/

void EditStateBrowserEvent::applyToEditSquadLayer(EditSquadLayer* layer)
{
	if (squadSide)
	{
		layer->applySquadBrowserEvent(browserEvent);
	}
	else
	{
		layer->applyUnitBrowserEvent(browserEvent);
	}
}

/*void EditSquadEvent::openNewAnimationLayer(SquadManagerLayer* currLayer)
{
	currLayer->openEditSquadLayer();
}*/

/*void EditStatePassCursorEvent::actUponSquadManagerLayer(SquadManagerLayer* layer)
{
	layer->applyEditStatePassCursorEvent(this);
}

void EditStatePassCursorEvent::actUponEditSquadLayer(EditSquadLayer* layer)
{
	layer->passBrowserCursor(unitToSquad);
}*/

void EditStatePassCursorEvent::applyToEditSquadLayer(EditSquadLayer* layer)
{
	layer->passBrowserCursor(unitToSquad);
}

/*void OpenSquadMenuEvent::actUponSquadManagerLayer(SquadManagerLayer* layer)
{
	layer->applyOpenSquadMenuEvent(this);
}*/

void OpenSquadMenuEvent::actUponSquadBrowserLayer(SquadBrowserLayer* layer)
{
	layer->openSquadMenuLayer();
}

void OpenSquadMenuEvent::applyToSquadBrowserLayer(SquadBrowserLayer* layer)
{
	layer->openSquadMenuLayer();
}

/*void OpenUnitMenuEvent::actUponSquadManagerLayer(SquadManagerLayer* layer)
{
	layer->applyOpenUnitMenuEvent(this);
}*/

void OpenUnitMenuEvent::actUponEditSquadLayer(EditSquadLayer* layer)
{
	layer->openMenuLayer();
}

void OpenUnitMenuEvent::applyToEditSquadLayer(EditSquadLayer* layer)
{
	layer->openMenuLayer();
}

/*void OpenSquadEditorEvent::actUponSquadManagerLayer(SquadManagerLayer* layer)
{
	layer->applyOpenSquadEditorEvent(this);
}*/

void OpenSquadEditorEvent::actUponSquadMenuLayer(SquadMenuLayer* layer)
{
	layer->openEditSquadLayer();
}

void OpenSquadEditorEvent::actUponSquadBrowserLayer(SquadBrowserLayer* layer)
{
	layer->openEditSquadLayer();
}

void OpenSquadEditorEvent::applyToSquadMenuLayer(SquadMenuLayer* layer)
{
	layer->openEditSquadLayer();
}

void OpenSquadEditorEvent::applyToSquadBrowserLayer(SquadBrowserLayer* layer)
{
	layer->openEditSquadLayer();
}