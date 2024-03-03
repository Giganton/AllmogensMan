#pragma once
#include "VisualStack.h"
#include "AnimationSignal.h"
#include "GraphicalEvent.h"
#include<vector>

class GraphicsInterface
{
private:
	std::vector<AnimationSignal> signals = { };
	VisualStack vStack;

	StructuredEventQueue eventQueue;
public:
	GraphicsInterface() {};

	VisualStack getVisualStack() { return vStack; };
	std::vector<AnimationSignal> getSignals() { return signals; };
	std::vector<AnimationSignal> getSignals(int ID);
	std::vector<AnimationSignal> takeSignals(int ID);

	VisualStack* getVisualStackPointer() { return &vStack; };
	void setVisualStack(VisualStack stk) { vStack = stk; };
	void addSignal(AnimationSignal signal) { signals.push_back(signal); };
	void addSignals(std::vector<AnimationSignal> newSignals) { signals.insert(signals.end(), newSignals.begin(), newSignals.end()); };
	void setSignalsList(std::vector<AnimationSignal> sgn) { signals = sgn; };
	void clearVisualStack() { vStack = VisualStack(); };

	void deleteSignals() { signals = { }; };

	void addEvents(StructuredEventQueue newEvents) { eventQueue.concatenateQueues(newEvents); };
	StructuredEventQueue getEventQueue() { StructuredEventQueue temp = eventQueue; eventQueue.emptyQueue(); return temp; };
};