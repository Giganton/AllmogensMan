#include "GraphicalEvent.h"
#include "BrowserEvent.h"
#include "StructuredEvent.h"

StructuredEventQueue::~StructuredEventQueue()
{
	emptyQueue();
}

void StructuredEventQueue::emptyQueue()
{
	while (queue.size() > 0)
	{
		delete queue.at(0);
		queue.erase(queue.begin());
	}
}

StructuredEventQueue::StructuredEventQueue(const StructuredEventQueue& cpEQ)
{
	unsigned int i;
	for (i = 0; i < cpEQ.queue.size(); i++)
	{
		queue.push_back(cpEQ.queue.at(i)->clone());
	}
}

StructuredEventQueue& StructuredEventQueue::operator=(const StructuredEventQueue asEQ)
{
	unsigned int i;
	queue.clear();
	for (i = 0; i < asEQ.queue.size(); i++)
	{
		queue.push_back(asEQ.queue.at(i)->clone());
	}
	return *this;
}

void StructuredEventQueue::addEvent(StructuredEvent* evnt)
{
	StructuredEvent* temp = evnt->clone();
	queue.push_back(temp);
}

StructuredEvent* StructuredEventQueue::pop()
{
	if (queue.size() == 0)
	{
		throw new std::exception();
	}
	StructuredEvent* temp = queue.at(0)->clone();
	delete(queue.at(0));
	queue.erase(queue.begin());

	return temp;
}

StructuredEvent* StructuredEventQueue::getFirstEvent()
{
	return getEventAt(0);
}

StructuredEvent* StructuredEventQueue::getEventAt(int i)
{
	if (queue.size() == 0)
	{
		throw new std::exception();
	}
	return queue.at(i)->clone();

}

void StructuredEventQueue::removeFirstEvent()
{
	removeEventAt(0);
}

void StructuredEventQueue::removeEventAt(int i)
{
	if (queue.size() < i + 1)
	{
		throw new std::exception();
	}
	delete queue.at(i);
	queue.erase(queue.begin() + i);
}

void StructuredEventQueue::concatenateQueues(StructuredEventQueue qu)
{
	while (qu.size() > 0)
	{
		StructuredEvent* temp = qu.pop();
		addEvent(temp);
		delete temp;
	}
}