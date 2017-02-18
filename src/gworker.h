#ifndef GWORKER_H
#define GWORKER_H

#include "cpgf/gcallback.h"

#include <memory>
#include <deque>
#include <mutex>
#include <condition_variable>

namespace gincu {

class GWorker
{
public:
	typedef cpgf::GCallback<void ()> TaskCallback;

private:
	struct ThreadData
	{
		std::deque<TaskCallback> taskQueue;
		std::mutex mutex;
		std::condition_variable signal;
		std::mutex signalMutex;
	};

	typedef std::shared_ptr<ThreadData> ThreadDataPointer;

public:
	void addTask(const TaskCallback & task); // called from main thread

private:
	void doCheckStartThread();

private:
	static void threadMain(ThreadDataPointer threadData);

private:
	ThreadDataPointer threadData;
};


} //namespace gincu


#endif
