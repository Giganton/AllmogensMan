#include "ChangeWordSelectionEvent.h"
#include "SquadNamePickerLayer.h"

ChangeWordSelectionEvent::ChangeWordSelectionEvent(int layer, int prefIndex, int descIndex, int subjIndex, std::string currWord) : StructuredEvent(layer)
{
	prefixIndex = prefIndex;
	descriptorIndex = descIndex;
	subjectIndex = subjIndex;
	currentWord = currWord;
}

void ChangeWordSelectionEvent::applyToSquadNamePickerLayer(SquadNamePickerLayer* layer)
{
	layer->updateSelection(prefixIndex, descriptorIndex, subjectIndex, currentWord);
}