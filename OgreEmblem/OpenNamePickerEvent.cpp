#include "OpenNamePickerEvent.h"
#include "DraftScreenLayer.h"

void OpenNamePickerEvent::applyToDraftScreenLayer(DraftScreenLayer* layer)
{
	layer->openNamePickerLayer();
}