#include "gincu/geventqueue.h"
#include "gincu/gutil.h"

namespace gincu {

std::deque<GEventQueue *> GEventQueue::eventQueueList;
GEventQueue::MutexType GEventQueue::eventQueueListMutex;

void GEventQueue::dispatchAll()
{
	LockType lock(eventQueueListMutex);
	for(GEventQueue * eventQueue : eventQueueList) {
		eventQueue->dispatch();
	}
}

GEventQueue::GEventQueue()
{
	LockType lock(eventQueueListMutex);
	eventQueueList.push_back(this);
}

GEventQueue::~GEventQueue()
{
	LockType lock(eventQueueListMutex);
	removeValueFromContainer(eventQueueList, this);
}

void GEventQueue::addListener(const GEventType type, const EventListener & listener, const GEvent::TagType tag)
{
	LockType lock(this->listenerMutex);
	ListenerItem & item = this->listenerMap[type];
	if(tag == nullptr) {
		item.nonTagListenerList.add(listener);
	}
	else {
		item.taggedListenerList.push_back({ listener, tag });
	}
}

void GEventQueue::addListener(const EventListener & listener, const GEvent::TagType tag)
{
	this->addListener(GEventType::none, listener, tag);
}

void GEventQueue::removeListener(const GEventType type, const EventListener & listener, const GEvent::TagType tag)
{
	LockType lock(this->listenerMutex);
	auto it = this->listenerMap.find(type);
	if(it != this->listenerMap.end()) {
		if(tag == nullptr) {
			it->second.nonTagListenerList.remove(listener);
		}
		else {
			this->doRemoveFromTaggedList(&it->second.taggedListenerList, listener, tag);
		}
	}
}

void GEventQueue::removeListener(const EventListener & listener, const GEvent::TagType tag)
{
	this->removeListener(GEventType::none, listener, tag);
}

void GEventQueue::send(const GEvent & event)
{
	this->doDispatchEvent(event);
}

void GEventQueue::post(const GEvent & event)
{
	{
		LockType lock(this->eventMutex);
		this->eventQueue.push_back(event);
	}
}

void GEventQueue::dispatch()
{
	while(! this->eventQueue.empty()) {
		this->doDispatch();
	}
}

void GEventQueue::doDispatch()
{
	const std::size_t count = this->eventQueue.size();
	for(std::size_t i = 0; i < count; ++i) {
		const GEvent & event = this->eventQueue[i];
		this->doDispatchEvent(event);
	}
	
	{
		LockType lock(this->eventMutex);
		this->eventQueue.erase(this->eventQueue.begin(), this->eventQueue.begin() + count);
	}
}

void GEventQueue::doDispatchEvent(const GEvent & event)
{
	this->doDispatchEventByType(event, event.getType());
	if(event.getType() != GEventType::none) {
		this->doDispatchEventByType(event, GEventType::none); // dispatch to "catch all" listeners.
	}
}

void GEventQueue::doDispatchEventByType(const GEvent & event, const GEventType type)
{
	auto it = this->listenerMap.find(type);
	if(it != this->listenerMap.end()) {
		if(event.getTag() == nullptr) {
			it->second.nonTagListenerList(event);
		}
		else {
			for(int i = (int)it->second.taggedListenerList.size() - 1; i >= 0; --i) {
				TaggedListener & item = it->second.taggedListenerList[i];
				if(item.listener.empty()) {
					LockType lock(this->listenerMutex);
					it->second.taggedListenerList.erase(it->second.taggedListenerList.begin() + i);
					continue;
				}
				if(item.tag == event.getTag()) {
					item.listener(event);
				}
			}
		}
	}
}

void GEventQueue::doRemoveFromTaggedList(std::deque<TaggedListener> * taggedList, const EventListener & listener, const GEvent::TagType tag)
{
	// Don't remove the item because this may happen during dispatching
	// instead we just set the listener to empty.
	// Also we need to iterate in the reversed order because at the mean time new listener may be added from another thread
	for(int i = (int)taggedList->size() - 1; i >= 0; --i) {
		TaggedListener & item = taggedList->at(i);
		if(item.listener == listener && item.tag == tag) {
			item.listener = EventListener();
		}
	}
}

void GEventQueue::doRemoveFromTaggedList(std::deque<TaggedListener> * taggedList, const EventListener & listener)
{
	for(int i = (int)taggedList->size() - 1; i >= 0; --i) {
		TaggedListener & item = taggedList->at(i);
		if(item.listener == listener) {
			item.listener = EventListener();
		}
	}
}


} //namespace gincu

