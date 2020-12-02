#include "TaskQueue.h"

TaskQueue::TaskQueue()
{

}

void TaskQueue::pushTask(const TTask &task)
{
	mutex.lock();
	this->taskQueue.push(task);
	mutex.unlock();
}

void TaskQueue::popTask()
{
	mutex.lock();
	if (!this->taskQueue.empty()) {
		this->taskQueue.pop();
	}
	mutex.unlock();
}

TTask* TaskQueue::frontTask() 
{
	mutex.lock();
	TTask* task;
	if (!this->taskQueue.empty()) {
		task = &(this->taskQueue.front());
	}
	else {
		task = nullptr;
	}
	mutex.unlock();
	return task;
}

