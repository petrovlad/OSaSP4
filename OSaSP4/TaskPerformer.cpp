#include "TaskPerformer.h"
// what if num < 0?
TaskPerformer::TaskPerformer(TaskQueue taskQueue, int numOfThreads) 
{
	this->numOfThreads = numOfThreads;
	this->taskQueue = &taskQueue;
}

void TaskPerformer::Perform()
{
	std::vector<std::thread> threads;

	for (int i = this->numOfThreads; i > 0; i--) {
		TTask task = *(this->taskQueue->frontTask());
		if (!task) {
			this->taskQueue->popTask();
			std::thread taskThread(task);
			threads.push_back(taskThread);
		}
	}

	for (std::thread &thread : threads) {
		thread.join();
	}
}
