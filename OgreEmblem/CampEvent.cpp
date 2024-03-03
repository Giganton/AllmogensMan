#include "CampEvent.h"
#include "CampLayer.h"
#include "CampMenuLayer.h"
#include "BaseLayer.h"

/*void CampEvent::actUponAnimationLayer(AnimationLayer* layer)
{
	layer->applyCampEvent(this);
}

void CampMenuEvent::actUponCampLayer(CampLayer* layer)
{
	layer->applyCampMenuEvent(this);
}

void CampMenuEvent::actUponCampMenuLayer(CampMenuLayer* layer)
{
	layer->applyMenuEvent(menuEvent);
}*/

void CampMenuEvent::applyToCampMenuLayer(CampMenuLayer* layer)
{
	layer->applyMenuEvent(menuEvent);
}

/*void OpenSquadManagerEvent::actUponCampLayer(CampLayer* layer)
{
	layer->applyOpenSquadManagerEvent(this);
}

void OpenSquadManagerEvent::actUponCampMenuLayer(CampMenuLayer* layer)
{
	layer->openSquadManagerLayer();
}*/
void OpenSquadManagerEvent::applyToCampMenuLayer(CampMenuLayer* layer)
{
	layer->openSquadManagerLayer();
}
/*void OpenMapBrowserEvent::actUponCampLayer(CampLayer* layer)
{
	//layer->applyOpenMapBrowserEvent(this);
}*/


void OpenCampMenuEvent::applyToBaseLayer(BaseLayer* layer)
{
	layer->openCampMenuLayer();
}