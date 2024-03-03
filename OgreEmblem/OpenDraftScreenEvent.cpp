#include "OpenDraftScreenEvent.h"
#include "BaseLayer.h"

void OpenDraftScreenEvent::applyToBaseLayer(BaseLayer* layer)
{
	layer->openDraftScreenLayer();
}