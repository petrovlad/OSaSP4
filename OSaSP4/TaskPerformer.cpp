#include "TaskPerformer.h"
// what if num < 0?
TaskPerformer::TaskPerformer(TaskQueue taskQueue, int numOfThreads) 
{
	if (taskQueue.frontTask() == NULL) {
		throw "TaskQueue can't be empty.";
	}
	if (numOfThreads < 1) {
		throw "Number of threads must be greater than 1.";
	}
	this->numOfThreads = numOfThreads;
	this->taskQueue = taskQueue;
}

void TaskPerformer::Perform()
{
	std::vector<std::thread> threads;

	for (int i = this->numOfThreads; i > 0; i--) {
		TTask task = this->taskQueue.frontTask();
		if (task) {
			this->taskQueue.popTask();
			std::thread taskThread(task);
			threads.push_back(move(taskThread));
		}
	}

	for (std::thread &thread : threads) {
		thread.join();
	}
}
