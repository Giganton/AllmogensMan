#include "OpenConfirmationEvent.h"
#include "DraftScreenLayer.h"

void OpenConfirmationEvent::applyToDraftScreenLayer(DraftScreenLayer* layer)
{
	layer->openConfirmationLayer();
}