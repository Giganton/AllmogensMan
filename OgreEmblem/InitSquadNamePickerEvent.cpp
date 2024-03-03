#include "InitSquadNamePickerEvent.h"
#include "SquadNamePickerLayer.h"


InitSquadNamePickerEvent::InitSquadNamePickerEvent(int layer, std::vector<std::string> prefix, std::vector<std::string> descr, std::vector<std::string> subj, std::string startString) : StructuredEvent(layer)
{
	prefixes = prefix;
	descriptors = descr;
	subjects = subj;

	currentString = startString;
}
void InitSquadNamePickerEvent::applyToSquadNamePickerLayer(SquadNamePickerLayer* layer)
{
	layer->init(prefixes, descriptors, subjects, currentString);
}