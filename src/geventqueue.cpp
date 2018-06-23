#include "gincu/geventqueue.h"
#include "gincu/gutil.h"

#include <deque>
#include <mutex>

namespace gincu {

namespace {

using MutexType = std::recursive_mutex;
using LockType = std::lock_guard<MutexType>;

std::deque<GEventQueue *> eventQueueList;
MutexType eventQueueListMutex;

} //unnamed namespace

void GEventQueue::dispatchAll()
{
	LockType lock(eventQueueListMutex);
	for(GEventQueue * eventQueue : eventQueueList) {
		eventQueue->process();
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


} //namespace gincu

