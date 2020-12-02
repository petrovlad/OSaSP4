#ifndef TASKPERFORMER_H

#define TASKPERFORMER_H
#include "TaskQueue.h"

class TaskPerformer {
	private:
		int numOfThreads;
		TaskQueue *taskQueue;
	public:
		TaskPerformer(TaskQueue taskQueue, int numOfThreads);
		void Perform();
};

#endif