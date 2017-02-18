#include "gworker.h"

#include <thread>

namespace gincu {

void GWorker::threadMain(ThreadDataPointer threadData)
{
	for(;;) {
		{
			std::unique_lock<std::mutex> lock(threadData->signalMutex);
			threadData->signal.wait(lock, [&]() {
				return ! threadData->taskQueue.empty();
			});
		}

		cpgf::GCallback<void ()> task;

		{
			std::lock_guard<std::mutex> lock(threadData->mutex);
			task = threadData->taskQueue.front();
			threadData->taskQueue.pop_front();
		}

		task();
	}
}

void GWorker::addTask(const TaskCallback & task)
{
	this->doCheckStartThread();

	{
		std::lock_guard<std::mutex> lock(threadData->mutex);
		this->threadData->taskQueue.push_back(task);
	}

	this->threadData->signal.notify_one();
}

void GWorker::doCheckStartThread()
{
	if(! this->threadData) {
		this->threadData = std::make_shared<ThreadData>();

		std::thread thread(&threadMain, this->threadData);
		thread.detach();
	}
}


} //namespace gincu

