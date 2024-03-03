#pragma once
#include<vector>

class BrowserAnimation;
class BrowserEvent;
class SquadManagerAnimation;
class MenuAnimation;
class StructuredEvent;

class GraphicalEvent
{
private:

public:
	GraphicalEvent() {};

	virtual GraphicalEvent* allocateNew() const = 0;
	virtual GraphicalEvent* clone() const = 0;

	//virtual void actUponBrowserAnim(BrowserAnimation* anim) = 0;
	//virtual void actUponSquadManagerAnim(SquadManagerAnimation* anim) = 0;
	//virtual void actUponMenuAnim(MenuAnimation* anim) = 0;
};


class StructuredEventQueue
{
private:
	std::vector<StructuredEvent*> queue = {};

public:
	StructuredEventQueue() {};
	~StructuredEventQueue();
	StructuredEventQueue(const StructuredEventQueue& cpEQ);
	StructuredEventQueue& operator=(const StructuredEventQueue asEQ);


	void addEvent(StructuredEvent* evnt);
	void emptyQueue();
	bool isEmpty() { return queue.size() == 0; };
	unsigned int size() { return queue.size(); };

	void concatenateQueues(StructuredEventQueue queue);

	//std::vector<GraphicalEvent*> getQueue() { return queue; };
	StructuredEvent* pop();
	StructuredEvent* getFirstEvent();
	StructuredEvent* getEventAt(int i);
	void removeFirstEvent();
	void removeEventAt(int i);
};